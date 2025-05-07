/*
 *    Translator.cpp
 *
 *    Class to implement the Translator architectural element.
 *
 *    Class to implement the Translator architectural element.
 *    The class implements the Translator element of the message
 *    layer.  It implements the node of the IEEE2654Tree model.
 *    It also implements the API functions the TransformLibrary,
 *    DebufLibrary, InjectLibrary, and CommandLibrary libraries
 *    call when communicating with the IEEE2654 Tool application.
 *    This file implements the body of the class.
 * 
 * Copyright (C) 2024 Bradford G. Van Treuren
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
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
static const char __date__[] = "2024/02/20";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <stdexcept>
#include <iostream>
#include <string.h>

#include "repository/Repository.hpp"
#include "model/Translator.hpp"
#include "bus/CommandBus.hpp"

#include "factory/TransformLibraryFactory.hpp"
#include "factory/DebugLibraryFactory.hpp"
#include "factory/InjectLibraryFactory.hpp"
#include "factory/CommandLibraryFactory.hpp"
#include "debug/Verify.hpp"
#include "log/Logger.hpp"

#if 0
uint32_t Translator::translator_count = 0;
CommandBus* Translator::cmd_bus = NULL;
std::vector<Translator*> Translator::translator_list;
std::vector<uint32_t> Translator::uid_list;
std::vector<const char*> Translator::path_list;
#endif


Translator::Translator(const TranslatorRep& tr) : trep(tr), ci_p(NULL), ii_p(NULL), tlw_p(NULL), dlw_p(NULL), ilw_p(NULL), clw_p(NULL) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::Translator",
			" const TranslatorRep& " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::Translator",
			" const TranslatorRep& " );
	// SwDebug trace( 1, Verify::MODEL, "Translator::Translator",
			// " const TranslatorRep& " );
#if 0
	std::string tlname = trep.get_TransformLibraryRep().get_library_name();
	if(tlname.length() > 0) {
		TransformLibraryFactory tlf;
		tlib_handle = tlf.create_handle(tlname.c_str());
		if(tlib_handle) {
			tla = tlf.get_api(tlib_handle);
			if(tla == NULL) {
				// TODO - Print error message to logger
				swtrace.log(1, Verify::MODEL, "tla == NULL error!");
				__logger(LOG_TYPE::ERROR, "Translator::Translator: tla == NULL");
			}
		}
		else {
			// TODO - Print error message to logger
			swtrace.log(1, Verify::MODEL, "tlib_handle == NULL error!");
			__logger(LOG_TYPE::ERROR, "Translator::Translator: tlib_handle == NULL");
		}
	}
	else {
		tlib_handle = NULL;
	}
#endif
	std::string tlname = trep.get_TransformLibraryRep().get_library_name();
	if(tlname.length() > 0) {
		tlw_p = new TransformLibraryWrapper(trep.get_translator_uid(), trep.get_TransformLibraryRep());
		if(tlw_p == NULL) {
			// TODO - Print error message to logger
			swtrace.log(1, Verify::MODEL, "tlw_p == NULL error!");
			__logger(LOG_TYPE::ERROR, "Translator::Translator: tlw_p == NULL");
		}
		if(!tlw_p->get_sanity()) {
			// TODO - print error message to logger
			swtrace.log(1, Verify::MODEL, "tlw_p->get_sanity() failed!");
			__logger(LOG_TYPE::ERROR, "Translator::Translator: !tlw_p->get_sanity())");
		}
		if(tlw_p->open() != 0) {
			__logger(LOG_TYPE::ERROR, "Translator::Translator: tlw_p->open() failed!");
		}
		// char *prop_p = strdup(trep.get_properties());
		// std::cerr << "trep.get_properties() = " << trep.get_properties() << std::endl;
		std::string tmp(trep.get_properties());
		// std::cerr << "tmp = " << tmp << std::endl;
		if(tlw_p->config((char*)(tmp.c_str())) != 0) {
			// std::cerr << "Translator path = " << trep.get_path() << std::endl;
			__logger(LOG_TYPE::ERROR, "Translator::Translator: tlw_p->config() failed!");
		}
	}
#if 0
	std::string dlname = trep.get_DebugLibraryRep().get_library_name();
	if(dlname.length() > 0) {
		DebugLibraryFactory dlf;
		dlib_handle = dlf.create_handle(dlname.c_str());
		if(dlib_handle) {
			dla = dlf.get_api(dlib_handle);
			if(dla == NULL) {
				// TODO - Print error message to logger
				swtrace.log(1, Verify::MODEL, "dla == NULL error!");
				__logger(LOG_TYPE::ERROR, "Translator::Translator: dla == NULL");
			}
		}
		else {
			// TODO - Print error message to logger
			swtrace.log(1, Verify::MODEL, "dlib_handle == NULL error!");
			__logger(LOG_TYPE::ERROR, "Translator::Translator: dlib_handle == NULL");
		}
	}
	else {
		dlib_handle = NULL;
	}
#endif
	std::string dlname = trep.get_DebugLibraryRep().get_library_name();
	if(dlname.length() > 0) {
		dlw_p = new DebugLibraryWrapper(trep.get_translator_uid(), trep.get_DebugLibraryRep());
		if(dlw_p == NULL) {
			// TODO - Print error message to logger
			swtrace.log(1, Verify::MODEL, "dlw_p == NULL error!");
			__logger(LOG_TYPE::ERROR, "Translator::Translator: dlw_p == NULL");
		}
		if(!dlw_p->get_sanity()) {
			// TODO - print error message to logger
			swtrace.log(1, Verify::MODEL, "dlw_p->get_sanity() failed!");
			__logger(LOG_TYPE::ERROR, "Translator::Translator: !dlw_p->get_sanity())");
		}
		if(dlw_p->open() != 0) {
			__logger(LOG_TYPE::ERROR, "Translator::Translator: dlw_p->open() failed!");
		}
		// char *prop_p = strdup(trep.get_properties());
		// std::cerr << "trep.get_properties() = " << trep.get_properties() << std::endl;
		std::string tmp(trep.get_properties());
		// std::cerr << "tmp = " << tmp << std::endl;
		if(dlw_p->config((char*)(tmp.c_str())) != 0) {
			// std::cerr << "Translator path = " << trep.get_path() << std::endl;
			__logger(LOG_TYPE::ERROR, "Translator::Translator: dlw_p->config() failed!");
		}
	}
	std::string ilname = trep.get_InjectLibraryRep().get_library_name();
	if(ilname.length() > 0) {
		ilw_p = new InjectLibraryWrapper(trep.get_translator_uid(), trep.get_InjectLibraryRep());
		if(ilw_p == NULL) {
			// TODO - Print error message to logger
			swtrace.log(1, Verify::MODEL, "ilw_p == NULL error!");
			__logger(LOG_TYPE::ERROR, "Translator::Translator: ilw_p == NULL");
		}
		if(!ilw_p->get_sanity()) {
			// TODO - print error message to logger
			swtrace.log(1, Verify::MODEL, "ilw_p->get_sanity() failed!");
			__logger(LOG_TYPE::ERROR, "Translator::Translator: !ilw_p->get_sanity())");
		}
		if(ilw_p->open() != 0) {
			__logger(LOG_TYPE::ERROR, "Translator::Translator: ilw_p->open() failed!");
		}
		// char *prop_p = strdup(trep.get_properties());
		// std::cerr << "trep.get_properties() = " << trep.get_properties() << std::endl;
		std::string tmp(trep.get_properties());
		// std::cerr << "tmp = " << tmp << std::endl;
		if(ilw_p->config((char*)(tmp.c_str())) != 0) {
			std::cerr << "Translator path = " << trep.get_path() << std::endl;
			__logger(LOG_TYPE::ERROR, "Translator::Translator: ilw_p->config() failed!");
		}
	}
	std::string clname = trep.get_CommandLibraryRep().get_library_name();
	if(clname.length() > 0) {
		clw_p = new CommandLibraryWrapper(trep.get_translator_uid(), trep.get_CommandLibraryRep());
		if(clw_p == NULL) {
			// TODO - Print error message to logger
			swtrace.log(1, Verify::MODEL, "clw_p == NULL error!");
			__logger(LOG_TYPE::ERROR, "Translator::Translator: clw_p == NULL");
		}
		if(!clw_p->get_sanity()) {
			// TODO - print error message to logger
			swtrace.log(5, Verify::TRACE, "clw_p->get_sanity() failed!");
			__logger(LOG_TYPE::ERROR, "Translator::Translator: !clw_p->get_sanity())");
		}
		if(clw_p->open() != 0) {
			__logger(LOG_TYPE::ERROR, "Translator::Translator: clw_p->open() failed!");
		}
		// char *prop_p = strdup(trep.get_properties());
		// std::cerr << "trep.get_properties() = " << trep.get_properties() << std::endl;
		std::string tmp(trep.get_properties());
		// std::cerr << "tmp = " << tmp << std::endl;
		if(clw_p->config((char*)(tmp.c_str())) != 0) {
			std::cerr << "Translator path = " << trep.get_path() << std::endl;
			__logger(LOG_TYPE::ERROR, "Translator::Translator: clw_p->config() failed!");
		}
		// free(prop_p);
	}
	// translator_count++;
	// translator_list.push_back(this);
	// uid_list.push_back(trep.get_translator_uid());
	// path_list.push_back(trep.get_path());
	t_uid = trep.get_translator_uid();
	// client_nds = trep.get_client();;
	mode = 0;
#if 0
	t_inst = NULL;
	d_inst = NULL;
	i_inst = NULL;
	c_inst = NULL;
#endif
}

Translator::~Translator() {
	SWDEBUGP1( 5, Verify::MODEL, "Translator::~Translator");
	SWDEBUG1( 5, Verify::TRACE, "Translator::~Translator");
#if 0
	if(tlib_handle != NULL) {
		TransformLibraryFactory tlf;
		int ret = tlf.free_handle(tlib_handle);
		if(ret) {
			// TODO - report error to log
		}
		tlib_handle = NULL;
	}
	if(dlib_handle != NULL) {
		DebugLibraryFactory dlf;
		int ret = dlf.free_handle(dlib_handle);
		if(ret) {
			// TODO - report error to log
		}
		dlib_handle = NULL;
	}
	if(ilib_handle != NULL) {
		InjectLibraryFactory ilf;
		int ret = ilf.free_handle(ilib_handle);
		if(ret) {
			// TODO - report error to log
		}
		ilib_handle = NULL;
	}
	if(clib_handle != NULL) {
		CommandLibraryFactory clf;
		int ret = clf.free_handle(clib_handle);
		if(ret) {
			// TODO - report error to log
		}
		clib_handle = NULL;
	}
#endif
}

bool operator==(const Translator& lhs, const Translator& rhs) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::operator=",
			" const TranslatorRep&i, const Translator& " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::operator=",
			" const TranslatorRep&i, const Translator& " );
	return lhs.trep == rhs.trep;
}

/*
 * Static member functions that interface with the C API calls.
 */

