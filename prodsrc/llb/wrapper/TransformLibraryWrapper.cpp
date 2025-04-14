/*
 *    TransformLibraryWrapper.cpp
 *
 *    Wrapper code to implement the interface with the TransformLibrary.
 *
 *    Wrapper code to implement the interface with the TransformLibrary.
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
#include "wrapper/TransformLibraryWrapper.hpp"
#include "repository/Repository.hpp"
#include "log/Logger.hpp"
#include "repository/BulletinBoard.hpp"
#include "model/Translator.hpp"
#include "wrapper/ModelData.hpp"
#include "factory/TransformLibraryFactory.hpp"
#include "debug/Verify.hpp"

/*
 * Functions that interface with the C API calls.
 */

const char** TransformLibraryWrapper::get_translator_error_strings( ) {
	SWDEBUGP1( 5, Verify::WRAPPER, "TransformLibraryWrapper::get_translator_error_strings" );
	SWDEBUG1( 5, Verify::TRACE, "TransformLibraryWrapper::get_translator_error_strings" );
	return ::get_translator_error_strings_data();
}

const char** TransformLibraryWrapper::get_translator_status_strings( ) {
	SWDEBUGP1( 5, Verify::WRAPPER, "TransformLibraryWrapper::get_translator_status_strings" );
	SWDEBUG1( 5, Verify::TRACE, "TransformLibraryWrapper::get_translator_status_strings" );
	return ::get_translator_status_strings_data();
}

int TransformLibraryWrapper::send_request( struct transform_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::send_request",
                        " struct transform_instance*, uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::send_request",
                        " struct transform_instance*, uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->transform_send_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int TransformLibraryWrapper::send_response( struct transform_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::send_response",
                        " struct transform_instance*, uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::send_response",
                        " struct transform_instance*, uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		// return t_p->send_transform_response(uid, len, message);
		return t_p->send_response(uid, len, message);
	}
	else {
		return -1;
	}
}

int TransformLibraryWrapper::logger( struct transform_instance* inst, LOG_TYPE severity, const char* message ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::logger",
                        " struct transform_instance*, LOG_TYPE, const char* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::logger",
                        " struct transform_instance*, LOG_TYPE, const char* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->logger_transform(severity, message);
	}
	else {
		return -1;
	}
}

const char* TransformLibraryWrapper::get_path( struct transform_instance* inst ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::get_path",
                        " struct transform_instance* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::get_path",
                        " struct transform_instance* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->get_path();
	}
	else {
		return NULL;
	}
}

int TransformLibraryWrapper::create_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::create_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::create_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->create_var(json_message);
}

const char* TransformLibraryWrapper::read_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::read_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::read_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->read_var(json_message);
}

int TransformLibraryWrapper::update_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::update_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::update_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->update_var(json_message);
}

int TransformLibraryWrapper::delete_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::delete_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::delete_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->delete_var(json_message);
}

/*
 * Class member functions
 */

