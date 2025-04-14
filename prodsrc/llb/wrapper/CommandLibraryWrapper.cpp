/*
 *    CommandLibraryWrapper.cpp
 *
 *    Wrapper code to implement the interface with the CommandLibrary.
 *
 *    Wrapper code to implement the interface with the CommandLibrary.
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
static const char __date__[] = "2024/07/04";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "api/transform_library_api.h"
#include "wrapper/CommandLibraryWrapper.hpp"
#include "repository/Repository.hpp"
#include "log/Logger.hpp"
#include "repository/BulletinBoard.hpp"
#include "model/Translator.hpp"
#include "wrapper/ModelData.hpp"
#include "factory/CommandLibraryFactory.hpp"
#include "debug/Verify.hpp"

/*
 * Functions that interface with the C API calls.
 */

const char** CommandLibraryWrapper::get_translator_error_strings( ) {
	SWDEBUGP1( 5, Verify::WRAPPER, "CommandLibraryWrapper::get_translator_error_strings");
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryWrapper::get_translator_error_strings");
	return ::get_translator_error_strings_data();
}

const char** CommandLibraryWrapper::get_translator_status_strings( ) {
	SWDEBUGP1( 5, Verify::WRAPPER, "CommandLibraryWrapper::get_translator_status_strings");
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryWrapper::get_translator_status_strings");
	return ::get_translator_status_strings_data();
}

int CommandLibraryWrapper::send_inject_request( struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "CommandLibraryWrapper::send_inject_request",
                        " struct command_instance*, uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryWrapper::send_inject_request",
                        " struct command_instance*, uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->send_inject_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int CommandLibraryWrapper::send_command_response( struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "CommandLibraryWrapper::send_command_response",
                        " struct command_instance*, uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryWrapper::send_command_response",
                        " struct command_instance*, uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->send_command_response(uid, len, message);
	}
	else {
		return -1;
	}
}

int CommandLibraryWrapper::logger( struct command_instance* inst, LOG_TYPE severity, const char* message ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "CommandLibraryWrapper::logger",
                        " struct command_instance*, LOG_TYPE, const char* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryWrapper::logger",
                        " struct command_instance*, LOG_TYPE, const char* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->logger_command(severity, message);
	}
	else {
		return -1;
	}
}

const char* CommandLibraryWrapper::get_path( struct command_instance* inst ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "CommandLibraryWrapper::get_path",
                        " struct command_instance* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryWrapper::get_path",
                        " struct command_instance* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->get_path();
	}
	else {
		return NULL;
	}
}

int CommandLibraryWrapper::create_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "CommandLibraryWrapper::create_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryWrapper::create_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->create_var(json_message);
}

const char* CommandLibraryWrapper::read_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "CommandLibraryWrapper::read_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryWrapper::read_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->read_var(json_message);
}

int CommandLibraryWrapper::update_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "CommandLibraryWrapper::update_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryWrapper::update_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->update_var(json_message);
}

int CommandLibraryWrapper::delete_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "CommandLibraryWrapper::delete_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryWrapper::delete_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->delete_var(json_message);
}

/*
 * Class member functions
 */

