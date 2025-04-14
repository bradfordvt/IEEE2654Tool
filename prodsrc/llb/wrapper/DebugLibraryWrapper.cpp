/*
 *    DebugLibraryWrapper.cpp
 *
 *    Wrapper code to implement the interface with the DebugLibrary.
 *
 *    Wrapper code to implement the interface with the DebugLibrary.
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
#include "wrapper/DebugLibraryWrapper.hpp"
#include "repository/Repository.hpp"
#include "log/Logger.hpp"
#include "repository/BulletinBoard.hpp"
#include "model/Translator.hpp"
#include "wrapper/ModelData.hpp"
#include "factory/DebugLibraryFactory.hpp"
#include "debug/Verify.hpp"

/*
 * Functions that interface with the C API calls.
 */

const char** DebugLibraryWrapper::get_translator_error_strings( ) {
	SWDEBUGP1( 5, Verify::WRAPPER, "DebugLibraryWrapper::get_translator_error_strings" );
	SWDEBUG1( 5, Verify::TRACE, "DebugLibraryWrapper::get_translator_error_strings" );
	return ::get_translator_error_strings_data();
}

const char** DebugLibraryWrapper::get_translator_status_strings( ) {
	SWDEBUGP1( 5, Verify::WRAPPER, "DebugLibraryWrapper::get_translator_status_strings" );
	SWDEBUG1( 5, Verify::TRACE, "DebugLibraryWrapper::get_translator_status_strings" );
	return ::get_translator_status_strings_data();
}

int DebugLibraryWrapper::logger( struct debug_instance* inst, LOG_TYPE severity, const char* message ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::logger",
                        " struct debug_instance*, LOG_TYPE, const char* " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::logger",
                        " struct debug_instance*, LOG_TYPE, const char* " );
	std::cerr << "inst = " << (void*)inst << std::endl;
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	std::cerr << "t_p = " << (void*)t_p << std::endl;
	if(t_p != NULL) {
		return t_p->logger_debug(severity, message);
	}
	else {
		return -1;
	}
}

const char* DebugLibraryWrapper::get_path( struct debug_instance* inst ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::get_path",
                        " struct debug_instance* " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::get_path",
                        " struct debug_instance* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->get_path();
	}
	else {
		return NULL;
	}
}

int DebugLibraryWrapper::create_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::create_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::create_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->create_var(json_message);
}

const char* DebugLibraryWrapper::read_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::read_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::read_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->read_var(json_message);
}

int DebugLibraryWrapper::update_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::update_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::update_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->update_var(json_message);
}

int DebugLibraryWrapper::delete_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::delete_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::delete_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->delete_var(json_message);
}

/*
 * Class member functions
 */

DebugLibraryWrapper::DebugLibraryWrapper(uint32_t uid, const DebugLibraryRep& dlr) : dlrep(dlr) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::DebugLibraryWrapper",
                        " uint32_t, const DebugLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::DebugLibraryWrapper",
                        " uint32_t, const DebugLibraryRep& " );
	// std::cerr << "uid passed in = " << uid << std::endl;
	tdapi.translator = uid;
	tdapi.get_translator_error_strings = DebugLibraryWrapper::get_translator_error_strings;
	tdapi.get_translator_status_strings = DebugLibraryWrapper::get_translator_status_strings;
        tdapi.logger = DebugLibraryWrapper::logger;
        tdapi.get_path = DebugLibraryWrapper::get_path;
        tdapi.create_var = DebugLibraryWrapper::create_var;
        tdapi.read_var = DebugLibraryWrapper::read_var;
        tdapi.update_var = DebugLibraryWrapper::update_var;
        tdapi.delete_var = DebugLibraryWrapper::delete_var;

	std::string dlname = dlrep.get_library_name();
        if(dlname.length() > 0) {
                DebugLibraryFactory dlf;
                dlib_handle = dlf.create_handle(dlname.c_str());
                if(dlib_handle) {
                        dla = dlf.get_api(dlib_handle);
                        if(dla == NULL) {
                                // TODO - Print error message to logger
				Logger *l = Logger::get_logger();
                                l->log(LOG_TYPE::ERROR, "cftDebugInjectLibraryWrapper: rdila == NULL");
				sanity = false;
                        }
			else {
				inst = dla->get_debug_instance(uid);
                                if(inst == NULL) {
                                        Logger *l = Logger::get_logger();
                                        l->log(LOG_TYPE::ERROR, "DebugLibraryWrapper: inst == NULL");
                                        sanity = false;
                                }
                                else {
                                        // std::cerr << "inst = " << inst << std::endl;
                                        sanity = true;
                                }
			}
                }
                else {
                        // TODO - Print error message to logger
			Logger *l = Logger::get_logger();
                        l->log(LOG_TYPE::ERROR, "DebugLibraryWrapper: dlib_handle == NULL");
			sanity = false;
                }
        }
        else {
		Logger *l = Logger::get_logger();
                l->log(LOG_TYPE::ERROR, "DebugLibraryWrapper: dlname.length == 0");
                dlib_handle = NULL;
		dla = NULL;
		sanity = false;
        }
}