TransformLibraryWrapper::TransformLibraryWrapper(uint32_t uid, const TransformLibraryRep& tlr) : tlrep(tlr) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::TransformLibraryWrapper",
                        " uint32_t, const TransformLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::TransformLibraryWrapper",
                        " uint32_t, const TransformLibraryRep& " );
	// std::cerr << "uid passed in = " << uid << std::endl;
	ttapi.translator = uid;
	ttapi.get_translator_error_strings = TransformLibraryWrapper::get_translator_error_strings;
	ttapi.get_translator_status_strings = TransformLibraryWrapper::get_translator_status_strings;
        ttapi.send_request = TransformLibraryWrapper::send_request;
        ttapi.send_response = TransformLibraryWrapper::send_response;
        ttapi.logger = TransformLibraryWrapper::logger;
        ttapi.get_path = TransformLibraryWrapper::get_path;
        ttapi.create_var = TransformLibraryWrapper::create_var;
        ttapi.read_var = TransformLibraryWrapper::read_var;
        ttapi.update_var = TransformLibraryWrapper::update_var;
        ttapi.delete_var = TransformLibraryWrapper::delete_var;

	std::string tlname = tlrep.get_library_name();
        if(tlname.length() > 0) {
                TransformLibraryFactory tlf;
                tlib_handle = tlf.create_handle(tlname.c_str());
                if(tlib_handle) {
                        tla = tlf.get_api(tlib_handle);
                        if(tla == NULL) {
                                // TODO - Print error message to logger
				Logger *l = Logger::get_logger();
                                l->log(LOG_TYPE::ERROR, "TransformLibraryWrapper: tla == NULL");
				sanity = false;
                        }
			else {
				inst = tla->get_transform_instance(uid);
                                if(inst == NULL) {
                                        Logger *l = Logger::get_logger();
                                        l->log(LOG_TYPE::ERROR, "TransformLibraryWrapper: inst == NULL");
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
                        l->log(LOG_TYPE::ERROR, "TransformLibraryWrapper: tlib_handle == NULL");
			sanity = false;
                }
        }
        else {
		Logger *l = Logger::get_logger();
                l->log(LOG_TYPE::ERROR, "TransformLibraryWrapper: tlname.length == 0");
                tlib_handle = NULL;
		tla = NULL;
		sanity = false;
        }
}

TransformLibraryWrapper::TransformLibraryWrapper(const TransformLibraryWrapper& cr) : tla(cr.tla), inst(cr.inst), tlrep(cr.tlrep), tlib_handle(cr.tlib_handle), sanity(cr.sanity) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::TransformLibraryWrapper",
                        " const TransformLibraryWrapper& " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::TransformLibraryWrapper",
                        " const TransformLibraryWrapper& " );
	ttapi.translator = cr.ttapi.translator;
	ttapi.get_translator_error_strings = cr.ttapi.get_translator_error_strings;
	ttapi.get_translator_status_strings = cr.ttapi.get_translator_status_strings;
        ttapi.send_request = TransformLibraryWrapper::send_request;
        ttapi.send_response = TransformLibraryWrapper::send_response;
        ttapi.logger = TransformLibraryWrapper::logger;
        ttapi.get_path = TransformLibraryWrapper::get_path;
        ttapi.create_var = TransformLibraryWrapper::create_var;
        ttapi.read_var = TransformLibraryWrapper::read_var;
        ttapi.update_var = TransformLibraryWrapper::update_var;
        ttapi.delete_var = TransformLibraryWrapper::delete_var;
}

TransformLibraryWrapper::~TransformLibraryWrapper() {
	SWDEBUGP1( 5, Verify::WRAPPER, "TransformLibraryWrapper::~TransformLibraryWrapper" );
	SWDEBUG1( 5, Verify::TRACE, "TransformLibraryWrapper::~TransformLibraryWrapper" );
}

struct translator_transform_api*
TransformLibraryWrapper::get_translator_transform_api() {
	SWDEBUGP1( 5, Verify::WRAPPER, "TransformLibraryWrapper::get_translator_transform_api" );
	SWDEBUG1( 5, Verify::TRACE, "TransformLibraryWrapper::get_translator_transform_api" );
	return &ttapi;
}

bool operator==(const TransformLibraryWrapper& lhs, const TransformLibraryWrapper& rhs) {
	SWDEBUGP1( 5, Verify::WRAPPER, "TransformLibraryWrapper::operator==" );
	SWDEBUG1( 5, Verify::TRACE, "TransformLibraryWrapper::operator==" );
	return lhs.inst->translator_uid == rhs.inst->translator_uid;
}