#if 0
// DONE
int Translator::transform_send_request( struct transform_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		t_p->mode = 0;
		ClientAPI* c_p = t_p->get_ClientAPI();
		return c_p->send_request(uid, len, message);
	}
	else {
		return -1;
	}
}
#endif

#if 0
// DONE
int Translator::inject_send_request( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		t_p->mode = 1;
		ClientAPI* c_p = t_p->get_ClientAPI();
		return c_p->send_request(uid, len, message);
	}
	else {
		return -1;
	}
}
#endif

#if 0
// replaced by InjectLibraryWrapper
// DONE
int Translator::send_inject_request( struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		// Find CommandInterface
		CommandInterface* ci_p = t_p->get_CommandInterface();
		return ci_p->send_inject_request(uid, len, message);
		// return t_p->handle_inject_request(uid, len, message);
	}
	else {
		return -1;
	}
}

// replaced by InjectLibraryWrapper
// DONE2
int Translator::send_inject_response( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		// Find the InjectInterface processing this message
		InjectInterface* ii_p = t_p->get_InjectInterface();
		return ii_p->send_inject_response(uid, len, message);
		// return t_p->handle_inject_response(uid, len, message);
	}
	else {
		return -1;
	}
}
#endif

#if 0
// DONE
int Translator::send_command_response( struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		const char *p = Translator::get_command_path(inst);
		return t_p->handle_command_response(p, len, message);
	}
	else {
		return -1;
	}
}
#endif

