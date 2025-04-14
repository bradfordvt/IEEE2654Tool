/*
 *    InjectLibraryWrapper.cpp
 *
 *    Wrapper code to implement the interface with the InjectLibrary.
 *
 *    Wrapper code to implement the interface with the InjectLibrary.
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
#include "wrapper/InjectLibraryWrapper.hpp"
#include "repository/Repository.hpp"
#include "log/Logger.hpp"
#include "repository/BulletinBoard.hpp"
#include "model/Translator.hpp"
#include "wrapper/ModelData.hpp"
#include "factory/InjectLibraryFactory.hpp"
#include "debug/Verify.hpp"

/*
 * Functions that interface with the C API calls.
 */

const char** InjectLibraryWrapper::get_translator_error_strings( ) {
	SWDEBUGP1( 5, Verify::WRAPPER, "InjectLibraryWrapper::get_translator_error_strings" );
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryWrapper::get_translator_error_strings" );
	return ::get_translator_error_strings_data();
}

const char** InjectLibraryWrapper::get_translator_status_strings( ) {
	SWDEBUGP1( 5, Verify::WRAPPER, "InjectLibraryWrapper::get_translator_status_strings" );
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryWrapper::get_translator_status_strings" );
	return ::get_translator_status_strings_data();
}

int InjectLibraryWrapper::send_request( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::send_request",
                        " struct inject_instance*, uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::send_request",
                        " struct inject_instance*, uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	// std::cerr << "inst = " << (void*)inst << std::endl;
	// std::cerr << "inst->translator_uid = " << inst->translator_uid << std::endl;
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	// std::cerr << "t_p = " << (void*)t_p << std::endl;
	// std::cerr << "t_p->inject_send_request = " << (void*)(t_p->inject_send_request) << std::endl;
	if(t_p != NULL) {
		return t_p->inject_send_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int InjectLibraryWrapper::update_request( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::update_request",
                        " struct inject_instance*, uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::update_request",
                        " struct inject_instance*, uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->update_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int InjectLibraryWrapper::send_update_response( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::send_update_response",
                        " struct inject_instance*, uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::send_update_response",
                        " struct inject_instance*, uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->send_update_response(uid, len, message);
	}
	else {
		return -1;
	}
}

int InjectLibraryWrapper::send_inject_response( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::send_inject_response",
                        " struct inject_instance*, uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::send_inject_response",
                        " struct inject_instance*, uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->send_inject_response(uid, len, message);
	}
	else {
		return -1;
	}
}

#if 0
int InjectLibraryWrapper::send_command_response( struct inject_instance* inst, size_t len, uint8_t* message ) {
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->send_command_response(inst->translator_uid, len, message);
	}
	else {
		return -1;
	}
}
#endif

int InjectLibraryWrapper::logger( struct inject_instance* inst, LOG_TYPE severity, const char* message ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::logger",
                        " struct inject_instance*, LOG_TYPE, const char* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::logger",
                        " struct inject_instance*, LOG_TYPE, const char* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->logger_inject(severity, message);
	}
	else {
		return -1;
	}
}

const char* InjectLibraryWrapper::get_path( struct inject_instance* inst ) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::get_path",
                        " struct inject_instance* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::get_path",
                        " struct inject_instance* " );
	Repository* rep = Repository::get_repository();
	Translator* t_p = rep->lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->get_path();
	}
	else {
		return NULL;
	}
}

int InjectLibraryWrapper::create_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::create_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::create_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->create_var(json_message);
}

const char* InjectLibraryWrapper::read_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::read_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::read_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->read_var(json_message);
}

int InjectLibraryWrapper::update_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::update_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::update_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->update_var(json_message);
}

int InjectLibraryWrapper::delete_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::delete_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::delete_var",
                        " const char* " );
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	return bb_p->delete_var(json_message);
}

/*
 * Class member functions
 */

