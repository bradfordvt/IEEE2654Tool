/*
 *	PythonInterpreter.cpp
 *
 *	Class to implement the Python interpreter link to the Python application
 *
 *	Class to implement the Python interpreter link to the Python application
 *
 * Copyright (C) 2024 Bradford G. Van Treuren
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

static const char __authors__[] = "Bradford G. Van Treuren";
static const char __contact__[] = "bradvt59@gmail.com";
static const char __copyright__[] = "Copyright (C) 2024, Bradford G. Van Treuren";
static const char __credits__[] = "Bradford G. Van Treuren";
static const char __date__[] = "2024/09/30";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <cstdio>
#include "dsl/PythonInterpreter.hpp"
#include "builder/PathManager.hpp"
#include "bus/CommandBus.hpp"
#include "log/Logger.hpp"
#include <Python.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <locale>
#include <iostream>
#include <sstream>
#include <bitset>

#ifdef WIN32	// Windows includes
#include <Windows.h>
#include <process.h>
#define sleep(x) Sleep(1000*x)
HANDLE handle;
HANDLE apply_handle;
#else	// POSIX includes
#include <pthread.h>
pthread_t mythread;
pthread_t apply_thread;
#endif

#include "debug/Verify.hpp"

struct reqargs {
	/* const */ char *target;
	size_t len;
	uint8_t *message;
};

template <typename T>
class ThreadSafeQueue {
    std::mutex mutex;
    std::condition_variable cond_var;
    std::queue<T> queue;

public:
    void push(T item) {
        {
            std::lock_guard lock(mutex);
            queue.push(item);
        }

        cond_var.notify_one();
    }

    T& front() {
        std::unique_lock lock(mutex);
        cond_var.wait(lock, [&]{ return !queue.empty(); });
        return queue.front();
    }

    void pop() {
        std::lock_guard lock(mutex);
        queue.pop();
    }

    bool empty() const {
	    return queue.empty();
    }
};

ThreadSafeQueue<struct reqargs*> req_queue;
ThreadSafeQueue<struct reqargs*> resp_queue;
std::condition_variable cond_var_run;
std::mutex mutex_run;
static int transaction_done = 0;
static PyObject *self_obj = NULL;
static PyObject *response_callback = NULL;
static int my_errno;
static int apply_flag = 0;
static long timeout = 0L;

/*
 * Python strings are in utf-8 format. So the code
 *	if(!PyArg_ParseTuple(args, "OiO", &target_p, &ln, &message_p)) {
 *	}
 *	PyObject* mrepr = PyObject_Repr(message_p);
 *      PyObject* mstr = PyUnicode_AsEncodedString(mrepr, "utf-8", "~E~");
 *      const char *message = (const char*)PyBytes_AS_STRING(mstr);
 *
 *      produces a string that looks like:
 *      b'\x1a\x06BUTTON"\x07\x12\x05PRESS'
 *      when the C++ protobuf needs a serialized string that looks like:
 *      ^Z^FBUTTON"^G^R^EPRESS
 *      parse_utf8() transforms the utf-8 b' format into the second format as
 *      a workaround.
 *
 */