#if 0
int Translator::update_request( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* rep = Repository::get_repository();
	HostAPI* h_p = rep->lookup_host(uid);
	if(h_p !=  NULL) {
		return h_p->update_request(uid, len, message);
	}
	else {
		return -1;
	}
}
#endif

#if 0
// DONE
int Translator::send_response( struct transform_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* rep = Repository::get_repository();
	HostAPI* h_p = rep->lookup_host(uid);
	if(h_p !=  NULL) {
		return h_p->send_response(uid, len, message);
	}
	else {
		return -1;
	}
}
#endif

#if 0
int Translator::send_update_response( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		t_p->mode = 1;
		ClientAPI* c_p = t_p->get_ClientAPI();
		return c_p->send_update_response(uid, len, message);
	}
	else {
		return -1;
	}
}
#endif

#if 0
int Translator::logger_transform( struct transform_instance* inst, LOG_TYPE severity, const char* message ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__logger(severity, message);
	}
	else {
		return -1;
	}
}

int Translator::logger_inject( struct inject_instance* inst, LOG_TYPE severity, const char* message ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__logger(severity, message);
	}
	else {
		return -1;
	}
}

int Translator::logger_debug( struct debug_instance* inst, LOG_TYPE severity, const char* message ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__logger(severity, message);
	}
	else {
		return -1;
	}
}