InjectLibraryWrapper::InjectLibraryWrapper(uint32_t uid, const InjectLibraryRep& ilr) : ilrep(ilr) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::InjectLibraryWrapper",
                        " uint32_t, const InjectLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::InjectLibraryWrapper",
                        " uint32_t, const InjectLibraryRep& " );
	// std::cerr << "uid passed in = " << uid << std::endl;
	tiapi.translator = uid;
	tiapi.get_translator_error_strings = InjectLibraryWrapper::get_translator_error_strings;
	tiapi.get_translator_status_strings = InjectLibraryWrapper::get_translator_status_strings;
        tiapi.send_request = InjectLibraryWrapper::send_request;
        tiapi.update_request = InjectLibraryWrapper::send_request;
        tiapi.send_update_response = InjectLibraryWrapper::send_update_response;
        tiapi.send_inject_response = InjectLibraryWrapper::send_inject_response;
        tiapi.logger = InjectLibraryWrapper::logger;
        tiapi.get_path = InjectLibraryWrapper::get_path;
        tiapi.create_var = InjectLibraryWrapper::create_var;
        tiapi.read_var = InjectLibraryWrapper::read_var;
        tiapi.update_var = InjectLibraryWrapper::update_var;
        tiapi.delete_var = InjectLibraryWrapper::delete_var;

	Logger *lp = Logger::get_logger();
	std::string msg("InjectLibraryWrapper: ");
	msg += "uid = ";
	msg += std::to_string(uid);
	lp->log(LOG_TYPE::DEBUG, msg.c_str());
	msg = "InjectLibraryWrapper: ";
	msg += "ilrep.get_library_name() = ";
	msg += ilrep.get_library_name();
	lp->log(LOG_TYPE::DEBUG, msg.c_str());
	std::string ilname = ilrep.get_library_name();
        if(ilname.length() > 0) {
                InjectLibraryFactory ilf;
                ilib_handle = ilf.create_handle(ilname.c_str());
                if(ilib_handle) {
                        ila = ilf.get_api(ilib_handle);
			// std::cerr << "ila = " << ila << std::endl;
                        if(ila == NULL) {
                                // TODO - Print error message to logger
				Logger *l = Logger::get_logger();
				l->log(LOG_TYPE::ERROR, "InjectLibraryWrapper: ila == NULL");
				sanity = false;
                        }
			else {
				inst = ila->get_inject_instance(uid);
				if(inst == NULL) {
					Logger *l = Logger::get_logger();
					l->log(LOG_TYPE::ERROR, "InjectLibraryWrapper: inst == NULL");
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
			l->log(LOG_TYPE::ERROR, "InjectLibraryWrapper: ilib_handle == NULL");
			sanity = false;
                }
        }
        else {
		Logger *l = Logger::get_logger();
		l->log(LOG_TYPE::ERROR, "InjectLibraryWrapper: ilname.length == 0");
                ilib_handle = NULL;
		ila = NULL;
		sanity = false;
        }
}

InjectLibraryWrapper::InjectLibraryWrapper(const InjectLibraryWrapper& cr) : ila(cr.ila), inst(cr.inst), ilrep(cr.ilrep), ilib_handle(cr.ilib_handle), sanity(cr.sanity) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::InjectLibraryWrapper",
                        " const InjectLibraryWrapper& " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::InjectLibraryWrapper",
                        " const InjectLibraryWrapper& " );
	tiapi.translator = cr.tiapi.translator;
	tiapi.get_translator_error_strings = cr.tiapi.get_translator_error_strings;
	tiapi.get_translator_status_strings = cr.tiapi.get_translator_status_strings;
        tiapi.send_request = InjectLibraryWrapper::send_request;
        tiapi.update_request = InjectLibraryWrapper::update_request;
        tiapi.send_update_response = InjectLibraryWrapper::send_update_response;
        tiapi.send_inject_response = InjectLibraryWrapper::send_inject_response;
        tiapi.logger = InjectLibraryWrapper::logger;
        tiapi.get_path = InjectLibraryWrapper::get_path;
        tiapi.create_var = InjectLibraryWrapper::create_var;
        tiapi.read_var = InjectLibraryWrapper::read_var;
        tiapi.update_var = InjectLibraryWrapper::update_var;
        tiapi.delete_var = InjectLibraryWrapper::delete_var;
}

InjectLibraryWrapper::~InjectLibraryWrapper() {
	SWDEBUGP1( 5, Verify::WRAPPER, "InjectLibraryWrapper::~InjectLibraryWrapper" );
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryWrapper::~InjectLibraryWrapper" );
}

struct translator_inject_api*
InjectLibraryWrapper::get_translator_inject_api() {
	SWDEBUGP1( 5, Verify::WRAPPER, "InjectLibraryWrapper::get_translator_inject_api" );
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryWrapper::get_translator_inject_api" );
	return &tiapi;
}

bool operator==(const InjectLibraryWrapper& lhs, const InjectLibraryWrapper& rhs) {
	SWDEBUGP1( 5, Verify::WRAPPER, "InjectLibraryWrapper::operator==" );
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryWrapper::operator==" );
	return lhs.inst->translator_uid == rhs.inst->translator_uid;
}

int InjectLibraryWrapper::open() {
	SWDEBUGP1( 5, Verify::WRAPPER, "InjectLibraryWrapper::open" );
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryWrapper::open" );
	// std::cerr << "InjectLibraryWrapper::open: ila = " << ila << std::endl;
	// std::cerr << "InjectLibraryWrapper::open: inst = " << inst << std::endl;
	// std::cerr << "InjectLibraryWrapper::open: &tiapi = " << &tiapi << std::endl;
	int r = ila->open(inst, &tiapi);
	// std::cerr << "InjectLibraryWrapper::open: inst->private_data = " << (void*)(inst->private_data) << std::endl;
	return r;
	// return ila->open(inst, &tiapi);
}

int InjectLibraryWrapper::close() {
	SWDEBUGP1( 5, Verify::WRAPPER, "InjectLibraryWrapper::close" );
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryWrapper::close" );
	return ila->close(inst);
}