static int parse_utf8(const char* str, int len, std::string& s, int* flen) {
	char c0, c1;
	char c;
	if(len == 0) {
		std::cerr << "parse_utf8 found: len == 0" << std::endl;
		return 0;
	}
	if((str[0] == '\\') && (str[1] == 'x')) { // utf-8 character start
		if(str[2] >= '0' && str[2] <= '9') {
			c0 = str[2] - '0';
		}
		else if(str[2] >= 'a' && str[2] <= 'f') {
			c0 = str[2] - 'W';
		}
		else {
			return -1;
		}
		if(str[3] >= '0' && str[3] <= '9') {
			c1 = str[3] - '0';
		}
		else if(str[3] >= 'a' && str[3] <= 'f') {
			c1 = str[3] - 'W';
		}
		else {
			return -1;
		}
		// std::cerr << "parse_utf8 found: str[2], str[3], c0, c1:: " << static_cast<int>(str[2]) << ", " << static_cast<int>(str[3]) << ", " << static_cast<int>(c0) << ", " << static_cast<int>(c1) << std::endl;
		c = ((c0 << 4) + c1) & 0xFF;
		s += c;
		(*flen)++;
		// std::cerr << "parse_utf8 found: str[2], str[3], c0, c1, c, s:: " << str[2] << ", " << str[3] << ", " << static_cast<unsigned int>(c0) << ", " << static_cast<unsigned int>(c1) << ", " << static_cast<unsigned int>(c) << ", " << s << std::endl;
		return parse_utf8(&str[4], len - 4, s, flen);
	}
	else if((str[0] == '\\') && (str[1] == 't')) { // TAB
		c = 0x9;
		s += c;
		return parse_utf8(&str[2], len - 2, s, flen);
	}
	else if((str[0] == '\\') && (str[1] == 'n')) { // NL
		s += '\n';
		return parse_utf8(&str[2], len - 2, s, flen);
	}
	else if((str[0] == '\\') && (str[1] == 'r')) { // CR
		s += '\r';
		return parse_utf8(&str[2], len - 2, s, flen);
	}
	else if((str[0] == '\\') && (str[1] == 'b')) { // BS
		s += '\b';
		return parse_utf8(&str[2], len - 2, s, flen);
	}
	else if((str[0] == '\\') && (str[1] == '\\')) { // backslash
		s += '\\';
		return parse_utf8(&str[2], len - 2, s, flen);
	}
	else {
		s += str[0];
		// std::cerr << "parse_utf8 found: str[0], s:: " << str[0] << ", " << s << std::endl;
		(*flen)++;
		return parse_utf8(&str[1], len - 1, s, flen);
	}
}

static int
dsl_send_command_response(const char *target, size_t len, uint8_t *message) {
	SWDEBUGP2( 5, Verify::DSL, "dsl_send_command_response",
                        " const char*, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "dsl_send_command_response",
                        " const char*, size_t, uint8_t* " );
	// std::cerr << "dsl_send_command_response(): target = " << target << std::endl;
	// std::cerr << "dsl_send_command_response(): len = " << len << std::endl;
	// std::cerr << "dsl_send_command_response(): message = " << (const char*)message << std::endl;
	// std::cerr << "dsl_send_command_response(): response_callback = " << (void*)response_callback << std::endl;
	int ret = 0;
	if(response_callback) {
		// std::cerr << "dsl_send_command_response(): line 184" << std::endl;
		/* Make sure we own the GIL */
		PyGILState_STATE state = PyGILState_Ensure();

		PyObject *target_p = PyUnicode_InternFromString(target);
		PyObject *len_p = PyLong_FromSize_t(len);
		// std::cerr << "dsl_send_command_response(): line 190" << std::endl;
		// PyObject *message_p = PyUnicode_InternFromString(message);
		// sequence of uint8_t values representing UTF-8 encoded string
		// PyObject *message_p = PyUnicode_DecodeUTF8((const char*)message, len, NULL);
		PyObject *message_p = PyBytes_FromStringAndSize((const char*)message, len);
		// std::cerr << "dsl_send_command_response(): line 195" << std::endl;
		// PyObject* args = PyTuple_Pack(4, self_obj, target_p, len_p, message_p);
		PyObject* args = PyTuple_Pack(3, target_p, len_p, message_p);
		PyObject *kwargs = PyDict_New();
		PyObject *result = PyObject_Call(response_callback, args, kwargs);
		if(result == NULL) {
			// std::cerr << "dsl_send_command_response(): callable failed!" << std::endl;
			ret = -1;
		}
		else {
			// std::cerr << "dsl_send_command_response(): line 204" << std::endl;
			if (!PyLong_Check(result))
			{
				// std::cerr << "dsl_send_command_response(): callable didn't return a long" << std::endl;
				ret = -2;
			}
			ret = int(PyLong_AsLong(result));
			// std::cerr << "dsl_send_command_response(): line 211" << std::endl;
			if (PyErr_Occurred())
			{
				PyErr_Print();
				// Py_XDECREF(result);
				// PyGILState_Release(state);
				ret = -3;
			}
		}
		response_callback = NULL;
		Py_DECREF(target_p);
		Py_DECREF(len_p);
		Py_DECREF(message_p);
		Py_DECREF(args);
		// std::cerr << "dsl_send_command_response(): line 225" << std::endl;
		// std::cerr << "dsl_send_command_response(): result = " << (void*)result << std::endl;
		// std::cerr << "dsl_send_command_response(): line 227" << std::endl;
		Py_XDECREF(result);
		PyGILState_Release(state);
	}
	else {
		// std::cerr << "dsl_send_command_response(): response_callback is NULL!" << std::endl;
		ret = -4;
	}
	// std::cerr << "dsl_send_command_response(): line 235" << std::endl;
	return ret;
}