int Translator::logger_command( struct command_instance* inst, LOG_TYPE severity, const char* message ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__logger(severity, message);
	}
	else {
		return -1;
	}
}
#endif

#if 0
const char* Translator::__get_path() {
	return trep.get_path();
}

const char* Translator::get_transform_path( struct transform_instance* inst ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__get_path();
	}
	else {
		return NULL;
	}
}

const char* Translator::get_debug_path( struct debug_instance* inst ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__get_path();
	}
	else {
		return NULL;
	}
}

const char* Translator::get_inject_path( struct inject_instance* inst ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__get_path();
	}
	else {
		return NULL;
	}
}

const char* Translator::get_command_path( struct command_instance* inst ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__get_path();
	}
	else {
		return NULL;
	}
}

int Translator::create_var(const char* json_message) {
	return -1;
}

const char* Translator::read_var(const char* json_message) {
	return NULL;
}

int Translator::update_var(const char* json_message) {
	return -1;
}

int Translator::delete_var(const char* json_message) {
	return -1;
}
#endif

#if 0
int Translator::send_command_request( const char* target, size_t len, uint8_t* message ) {
	if(target != __get_path()) {
		// TODO - log error
		return -1;
	}
	else {
		// return cla->handle_command_request(i_inst, len, message);
		CommandInterface* ci = get_CommandInterface();
		if(ci != NULL) {
			return -1;
		}
		else {
			return ci->handle_command_request(target, len, message);
		}
	}
}
#endif

// DONE
int Translator::handle_request( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::handle_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::handle_request",
			" uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(uid);
	std::cerr << "uid = " << uid << std::endl;
	std::cerr << "len = " << len << std::endl;
	std::cerr << "message = " << (const char*)message << std::endl;
	std::cerr << "trep.get_translator_uid() = " << trep.get_translator_uid() << std::endl;
	if(dlw_p != NULL) {
		dlw_p->handle_request(len, message);
	}
	if(tlw_p != NULL) {
		return tlw_p->handle_request(len, message);
	}
	else {
		return -1;
	}
}

// DONE
int Translator::handle_command_request( const char* target, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::handle_command_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::handle_command_request",
			" uint32_t, size_t, uint8_t* " );
	std::cerr << "Translator::handle_command_request: target = " << target << ", get_path() = " << get_path() << std::endl;
	std::cerr << "Translator::handle_command_request: strcmp(target, get_path()) = " << strcmp(target, get_path()) << std::endl;
	if(strcmp(target, get_path())) {
		// TODO - log error
		std::cerr << "Translator::handle_command_request: target does not compare!" << std::endl;
		return -1;
	}
	else {
		std::cerr << "Translator::handle_command_request: clw_p = " << clw_p << std::endl;
		std::cerr << "Translator::handle_command_request: Calling clw_p->handle_command_request()" << std::endl;
		// return cla->handle_command_request(c_inst, len, message);
		return clw_p->handle_command_request(len, message);
	}
}