int TransformLibraryWrapper::open() {
	SWDEBUGP1( 5, Verify::WRAPPER, "TransformLibraryWrapper::open" );
	SWDEBUG1( 5, Verify::TRACE, "TransformLibraryWrapper::open" );
	// std::cerr << "inst = " << (void*)inst << std::endl;
	// std::cerr << "&ttapi = " << (void*)&ttapi << std::endl;
	// std::cerr << "tla = " << (void*)tla << std::endl;
	// std::cerr << "tla->name = " << tla->name << std::endl;
	return tla->open(inst, &ttapi);
}

int TransformLibraryWrapper::close() {
	SWDEBUGP1( 5, Verify::WRAPPER, "TransformLibraryWrapper::open" );
	SWDEBUG1( 5, Verify::TRACE, "TransformLibraryWrapper::open" );
	return tla->close(inst);
}

int TransformLibraryWrapper::config(char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::config",
                        " char* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::config",
                        " char* " );
	// std::cerr << "json_message = " << json_message << std::endl;
	// std::cerr << "inst = " << (void*)inst << std::endl;
	// std::cerr << "tla = " << (void*)tla << std::endl;
	// std::cerr << "tla->name = " << tla->name << std::endl;
	return tla->config(inst, json_message);
}

int TransformLibraryWrapper::select(uint32_t index) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::select",
                        " uint32_t " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::select",
                        " uint32_t " );
	return tla->select(inst, index);
}

int TransformLibraryWrapper::deselect(uint32_t index) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::deselect",
                        " uint32_t " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::deselect",
                        " uint32_t " );
	return tla->deselect(inst, index);
}

bool TransformLibraryWrapper::is_selected(uint32_t uid) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::is_selected",
                        " uint32_t " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::is_selected",
                        " uint32_t " );
	return tla->is_selected(inst, uid);
}

translator_error_code TransformLibraryWrapper::get_error_code() {
	SWDEBUGP1( 5, Verify::WRAPPER, "TransformLibraryWrapper::get_error_code" );
	SWDEBUG1( 5, Verify::TRACE, "TransformLibraryWrapper::get_error_code" );
	return tla->get_error_code(inst);
}

const char* TransformLibraryWrapper::get_error_string() {
	SWDEBUGP1( 5, Verify::WRAPPER, "TransformLibraryWrapper::get_error_string" );
	SWDEBUG1( 5, Verify::TRACE, "TransformLibraryWrapper::get_error_string" );
	return tla->get_error_string(inst);
}

translator_status TransformLibraryWrapper::get_status_code() {
	SWDEBUGP1( 5, Verify::WRAPPER, "TransformLibraryWrapper::get_status_code" );
	SWDEBUG1( 5, Verify::TRACE, "TransformLibraryWrapper::get_status_code" );
	return tla->get_status_code(inst);
}

const char* TransformLibraryWrapper::get_status_string() {
	SWDEBUGP1( 5, Verify::WRAPPER, "TransformLibraryWrapper::get_status_string" );
	SWDEBUG1( 5, Verify::TRACE, "TransformLibraryWrapper::get_status_string" );
	return tla->get_status_string(inst);
}

int TransformLibraryWrapper::handle_request(size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::handle_request",
                        " size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::handle_request",
                        " size_t, uint8_t* " );
	return tla->handle_request(inst, len, message);
}

int TransformLibraryWrapper::handle_response(size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "TransformLibraryWrapper::handle_response",
                        " size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryWrapper::handle_response",
                        " size_t, uint8_t* " );
	return tla->handle_response(inst, len, message);
}

int TransformLibraryWrapper::apply() {
	SWDEBUGP1( 5, Verify::WRAPPER, "TransformLibraryWrapper::apply" );
	SWDEBUG1( 5, Verify::TRACE, "TransformLibraryWrapper::apply" );
	return tla->apply(inst);
}

bool TransformLibraryWrapper::get_sanity() {
	SWDEBUGP1( 5, Verify::WRAPPER, "TransformLibraryWrapper::sanity" );
	SWDEBUG1( 5, Verify::TRACE, "TransformLibraryWrapper::sanity" );
	return sanity;
}