static PyObject*
dsl_set_response_callback(PyObject *self, PyObject *args) {
	SWDEBUGP2( 5, Verify::DSL, "dsl_set_response_callback",
                        " PyObject*, PyObject* " );
	SWDEBUG2( 5, Verify::TRACE, "dsl_set_response_callback",
                        " PyObject*, PyObject* " );
	long ret = 0;
	if(!PyArg_ParseTuple(args, "O", &response_callback)) {
                // Log the error
		ret = -1;
        }
	self_obj = self;
        return PyLong_FromLong(ret);
}

static PyObject*
dsl_set_timeout(PyObject *self, PyObject *args) {
	SWDEBUGP2( 5, Verify::DSL, "dsl_set_timeout",
                        " PyObject*, PyObject* " );
	SWDEBUG2( 5, Verify::TRACE, "dsl_set_timeout",
                        " PyObject*, PyObject* " );
	long ret = 0;
	PyObject *po_timeout;
	if(!PyArg_ParseTuple(args, "O", &po_timeout)) {
                // Log the error
		ret = -1;
        }
	timeout = PyLong_AsLong(po_timeout);
        return PyLong_FromLong(ret);
}

static PyObject*
dsl_send_command_request(PyObject *self, PyObject *args) {
	SWDEBUGP2( 5, Verify::DSL, "dsl_send_command_request",
                        " PyObject*, PyObject* " );
	SWDEBUG2( 5, Verify::TRACE, "dsl_send_command_request",
                        " PyObject*, PyObject* " );
        int ret = -1;
	self_obj = self;
	PyObject *target_p, *message_p;
	int ln;
	if(!PyArg_ParseTuple(args, "OiO", &target_p, &ln, &message_p)) {
                // Log the error
                Py_INCREF(Py_None);
                return Py_None;
        }
	// std::cerr << "dsl_send_command_request(): ln = " << ln << std::endl;
	PyObject* trepr = PyObject_Repr(target_p);
        PyObject* tstr = PyUnicode_AsEncodedString(trepr, "utf-8", "~E~");
        const char *target = PyBytes_AS_STRING(tstr);

	PyObject* mrepr = PyObject_Repr(message_p);
        PyObject* mstr = PyUnicode_AsEncodedString(mrepr, "utf-8", "~E~");
        const char *message = (const char*)PyBytes_AS_STRING(mstr);
	size_t len = strlen((const char*)message);

	std::string smessage;
	int flen = 0;
	int r = parse_utf8(&message[2], len - 3, smessage, &flen);
	if(r) {
		// std::cerr << "dsl_send_command_request(): parse_utf8() failed!" << std::endl;
		return PyLong_FromLong(-8);
	}
	// std::cerr << "dsl_send_command_request(): smessage = " << smessage << std::endl;
	// std::cerr << "dsl_send_command_request(): target = " << target << std::endl;
	// Remove single quotes at beginning and end if present
	char* tmp_target = strdup(target);
	const char* start = strchr(tmp_target, '\'');
	const char* end = strrchr(tmp_target, '\'');
	if(start && end) {
		memmove(tmp_target, start + 1, end - start - 1);
		tmp_target[end - start - 1] = '\0';
	}
	char* tmp_mem = strndup(message, len);
	const char* startm = strchr(tmp_mem, '\'');
	const char* endm = strrchr(tmp_mem, '\'');
	if(startm && endm) {
		memmove(tmp_mem, startm + 1, endm - startm - 1);
		tmp_mem[endm - startm - 1] = '\0';
	}
	// std::cerr << "dsl_send_command_request(): tmp_target = " << tmp_target << std::endl;
	// std::cerr << "dsl_send_command_request(): len = " << len << std::endl;
	// std::cerr << "dsl_send_command_request(): message = " << message << std::endl;
	uint8_t* tmp_message = (uint8_t*)strndup((const char*)smessage.c_str(), smessage.length());
	// std::cerr << "dsl_send_command_request(): tmp_message = " << tmp_message << std::endl;
	// std::cerr << "dsl_send_command_request(): flen = " << flen << std::endl;
	// std::cerr << "Obtaining CommandBus Singleton instance." << std::endl;
	// Obtain the CommandBus object to handle commands
	CommandBus *cb_p = CommandBus::get_command_bus(); // Factory method

	if(cb_p != NULL) {
		// std::cerr << "Calling CommandBus::send_command_request()" << std::endl;
		ret = cb_p->send_command_request(::dsl_send_command_response, tmp_target, flen, tmp_message);
		// ret = cb_p->send_command_request(::dsl_send_command_response, tmp_target, endm - startm - 2, (uint8_t*)tmp_mem);
		// ret = cb_p->send_command_request(::dsl_send_command_response, tmp_target, len, (uint8_t*)message);
	}
	else {
		ret = -9;
	}
	free(tmp_target);
	free(tmp_mem);

	Py_XDECREF(trepr);
        Py_XDECREF(tstr);
        Py_XDECREF(mrepr);

	// std::cerr << "dsl_send_command_request(): ret = " << ret << std::endl;
        return PyLong_FromLong(ret);
}