#if 0
// DONE
int Translator::handle_inject_request( uint32_t uid, size_t len, uint8_t* message ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(uid);
	if(t_p != NULL) {
		return ila->handle_inject_request(i_inst, len, message);
	}
	else {
		return -1;
	}
}
#endif

#if 0
// DONE
int Translator::handle_command_response( const char* target, size_t len, uint8_t* message ) {
	if(target != __get_path()) {
		// TODO - log error
		return -1;
	}
	else {
		CommandBus* cb = CommandBus::get_command_bus();
		return cb->send_command_response(target, len, message);
	}
}
#endif

int Translator::handle_update_response( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::handle_update_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::handle_update_response",
			" uint32_t, size_t, uint8_t* " );
	Translator* t_p = __get_child_by_uid(uid);
	if(t_p == NULL) {
		// Response received from not one of the children - ERROR
		std::string err("Translator::handle_update_response() received response from a child that is not in the branch.");
		err += "\nMy uid = ";
		err += (int)get_uid();
		err += "\nChild uid = ";
		err += (int)uid;
		__logger(ERROR, err.c_str());
		return -1;
	}
	if(dlw_p != NULL) {
		dlw_p->handle_update_response(len, message);
	}
	return ilw_p->handle_update_response(len, message);
}

#if 0
int Translator::handle_inject_response( uint32_t uid, size_t len, uint8_t* message ) {
	return cla->handle_inject_response(c_inst, len, message);
}
#endif

#if 0
// DONE
int Translator::handle_response( uint32_t uid, size_t len, uint8_t* message ) {
	if(uid != trep.get_translator_uid()) {
		return -1;
	}
	if(mode == 1) { // Inject response
		return ila->handle_response(i_inst, len, message);
	}
	if(mode == 0) { // Transform response
		return tla->handle_response(t_inst, len, message);
	}
	__logger(ERROR, "Translator::handle_response incorrect mode value.");
	return -1;
	
}
#endif

ClientAPI* Translator::get_ClientAPI() {
	SWDEBUGP1( 5, Verify::MODEL, "Translator::get_ClientAPI");
	SWDEBUG1( 5, Verify::TRACE, "Translator::get_ClientAPI");
	Repository* rep = Repository::get_repository();
	ClientAPI* c_p = rep->get_ClientAPI(trep.get_client());
	return c_p;
}

HostAPI* Translator::get_HostAPI(int index) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::get_HostAPI",
			" int " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::get_HostAPI",
			" int " );
	Repository* rep = Repository::get_repository();
	HostAPI* h_p = rep->get_HostAPI(trep.get_host(index));
	return h_p;
}

#if 0
CommandInterface* Translator::get_CommandInterface() {
	Repository* rep = Repository::get_repository();
	CommandInterface* c_p = rep->get_CommandInterface(trep.get_command_interface());
	return c_p;
}

InjectInterface* Translator::get_InjectInterface() {
	Repository* rep = Repository::get_repository();
	InjectInterface* i_p = rep->get_InjectInterface(trep.get_inject_interface());
	return i_p;
}
#endif

int Translator::get_num_children() {
	SWDEBUGP1( 5, Verify::MODEL, "Translator::get_num_children");
	SWDEBUG1( 5, Verify::TRACE, "Translator::get_num_children");
	return trep.get_num_children();
}

Translator* Translator::get_child(int index) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::get_child",
			" int " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::get_child",
			" int " );
	Repository* rep = Repository::get_repository();
	int child_uid = trep.get_child(index);
	return rep->lookup_translator(child_uid);
}

#if 0
Translator* Translator::__lookup_translator(uint32_t translator_uid) {
	auto i = begin(uid_list);
	auto t = begin(translator_list);
	for(; i != end(uid_list); ++t, ++i) {
		if(*i == translator_uid) {
			return *t;
		}
	}
	return NULL;
}

HostAPI* Translator::__lookup_host(uint32_t uid) {
_	try {
		HostAPI* h_p = host_repository.at(uid);
		return h_p;
	}
	catch (const std::out_of_range& oor) {
		return NULL;
	}
}
#endif