CommandLibraryWrapper::CommandLibraryWrapper(uint32_t uid, const CommandLibraryRep& clr) : clrep(clr) {
	SWDEBUGP2( 5, Verify::WRAPPER, "CommandLibraryWrapper::CommandLibraryWrapper",
                        " uint32_t, const CommandLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryWrapper::CommandLibraryWrapper",
                        " uint32_t, const CommandLibraryRep& " );
	// std::cerr << "uid passed in = " << uid << std::endl;
	tcapi.translator = uid;
	tcapi.get_translator_error_strings = CommandLibraryWrapper::get_translator_error_strings;
	tcapi.get_translator_status_strings = CommandLibraryWrapper::get_translator_status_strings;
        tcapi.send_inject_request = CommandLibraryWrapper::send_inject_request;
        tcapi.send_command_response = CommandLibraryWrapper::send_command_response;
        tcapi.logger = CommandLibraryWrapper::logger;
        tcapi.get_path = CommandLibraryWrapper::get_path;
        tcapi.create_var = CommandLibraryWrapper::create_var;
        tcapi.read_var = CommandLibraryWrapper::read_var;
        tcapi.update_var = CommandLibraryWrapper::update_var;
        tcapi.delete_var = CommandLibraryWrapper::delete_var;

	Logger *lp = Logger::get_logger();
	std::string msg("CommandLibraryWrapper: ");
	msg += "uid = ";
	msg += std::to_string(uid);
	lp->log(LOG_TYPE::DEBUG, msg.c_str());
	msg = "CommandLibraryWrapper: ";
	msg += "clrep.get_library_name() = ";
	msg += clrep.get_library_name();
	lp->log(LOG_TYPE::DEBUG, msg.c_str());
	std::string clname = clrep.get_library_name();
        if(clname.length() > 0) {
                CommandLibraryFactory clf;
                clib_handle = clf.create_handle(clname.c_str());
                if(clib_handle) {
                        cla = clf.get_api(clib_handle);
			// std::cerr << "cla = " << cla << std::endl;
                        if(cla == NULL) {
                                // TODO - Print error message to logger
				Logger *l = Logger::get_logger();
				l->log(LOG_TYPE::ERROR, "CommandLibraryWrapper: cla == NULL");
				sanity = false;
                        }
			else {
				c_inst = cla->get_command_instance(uid);
				if(c_inst == NULL) {
					Logger *l = Logger::get_logger();
					l->log(LOG_TYPE::ERROR, "CommandLibraryWrapper: c_inst == NULL");
					sanity = false;
				}
				else {
					// std::cerr << "c_inst = " << c_inst << std::endl;
					sanity = true;
				}
			}
                }
                else {
                        // TODO - Print error message to logger
			Logger *l = Logger::get_logger();
			l->log(LOG_TYPE::ERROR, "CommandLibraryWrapper: clib_handle == NULL");
			sanity = false;
                }
        }
        else {
		Logger *l = Logger::get_logger();
		l->log(LOG_TYPE::ERROR, "CommandLibraryWrapper: clname.length == 0");
                clib_handle = NULL;
		cla = NULL;
		sanity = false;
        }
}

CommandLibraryWrapper::CommandLibraryWrapper(const CommandLibraryWrapper& cr) : cla(cr.cla), c_inst(cr.c_inst), clrep(cr.clrep), clib_handle(cr.clib_handle), sanity(cr.sanity) {
	SWDEBUGP2( 5, Verify::WRAPPER, "CommandLibraryWrapper::CommandLibraryWrapper",
                        " const CommandLibraryWrapper& " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryWrapper::CommandLibraryWrapper",
                        " const CommandLibraryWrapper& " );
	tcapi.translator = cr.tcapi.translator;
	tcapi.get_translator_error_strings = cr.tcapi.get_translator_error_strings;
	tcapi.get_translator_status_strings = cr.tcapi.get_translator_status_strings;
        tcapi.send_inject_request = CommandLibraryWrapper::send_inject_request;
        tcapi.send_command_response = CommandLibraryWrapper::send_command_response;
        tcapi.logger = CommandLibraryWrapper::logger;
        tcapi.get_path = CommandLibraryWrapper::get_path;
        tcapi.create_var = CommandLibraryWrapper::create_var;
        tcapi.read_var = CommandLibraryWrapper::read_var;
        tcapi.update_var = CommandLibraryWrapper::update_var;
        tcapi.delete_var = CommandLibraryWrapper::delete_var;
}

CommandLibraryWrapper::~CommandLibraryWrapper() {
	SWDEBUGP1( 5, Verify::WRAPPER, "CommandLibraryWrapper::~CommandLibraryWrapper");
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryWrapper::~CommandLibraryWrapper");
}

struct translator_command_api*
CommandLibraryWrapper::get_translator_command_api() {
	SWDEBUGP1( 5, Verify::WRAPPER, "CommandLibraryWrapper::get_translator_command_api" );
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryWrapper::get_translator_command_api" );
	return &tcapi;
}