static PyMethodDef DSLMethods[] = {
	{"send_command_request", dsl_send_command_request, METH_VARARGS,
	"Sends a serialized IEEE2654 Command Message to the framework."},
	{"set_response_callback", dsl_set_response_callback, METH_VARARGS,
	"Sets the callback function to call to handle responses to command requests."},
	{"set_timeout", dsl_set_timeout, METH_VARARGS,
	"Sets the callback function time to wait for completion of a command."},
	{NULL, NULL, 0, NULL}
};

static PyModuleDef DSLModule = {
	PyModuleDef_HEAD_INIT, "IEEE2654DSL", NULL, -1, DSLMethods,
	NULL, NULL, NULL, NULL
};

static PyObject*
PyInit_DSL(void) {
	SWDEBUGP2( 5, Verify::DSL, "PyInit_DSL",
                        " void " );
	SWDEBUG2( 5, Verify::TRACE, "PyInit_DSL",
                        " void " );
	return PyModule_Create(&DSLModule);
}

PythonInterpreter::PythonInterpreter() {
	SWDEBUGP1( 5, Verify::DSL, "PythonInterpreter::PythonInterpreter");
	SWDEBUG1( 5, Verify::TRACE, "PythonInterpreter::PythonInterpreter");
	apply_flag = 0;
}

PythonInterpreter::~PythonInterpreter() {
	SWDEBUGP1( 5, Verify::DSL, "PythonInterpreter::~PythonInterpreter");
	SWDEBUG1( 5, Verify::TRACE, "PythonInterpreter::~PythonInterpreter");
}

int PythonInterpreter::run(const std::string& filename, std::vector<std::string> argv) {
	SWDEBUGP2( 5, Verify::DSL, "PythonInterpreter::run",
                        " const std::string&, std::vector<std::string>" );
	SWDEBUG2( 5, Verify::TRACE, "PythonInterpreter::run",
                        " const std::string&, std::vector<std::string>" );
	std::vector<std::string>::size_type i;
	CMD_LINE_STRUCT cmd;

	cmd.argv.push_back(filename);
	// cmd.argv[0] = filename.c_str();
	// cmd.argv[1] = func.c_str();
	for(i = 0; i < argv.size(); i++) {
		if(i == 0) {
			cmd.argv.push_back(argv[i]);
		}
		else {
			cmd.argv.push_back(argv[i]);
		}
	}
	cmd.argc = cmd.argv.size();

	// Create a thread
	apply_flag = 1;
#ifdef WIN32
	// Windows code
	// apply_handle = (HANDLE) _beginthread( PythonInterpreter::applyProc,0,&cmd);
	handle = (HANDLE) _beginthread( PythonInterpreter::ThreadProc,0,&cmd);
#else
	// POSIX code
	// std::cerr << "Starting applyProc" << std::endl;
	// pthread_create( &apply_thread, NULL, PythonInterpreter::applyProc, (void*)&cmd );
	// std::cerr << "Starting ThreadProc" << std::endl;
	pthread_create( &mythread, NULL, PythonInterpreter::ThreadProc, (void*)&cmd );
#endif

	// Join and wait for the created thread to complete...
#ifdef WIN32
	// Windows code
	WaitForSingleObject(handle,INFINITE);
	apply_flag = 0;
	// WaitForSingleObject(apply_handle,INFINITE);
#else
	// POSIX code
	// std::cerr << "Joining ThreadProc" << std::endl;
	pthread_join(mythread, NULL);
	apply_flag = 0;
	// std::cerr << "Joining applyProc" << std::endl;
	// pthread_join(apply_thread, NULL);
#endif

	// delete [] wargv;
	// delete [] cmd.argv;
	return 0;
}