int Translator::logger_transform( LOG_TYPE severity, const char* message ) {
	SWDEBUGP1( 5, Verify::MODEL, "Translator::logger_transform");
	SWDEBUG1( 5, Verify::TRACE, "Translator::logger_transform");
	return __logger(severity, message);
}

int Translator::logger_inject( LOG_TYPE severity, const char* message ) {
	SWDEBUGP1( 5, Verify::MODEL, "Translator::logger_inject");
	SWDEBUG1( 5, Verify::TRACE, "Translator::logger_inject");
	return __logger(severity, message);
}

int Translator::logger_debug( LOG_TYPE severity, const char* message ) {
	SWDEBUGP1( 5, Verify::MODEL, "Translator::logger_debug");
	SWDEBUG1( 5, Verify::TRACE, "Translator::logger_debug");
	return __logger(severity, message);
}

int Translator::logger_command( LOG_TYPE severity, const char* message ) {
	SWDEBUGP1( 5, Verify::MODEL, "Translator::logger_command");
	SWDEBUG1( 5, Verify::TRACE, "Translator::logger_command");
	return __logger(severity, message);
}

int Translator::__logger( LOG_TYPE severity, const char* message ) {
	Logger* logger_p = Logger::get_logger();
	return logger_p->log(severity, message);
#if 0
	if(severity == (LOG_TYPE)WARNING) {
		std::cerr << "WARNING: " << message;
		return 0;
	}
	else if(severity == (LOG_TYPE)ERROR) {
		std::cerr << "ERROR: " << message;
		return 0;
	}
	else if(severity == (LOG_TYPE)DEBUG) {
		std::cout << "DEBUG: " << message;
		return 0;
	}
	else if(severity == (LOG_TYPE)NOTICE) {
		std::cout << "NOTICE: " << message;
		return 0;
	}
	else {
		std::cerr << "UNKNOWN: " << message;
		return -1;
	}
#endif
}

// DONE
int Translator::send_response( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::send_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::send_response",
			" uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	HostAPI* h_p = rep->lookup_host(uid);
	if(h_p !=  NULL) {
		return h_p->send_response(uid, len, message);
	}
	else {
		return -1;
	}
}

// New code
int Translator::send_inject_request( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::send_inject_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::send_inject_request",
			" uint32_t, size_t, uint8_t* " );
	// Find CommandInterface
	CommandInterface* ci_p = get_CommandInterface();
	return ci_p->send_inject_request(uid, len, message);
}

int Translator::handle_inject_request( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::handle_inject_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::handle_inject_request",
			" uint32_t, size_t, uint8_t* " );
	// Send request to the InjectLibrary for processing
	// return ila->handle_inject_request(i_inst, len, message);
	if(ilw_p == NULL) { // no InjectLibrary defined
		return -1;
	}
	if(dlw_p != NULL) {
		dlw_p->handle_inject_request(len, message);
	}
	std::cerr << "ilw_p = " << ilw_p << std::endl;
	return ilw_p->handle_inject_request(len, message);
}

int Translator::send_command_response( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::send_command_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::send_command_response",
			" uint32_t, size_t, uint8_t* " );
	const char *p = get_path();
	std::cerr << "Translator::send_command_response(): path = " << p << std::endl;
	return handle_command_response(p, len, message);
}

int Translator::handle_command_response( const char* target, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::handle_command_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::handle_command_response",
			" uint32_t, size_t, uint8_t* " );
	CommandBus* cb = CommandBus::get_command_bus();
	return cb->send_command_response(target, len, message);
}

const char* Translator::get_path() {
	SWDEBUGP1( 5, Verify::MODEL, "Translator::get_path");
	SWDEBUG1( 5, Verify::TRACE, "Translator::get_path");
	return trep.get_path();
}

int Translator::inject_send_request( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::inject_send_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::inject_send_request",
			" uint32_t, size_t, uint8_t* " );
	std::cerr << "uid = " << uid << std::endl;
	std::cerr << "len = " << len << std::endl;
	std::cerr << "message = " << (const char*)message << std::endl;
	mode = 1;
	ClientAPI* c_p = get_ClientAPI();
	// std::cerr << "c_p->translator = " << c_p->get_translator() << std::endl;
	return c_p->send_request(uid, len, message);
}