bool operator==(const CommandLibraryWrapper& lhs, const CommandLibraryWrapper& rhs) {
	SWDEBUGP1( 5, Verify::WRAPPER, "CommandLibraryWrapper::operator==" );
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryWrapper::operator==" );
	return lhs.c_inst->translator_uid == rhs.c_inst->translator_uid;
}

int CommandLibraryWrapper::open() {
	SWDEBUGP1( 5, Verify::WRAPPER, "CommandLibraryWrapper::open" );
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryWrapper::open" );
	// std::cerr << "CommandLibraryWrapper::open: cla = " << cla << std::endl;
	// std::cerr << "CommandLibraryWrapper::open: c_inst = " << c_inst << std::endl;
	// std::cerr << "CommandLibraryWrapper::open: &tcapi = " << &tcapi << std::endl;
	return cla->open(c_inst, &tcapi);
}

int CommandLibraryWrapper::close() {
	SWDEBUGP1( 5, Verify::WRAPPER, "CommandLibraryWrapper::close" );
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryWrapper::close" );
	return cla->close(c_inst);
}

int CommandLibraryWrapper::config(char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "CommandLibraryWrapper::config",
                        " char* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryWrapper::config",
                        " char* " );
	// std::cerr << "CommandLibraryWrapper::config: cla = " << cla << std::endl;
	// std::cerr << "CommandLibraryWrapper::config: c_inst = " << c_inst << std::endl;
	// std::cerr << "CommandLibraryWrapper::config: json_message = " << json_message << std::endl;
	return cla->config(c_inst, json_message);
}

translator_error_code CommandLibraryWrapper::get_error_code() {
	SWDEBUGP1( 5, Verify::WRAPPER, "CommandLibraryWrapper::get_error_code" );
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryWrapper::get_error_code" );
	return cla->get_error_code(c_inst);
}

const char* CommandLibraryWrapper::get_error_string() {
	SWDEBUGP1( 5, Verify::WRAPPER, "CommandLibraryWrapper::get_error_string" );
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryWrapper::get_error_string" );
	return cla->get_error_string(c_inst);
}

translator_status CommandLibraryWrapper::get_status_code() {
	SWDEBUGP1( 5, Verify::WRAPPER, "CommandLibraryWrapper::get_status_code" );
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryWrapper::get_status_code" );
	return cla->get_status_code(c_inst);
}

const char* CommandLibraryWrapper::get_status_string() {
	SWDEBUGP1( 5, Verify::WRAPPER, "CommandLibraryWrapper::get_status_string" );
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryWrapper::get_status_string" );
	return cla->get_status_string(c_inst);
}

int CommandLibraryWrapper::handle_command_request(size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "CommandLibraryWrapper::handle_command_request",
                        " size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryWrapper::handle_command_request",
                        " size_t, uint8_t* " );
	// std::cerr << "cla = " << cla << std::endl;
	// std::cerr << "c_inst = " << c_inst << std::endl;
	// std::cerr << "len = " << len << std::endl;
	// std::cerr << "message = " << message << std::endl;
	return cla->handle_command_request(c_inst, len, message);
}

// From InjectInterface (via Translator) to CommandLibrary
int CommandLibraryWrapper::handle_inject_response(size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "CommandLibraryWrapper::handle_inject_response",
                        " size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryWrapper::handle_inject_response",
                        " size_t, uint8_t* " );
	return cla->handle_inject_response(c_inst, len, message);
}

int CommandLibraryWrapper::apply() {
	SWDEBUGP1( 5, Verify::WRAPPER, "CommandLibraryWrapper::apply" );
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryWrapper::apply" );
	return cla->apply(c_inst);
}

bool CommandLibraryWrapper::get_sanity() {
	SWDEBUGP1( 5, Verify::WRAPPER, "CommandLibraryWrapper::get_sanity" );
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryWrapper::get_sanity" );
	return sanity;
}