int InjectLibraryWrapper::config(char* json_message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::config",
                        " char* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::config",
                        " char* " );
	// std::cerr << "InjectLibraryWrapper::config: ila = " << ila << std::endl;
	// std::cerr << "InjectLibraryWrapper::config: inst = " << inst << std::endl;
	// std::cerr << "InjectLibraryWrapper::config: json_message = " << json_message << std::endl;
	// std::cerr << "InjectLibraryWrapper::config: ila->name = " << ila->name << std::endl;
	// std::cerr << "InjectLibraryWrapper::config: ila->config = " << (void*)ila->config << std::endl;
	int r = ila->config(inst, json_message);
	// std::cerr << "InjectLibraryWrapper::config: inst->private_data = " << (void*)(inst->private_data) << std::endl;
	return r;
	// return ila->config(inst, json_message);
}

int InjectLibraryWrapper::select(uint32_t index) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::select",
                        " uint32_t " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::select",
                        " uint32_t " );
	return ila->select(inst, index);
}

int InjectLibraryWrapper::deselect(uint32_t index) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::deselect",
                        " uint32_t " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::deselect",
                        " uint32_t " );
	return ila->deselect(inst, index);
}

bool InjectLibraryWrapper::is_selected(uint32_t uid) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::is_selected",
                        " uint32_t " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::is_selected",
                        " uint32_t " );
	return ila->is_selected(inst, uid);
}

translator_error_code InjectLibraryWrapper::get_error_code() {
	SWDEBUGP1( 5, Verify::WRAPPER, "InjectLibraryWrapper::get_error_code");
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryWrapper::get_error_code");
	return ila->get_error_code(inst);
}

const char* InjectLibraryWrapper::get_error_string() {
	SWDEBUGP1( 5, Verify::WRAPPER, "InjectLibraryWrapper::get_error_string");
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryWrapper::get_error_string");
	return ila->get_error_string(inst);
}

translator_status InjectLibraryWrapper::get_status_code() {
	SWDEBUGP1( 5, Verify::WRAPPER, "InjectLibraryWrapper::get_status_code");
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryWrapper::get_status_code");
	return ila->get_status_code(inst);
}

const char* InjectLibraryWrapper::get_status_string() {
	SWDEBUGP1( 5, Verify::WRAPPER, "InjectLibraryWrapper::get_status_string");
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryWrapper::get_status_string");
	return ila->get_status_string(inst);
}

int InjectLibraryWrapper::handle_request(size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::handle_request",
                        " size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::handle_request",
                        " size_t, uint8_t* " );
	// std::cerr << "ila = " << ila << std::endl;
	// std::cerr << "inst = " << inst << std::endl;
	// std::cerr << "len = " << len << std::endl;
	// std::cerr << "message = " << message << std::endl;
	return ila->handle_request(inst, len, message);
}

int InjectLibraryWrapper::handle_response(size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::handle_response",
                        " size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::handle_response",
                        " size_t, uint8_t* " );
	return ila->handle_response(inst, len, message);
}

int InjectLibraryWrapper::handle_update_request(size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::handle_update_request",
                        " size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::handle_update_request",
                        " size_t, uint8_t* " );
	// std::cerr << "ila = " << ila << std::endl;
	// std::cerr << "inst = " << inst << std::endl;
	// std::cerr << "len = " << len << std::endl;
	// std::cerr << "message = " << message << std::endl;
	return ila->handle_update_request(inst, len, message);
}

int InjectLibraryWrapper::handle_update_response(size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::WRAPPER, "InjectLibraryWrapper::handle_update_response",
                        " size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::handle_update_response",
                        " size_t, uint8_t* " );
	return ila->handle_update_response(inst, len, message);
}

int InjectLibraryWrapper::handle_inject_request(size_t len, uint8_t* message) {
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryWrapper::handle_inject_request",
			" size_t, uint8_t* ");
	// std::cerr << "ila = " << ila << std::endl;
	// std::cerr << "inst = " << inst << std::endl;
	// std::cerr << "len = " << len << std::endl;
	// std::cerr << "message = " << (const char*)message << std::endl;
	// std::cerr << "ila->name = " << ila->name << std::endl;
	// std::cerr << "ila->handle_inject_request = " << (void*)ila->handle_inject_request << std::endl;
	// std::cerr << "ila->open = " << (void*)ila->open << std::endl;
	// std::cerr << "ila->close = " << (void*)ila->close << std::endl;
	// std::cerr << "ila->config = " << (void*)ila->config << std::endl;
	// std::cerr << "inst->private_data = " << (void*)inst->private_data << std::endl;
	return ila->handle_inject_request(inst, len, message);
}

int InjectLibraryWrapper::apply() {
	SWDEBUGP1( 5, Verify::WRAPPER, "InjectLibraryWrapper::apply" );
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryWrapper::apply" );
	return ila->apply(inst);
}

bool InjectLibraryWrapper::get_sanity() {
	SWDEBUGP1( 5, Verify::WRAPPER, "InjectLibraryWrapper::get_sanity" );
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryWrapper::get_sanity" );
	return sanity;
}