int Translator::transform_send_request( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::transform_send_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::transform_send_request",
			" uint32_t, size_t, uint8_t* " );
	mode = 0;
	ClientAPI* c_p = get_ClientAPI();
	return c_p->send_request(uid, len, message);
}

int Translator::handle_response( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::handle_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::handle_response",
			" uint32_t, size_t, uint8_t* " );
	if(uid != trep.get_translator_uid()) {
		return -1;
	}
	if(dlw_p != NULL) {
		dlw_p->handle_response(len, message);
	}
	if(mode == 1) { // Inject response
		if(ilw_p != NULL) {
			return ilw_p->handle_response(len, message);
		}
		else {
			__logger(ERROR, "Translator::handle_response ilw_p is NULL.");
			return -1;
		}
	}
	if(mode == 0) { // Transform response
		if(tlw_p != NULL) {
			return tlw_p->handle_response(len, message);
		}
		else {
			__logger(ERROR, "Translator::handle_response tlw_p is NULL.");
			return -1;
		}
	}
	__logger(ERROR, "Translator::handle_response incorrect mode value.");
	return -1;
	
}

// Between InjectLibraryWrapper and InjectInterface
int Translator::send_inject_response( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::send_inject_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::send_inject_response",
			" uint32_t, size_t, uint8_t* " );
	ii_p = get_InjectInterface();
	std::cerr << "ii_p = " << (void*)ii_p << std::endl;
	if(ii_p == NULL) { // no InjectInterface defined
		return -1;
	}
	std::cerr << "Calling ii_p->send_inject_response()" << std::endl;
	return ii_p->send_inject_response(uid, len, message);
}

// Between InjectInterface and CommandLibraryWrapper
int Translator::handle_inject_response( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::handle_inject_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::handle_inject_response",
			" uint32_t, size_t, uint8_t* " );
	if(clw_p == NULL) { // no CommandLibrary defined
		return -1;
	}
	return clw_p->handle_inject_response(len, message);
}

// Between HostAPI and InjectLibraryWrapper
int Translator::handle_update_request( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::handle_update_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::handle_update_request",
			" uint32_t, size_t, uint8_t* " );
	if(ilw_p == NULL) { // no InjectLibrary defined
		return -1;
	}
	if(dlw_p != NULL) {
		dlw_p->handle_update_request(len, message);
	}
	return ilw_p->handle_update_request(len, message);
}

// Between Parent and Child in the branch
int Translator::update_request( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::update_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::update_request",
			" uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(uid);
	ClientAPI* cl_p = t_p->get_ClientAPI();
	IEEE2654Channel* ch_p = cl_p->get_Channel();
	HostAPI* h_p = ch_p->get_HostAPI();
	return h_p->update_request(uid, len, message);
}

// Between Child and Parent in the branch
int Translator::send_update_response( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::send_update_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::send_update_response",
			" uint32_t, size_t, uint8_t* " );
	// Translator* t_p = Repository::lookup_translator(uid);
	ClientAPI* cl_p = get_ClientAPI();
	return cl_p->send_update_response(uid, len, message);
}

// Between TransformLibraryWrapper and Translator/HostAPI
int Translator::send_transform_response( uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::send_transform_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::send_transform_response",
			" uint32_t, size_t, uint8_t* " );
	ii_p = get_InjectInterface();
	return ii_p->send_inject_response(uid, len, message);
}

CommandInterface* Translator::get_CommandInterface() {
	SWDEBUGP1( 5, Verify::MODEL, "Translator::get_CommandInterface");
	SWDEBUG1( 5, Verify::TRACE, "Translator::get_CommandInterface");
	if(ci_p == NULL) {
		Repository* rep_p = Repository::get_repository();
		ci_p = rep_p->get_CommandInterface(trep.get_command_interface());
	}
	return ci_p;
}

InjectInterface* Translator::get_InjectInterface() {
	SWDEBUGP1( 5, Verify::MODEL, "Translator::get_InjectInterface");
	SWDEBUG1( 5, Verify::TRACE, "Translator::get_InjectInterface");
	if(ii_p == NULL) {
		Repository* rep_p = Repository::get_repository();
		ii_p = rep_p->get_InjectInterface(trep.get_inject_interface());
	}
	return ii_p;
}