void *PythonInterpreter::ThreadProc( void *data )
{
	SWDEBUGP2( 5, Verify::DSL, "PythonInterpreter::ThreadProc",
                        " void*" );
	SWDEBUG2( 5, Verify::TRACE, "PythonInterpreter::ThreadProc",
                        " void*" );
	// PyObject *pName, *pModule, *pDict, *pFunc;
	// PyThreadState *mainThreadState, *myThreadState, *tempState;
	// PyInterpreterState *mainInterpreterState;
	int i;
	FILE* file = nullptr;

	// std::cerr << "Creating argv" << std::endl;
	CMD_LINE_STRUCT *arg = (CMD_LINE_STRUCT*)data;
	// std::wstring wfilename(arg->argv[0]);
	// std::string filename(wfilename.begin(), wfilename.end());
	const std::wstring **wargv = new const std::wstring*[arg->argc + 1];
	const wchar_t **argv = new const wchar_t*[arg->argc + 1];
	for(i = 0; i < arg->argc; i++) {
		std::wostringstream conv;
		std::string s(arg->argv[i]);
		conv << s.c_str();
		wargv[i] = new std::wstring(conv.str());
		// std::cerr << "wargv[" << i << "] = " << *(wargv[i]) << std::endl;
	}
	wargv[i] = nullptr;
	for(i = 0; i < arg->argc; i++) {
		argv[i] = wargv[i]->c_str();
	}
	argv[i] = nullptr;

	PyImport_AppendInittab("IEEE2654DSL", &PyInit_DSL);
	// Py_SetProgramName(wargv[0]->c_str());
	Py_Initialize();
	// Set module search path
	PathManager *pm_p = PathManager::get_PathManager();
	const std::vector<std::string>& pypathv = pm_p->get_python_search_path();
	std::string sstr = "import sys";
	// std::cerr << "sstr = " << sstr << std::endl;
	PyRun_SimpleString(sstr.c_str());
	// std::string dstr2 = "print(sys.modules[__name__].__dict__)";
	// std::cerr << "dstr2 = " << dstr2 << std::endl;
	// PyRun_SimpleString(dstr2.c_str());
	for( auto iter = pypathv.begin(); iter != pypathv.end(); iter++) {
		std::string str = "sys.path.append('"  + *iter + "')";
		// std::cerr << "str = " << str << std::endl;
		PyRun_SimpleString(str.c_str());
	}
	for( auto iter = pypathv.begin(); iter != pypathv.end(); iter++) {
		std::string pfullpath = *iter + pm_p->get_path_separator() + arg->argv[0];
		PyObject *obj = Py_BuildValue("s", pfullpath.c_str()); 
		file = _Py_fopen_obj(obj, "r+");
		if(file != NULL) break;
	}
	// std::string dstr1 = "print(sys.modules[__name__].__dict__)";
	// std::cerr << "dstr1 = " << dstr1 << std::endl;
	// PyRun_SimpleString(dstr1.c_str());
	PySys_SetArgv(arg->argc, const_cast<wchar_t**>(argv));
	// Don't use module name with .py extension added
	std::string module_name(arg->argv[0].begin(), arg->argv[0].end()-3);
	// std::cerr << "module_name = " << module_name.c_str() << std::endl;
	PyObject * moduleName = PyUnicode_FromString(module_name.c_str());
	PyObject *pluginModule = PyImport_Import(moduleName);
	if(pluginModule == nullptr) {
		PyErr_Print();
	}
	else {
		// std::cerr << "Module imported successfully!" << std::endl;
		// std::string dstr = "print(sys.modules[__name__].__dict__)";
		// std::cerr << "dstr = " << dstr << std::endl;
		// PyRun_SimpleString(dstr.c_str());
		if(file != NULL) {
			PyRun_SimpleFile(file, arg->argv[0].c_str());
			fclose(file);
		}
		else {
			std::cerr << "file not set!" << std::endl;
		}
		Py_DECREF(moduleName);
		Py_DECREF(pluginModule);
		// std::cerr << "Finalizing..." << std::endl;
		Py_Finalize();
	}
	delete [] argv;
	delete [] wargv;
	// std::cerr << "Returning from ThreadProc()" << std::endl;
	pthread_exit(NULL);
}