DebugLibraryWrapper::DebugLibraryWrapper(const DebugLibraryWrapper& cr) : dla(cr.dla), inst(cr.inst), dlrep(cr.dlrep), dlib_handle(cr.dlib_handle), sanity(cr.sanity) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::DebugLibraryWrapper",
                        " const DebugLibraryWrapper& " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::DebugLibraryWrapper",
                        " const DebugLibraryWrapper& " );
	tdapi.translator = cr.tdapi.translator;
	tdapi.get_translator_error_strings = cr.tdapi.get_translator_error_strings;
	tdapi.get_translator_status_strings = cr.tdapi.get_translator_status_strings;
        tdapi.logger = DebugLibraryWrapper::logger;
        tdapi.get_path = DebugLibraryWrapper::get_path;
        tdapi.create_var = DebugLibraryWrapper::create_var;
        tdapi.read_var = DebugLibraryWrapper::read_var;
        tdapi.update_var = DebugLibraryWrapper::update_var;
        tdapi.delete_var = DebugLibraryWrapper::delete_var;
}

DebugLibraryWrapper::~DebugLibraryWrapper() {
	SWDEBUGP1( 5, Verify::WRAPPER, "DebugLibraryWrapper::~DebugLibraryWrapper" );
	SWDEBUG1( 5, Verify::TRACE, "DebugLibraryWrapper::~DebugLibraryWrapper" );
}

struct translator_debug_api*
DebugLibraryWrapper::get_translator_debug_api() {
	SWDEBUGP1( 5, Verify::WRAPPER, "DebugLibraryWrapper::get_translator_debug_api" );
	SWDEBUG1( 5, Verify::TRACE, "DebugLibraryWrapper::get_translator_debug_api" );
	return &tdapi;
}

bool operator==(const DebugLibraryWrapper& lhs, const DebugLibraryWrapper& rhs) {
	SWDEBUGP1( 5, Verify::WRAPPER, "DebugLibraryWrapper::operator==" );
	SWDEBUG1( 5, Verify::TRACE, "DebugLibraryWrapper::operator==" );
	return lhs.inst->translator_uid == rhs.inst->translator_uid;
}

int DebugLibraryWrapper::open() {
	SWDEBUGP1( 5, Verify::WRAPPER, "DebugLibraryWrapper::open" );
	SWDEBUG1( 5, Verify::TRACE, "DebugLibraryWrapper::open" );
	return dla->open(inst, &tdapi);
}

int DebugLibraryWrapper::close() {
	SWDEBUGP1( 5, Verify::WRAPPER, "DebugLibraryWrapper::close" );
	SWDEBUG1( 5, Verify::TRACE, "DebugLibraryWrapper::close" );
	return dla->close(inst);
}

int DebugLibraryWrapper::config(char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::config",
                        " char* " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::config",
                        " char* " );
	return dla->config(inst, json_message);
}

int DebugLibraryWrapper::select(uint32_t index) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::select",
                        " uint32_t " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::select",
                        " uint32_t " );
	return dla->select(inst, index);
}

int DebugLibraryWrapper::deselect(uint32_t index) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::deselect",
                        " uint32_t " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::deselect",
                        " uint32_t " );
	return dla->deselect(inst, index);
}

bool DebugLibraryWrapper::is_selected(uint32_t uid) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::is_selected",
                        " uint32_t " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::is_selected",
                        " uint32_t " );
	return dla->is_selected(inst, uid);
}

translator_error_code DebugLibraryWrapper::get_error_code(translator_error_code code) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::get_error_code",
                        " translator_error_code " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::get_error_code",
                        " translator_error_code " );
	return dla->get_error_code(inst, code);
}

const char* DebugLibraryWrapper::get_error_string(translator_error_code code) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::get_error_string",
                        " translator_error_code " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::get_error_string",
                        " translator_error_code " );
	return dla->get_error_string(inst, code);
}

translator_status DebugLibraryWrapper::get_status_code(translator_status code) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::get_status_code",
                        " translator_status_code " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::get_status_code",
                        " translator_status_code " );
	return dla->get_status_code(inst, code);
}

const char* DebugLibraryWrapper::get_status_string(translator_status code) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::get_status_string",
                        " translator_status_code " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::get_status_string",
                        " translator_status_code " );
	return dla->get_status_string(inst, code);
}

int DebugLibraryWrapper::handle_request(size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::handle_request",
                        " size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::handle_request",
                        " size_t, uint8_t* " );
	return dla->handle_request(inst, len, message);
}

int DebugLibraryWrapper::handle_response(size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::handle_response",
                        " size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::handle_response",
                        " size_t, uint8_t* " );
	return dla->handle_response(inst, len, message);
}

int DebugLibraryWrapper::handle_update_request(size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::handle_update_request",
                        " size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::handle_update_request",
                        " size_t, uint8_t* " );
	return dla->handle_update_request(inst, len, message);
}

int DebugLibraryWrapper::handle_update_response(size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::handle_update_response",
                        " size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::handle_update_response",
                        " size_t, uint8_t* " );
	return dla->handle_update_response(inst, len, message);
}

int DebugLibraryWrapper::handle_inject_request(size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "DebugLibraryWrapper::handle_inject_request",
                        " size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryWrapper::handle_inject_request",
                        " size_t, uint8_t* " );
	return dla->handle_inject_request(inst, len, message);
}

int DebugLibraryWrapper::apply() {
	SWDEBUGP1( 5, Verify::WRAPPER, "DebugLibraryWrapper::apply" );
	SWDEBUG1( 5, Verify::TRACE, "DebugLibraryWrapper::apply" );
	return dla->apply(inst);
}

bool DebugLibraryWrapper::get_sanity() {
	SWDEBUGP1( 5, Verify::WRAPPER, "DebugLibraryWrapper::get_sanity" );
	SWDEBUG1( 5, Verify::TRACE, "DebugLibraryWrapper::get_sanity" );
	return sanity;
}