Translator* Translator::__get_child_by_uid(uint32_t uid) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::__get_child_by_uid",
			" uint32_t " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::__get_child_by_uid",
			" uint32_t " );
	Repository* rep_p = Repository::get_repository();
	int num_children = trep.get_num_children();
	int child_uid;
	for(int i = 0; i < num_children; i++) {
		child_uid = trep.get_child(i);
		Translator* t_p = rep_p->get_Translator(child_uid);
		if(t_p->get_uid() == uid) {
			return t_p;
		}
	}
	return NULL;
}

uint32_t Translator::get_uid() {
	SWDEBUGP1( 5, Verify::MODEL, "Translator::get_uid");
	SWDEBUG1( 5, Verify::TRACE, "Translator::get_uid");
	return trep.get_translator_uid();
}

const char* Translator::get_module_name() {
	SWDEBUGP1( 5, Verify::MODEL, "Translator::get_module_name");
	SWDEBUG1( 5, Verify::TRACE, "Translator::get_module_name");
	return trep.get_module_name();
}

const char* Translator::get_instance_name() {
	SWDEBUGP1( 5, Verify::MODEL, "Translator::get_instance_name");
	SWDEBUG1( 5, Verify::TRACE, "Translator::get_instance_name");
	return trep.get_instance_name();
}

void Translator::dump(size_t indent) {
	SWDEBUGP2( 5, Verify::MODEL, "Translator::dump",
			" size_t " );
	SWDEBUG2( 5, Verify::TRACE, "Translator::dump",
			" size_t " );
        std::string ind;
        indent == 0 ? ind = std::string(indent, '\t') : ind = std::string("");
        std::string ind2(indent + 1, '\t');
        std::cerr << ind << "Translator contents:" << std::endl;
        // std::cerr << ind2 << "cmd_bus = " << (void*)cmd_bus << std::endl;
        std::cerr << ind2 << "t_uid = " << t_uid << std::endl;
        std::cerr << ind2 << "mode = " << mode << std::endl;
        std::cerr << ind2 << "ttapi = " << (void*)&ttapi << std::endl;
        std::cerr << ind2 << "tiapi = " << (void*)&tiapi << std::endl;
        std::cerr << ind2 << "tdapi = " << (void*)&tdapi << std::endl;
        std::cerr << ind2 << "tcapi = " << (void*)&tcapi << std::endl;
#if 0
        std::cerr << ind2 << "tlib_handle = " << (void*)tlib_handle << std::endl;
        std::cerr << ind2 << "dlib_handle = " << (void*)dlib_handle << std::endl;
        std::cerr << ind2 << "ilib_handle = " << (void*)ilib_handle << std::endl;
        std::cerr << ind2 << "clib_handle = " << (void*)clib_handle << std::endl;
        std::cerr << ind2 << "tla = " << (void*)tla << std::endl;
        std::cerr << ind2 << "dla = " << (void*)dla << std::endl;
        std::cerr << ind2 << "ila = " << (void*)ila << std::endl;
        std::cerr << ind2 << "cla = " << (void*)cla << std::endl;
        std::cerr << ind2 << "t_inst = " << (void*)t_inst << std::endl;
        std::cerr << ind2 << "d_inst = " << (void*)d_inst << std::endl;
        std::cerr << ind2 << "i_inst = " << (void*)i_inst << std::endl;
        std::cerr << ind2 << "c_inst = " << (void*)c_inst << std::endl;
#endif
        std::cerr << ind2 << "ii_p = " << (void*)ii_p << std::endl;
        std::cerr << ind2 << "ci_p = " << (void*)ci_p << std::endl;
        std::cerr << ind2 << "tlw_p = " << (void*)tlw_p << std::endl;
        std::cerr << ind2 << "dlw_p = " << (void*)dlw_p << std::endl;
        std::cerr << ind2 << "ilw_p = " << (void*)ilw_p << std::endl;
        std::cerr << ind2 << "clw_p = " << (void*)clw_p << std::endl;
	trep.dump(indent + 1);
}