void *PythonInterpreter::applyProc( void* /*data*/ )
{
	SWDEBUGP2( 5, Verify::DSL, "PythonInterpreter::applyProc",
                        " void*" );
	SWDEBUG2( 5, Verify::TRACE, "PythonInterpreter::applyProc",
                        " void*" );
	int ret = -1;
	my_errno = -1;
	// std::cerr << "Entering PythonInterpreter::applyProc()" << std::endl;
	while(apply_flag) {
		// std::cerr << "Waiting for queue data in PythonInterpreter::applyProc()" << std::endl;
		struct reqargs *reqa = req_queue.front(); // no copy, just a reference
		// std::cerr << "Obtaining CommandBus Singleton instance." << std::endl;
		// Obtain the CommandBus object to handle commands
		CommandBus *cb_p = CommandBus::get_command_bus(); // Factory method

		if(cb_p != NULL) {
			// std::cerr << "Calling CommandBus::send_command_request()" << std::endl;
			ret = cb_p->send_command_request(::dsl_send_command_response, reqa->target, reqa->len, reqa->message);
			free(reqa->target);
			free(reqa->message);
			free(reqa);
			req_queue.pop();
		}
		if(ret == 0) {
			struct reqargs *respa = resp_queue.front();
			if(response_callback) {
				/* Make sure we own the GIL */
				PyGILState_STATE state = PyGILState_Ensure();

				PyObject *target_p = PyUnicode_InternFromString(respa->target);
				PyObject *len_p = PyLong_FromSize_t(respa->len);
				// PyObject *message_p = PyUnicode_InternFromString(message);
				// sequence of uint8_t values representing UTF-8 encoded string
				// PyObject *message_p = PyUnicode_DecodeUTF8((const char*)respa->message, respa->len, NULL);
				PyObject *message_p = PyBytes_FromStringAndSize((const char*)respa->message, respa->len);
				free(respa->target);
				free(respa->message);
				free(respa);
				resp_queue.pop();
				PyObject* args = PyTuple_Pack(4, self_obj, target_p, len_p, message_p);
				PyObject *kwargs = PyDict_New();
				PyObject *result = PyObject_Call(response_callback, args, kwargs);
				response_callback = NULL;
				Py_DECREF(target_p);
				Py_DECREF(len_p);
				Py_DECREF(message_p);
				Py_DECREF(args);
				if (!PyLong_Check(result))
				{
					// std::cerr << "applyProc(): callable didn't return a long" << std::endl;
					my_errno = -2;
					break;

				}
				if (PyErr_Occurred())
				{
					PyErr_Print();
					Py_XDECREF(result);
					PyGILState_Release(state);
					my_errno = -3;
					break;
				}
				ret = int(PyLong_AsLong(result));
				Py_XDECREF(result);
				PyGILState_Release(state);
				my_errno = ret;
				break;
			}
			else {
				// std::cerr << "applyProc()(): response_callback is not set." << std::endl;
				my_errno = -4;
				break;
			}
		}
		else {
			// std::cerr << "applyProc()(): call to dsl_send_command_request() failed!" << std::endl;
			my_errno = -5;
			break;
		}
	}
	std::lock_guard lock(mutex_run);
	transaction_done = 0;
	cond_var_run.notify_one();
	pthread_exit(NULL);
}

