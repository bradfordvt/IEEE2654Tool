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

#include "model/Translator.hpp"
#include "bus/CommandBus.hpp"

#include "factory/TransformLibraryFactory.hpp"
#include "factory/DebugLibraryFactory.hpp"
#include "factory/InjectLibraryFactory.hpp"
#include "factory/CommandLibraryFactory.hpp"

uint32_t Translator::translator_count = 0;
CommandBus* Translator::cmd_bus = NULL;
std::vector<Translator*> Translator::translator_list;
std::vector<uint32_t> Translator::uid_list;
std::vector<const char*> Translator::path_list;


Translator* Translator::find_translator_by_uid(uint32_t uid) {
	auto u = begin(Translator::uid_list);
	auto t = begin(Translator::translator_list);
	for( ; u != end(Translator::uid_list); ++t, ++u ) {
		if(*u == uid) {
			return *t;
		}
	}
	return NULL;
}

Translator* Translator::find_translator_by_path(const char* path) {
	auto p = begin(Translator::path_list);
	auto t = begin(Translator::translator_list);
	for( ; p != end(Translator::path_list); ++p, ++t ) {
		if(!strcmp(*p, path)) {
			return *t;
		}
	}
	return NULL;
}

Translator::Translator(const char* path, const char* tlibbase, const char* dlibbase, const char* ilibbase, const char* clibbase) {
	if(tlibbase) {
		TransformLibraryFactory tlf;
		tlib_handle = tlf.create_handle(tlibbase);
		if(tlib_handle) {
			tla = tlf.get_api(tlib_handle);
			if(tla == NULL) {
				// TODO - Print error message to logger
			}
		}
		else {
			// TODO - Print error message to logger
		}
	}
	else {
		tlib_handle = NULL;
	}
	if(dlibbase) {
		DebugLibraryFactory dlf;
		dlib_handle = dlf.create_handle(dlibbase);
		if(dlib_handle) {
			dla = dlf.get_api(dlib_handle);
			if(dla == NULL) {
				// TODO - Print error message to logger
			}
		}
		else {
			// TODO - Print error message to logger
		}
	}
	else {
		dlib_handle = NULL;
	}
	if(ilibbase) {
		InjectLibraryFactory ilf;
		ilib_handle = ilf.create_handle(ilibbase);
		if(ilib_handle) {
			ila = ilf.get_api(ilib_handle);
			if(ila == NULL) {
				// TODO - Print error message to logger
			}
		}
		else {
			// TODO - Print error message to logger
		}
	}
	else {
		ilib_handle = NULL;
	}
	if(clibbase) {
		CommandLibraryFactory clf;
		clib_handle = clf.create_handle(clibbase);
		if(clib_handle) {
			cla = clf.get_api(clib_handle);
			if(cla == NULL) {
				// TODO - Print error message to logger
			}
		}
		else {
			// TODO - Print error message to logger
		}
	}
	else {
		clib_handle = NULL;
	}
	translator_count++;
	translator_list.push_back(this);
	uid_list.push_back(translator_count);
	path_list.push_back(path);
	t_uid = translator_count;
	client_p = NULL;
	mode = 0;
	t_inst = NULL;
	d_inst = NULL;
	i_inst = NULL;
	c_inst = NULL;

	ttapi.translator = t_uid;
	ttapi.send_request = Translator::transform_send_request;
	ttapi.send_response = Translator::send_response;
	ttapi.logger = Translator::logger_transform;
	ttapi.get_path = Translator::get_transform_path;
	ttapi.create_var = Translator::create_var;
	ttapi.read_var = Translator::read_var;
	ttapi.update_var = Translator::update_var;
	ttapi.delete_var = Translator::delete_var;

	tdapi.translator = t_uid;
	tdapi.logger = Translator::logger_debug;
	tdapi.get_path = Translator::get_debug_path;
	tdapi.create_var = Translator::create_var;
	tdapi.read_var = Translator::read_var;
	tdapi.update_var = Translator::update_var;
	tdapi.delete_var = Translator::delete_var;

	tiapi.translator = t_uid;
	tiapi.send_request = Translator::inject_send_request;
	tiapi.update_request = Translator::update_request;
	tiapi.send_update_response = Translator::send_update_response;
	tiapi.send_inject_response = Translator::send_inject_response;
	tiapi.logger = Translator::logger_inject;
	tiapi.get_path = Translator::get_inject_path;
	tiapi.create_var = Translator::create_var;
	tiapi.read_var = Translator::read_var;
	tiapi.update_var = Translator::update_var;
	tiapi.delete_var = Translator::delete_var;

	tcapi.translator = t_uid;
	tcapi.send_inject_request = Translator::send_inject_request;
	tcapi.send_command_response = Translator::send_command_response;
	tcapi.logger = Translator::logger_command;
	tcapi.get_path = Translator::get_command_path;
	tcapi.create_var = Translator::create_var;
	tcapi.read_var = Translator::read_var;
	tcapi.update_var = Translator::update_var;
	tcapi.delete_var = Translator::delete_var;


}

int Translator::set_client(uint32_t uid, ClientAPI& client) {
	client_p = &client;
	return 0;
}

int Translator::add_host(uint32_t uid, HostAPI& host) {
	host_repository[uid] = &host;
	return 0;
}

int Translator::transform_send_request( struct transform_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		t_p->mode = 0;
		ClientAPI* c_p = t_p->client_p;
		return c_p->send_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int Translator::inject_send_request( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		t_p->mode = 1;
		ClientAPI* c_p = t_p->client_p;
		return c_p->send_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int Translator::send_inject_request( struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->handle_inject_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int Translator::send_inject_response( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->handle_inject_response(uid, len, message);
	}
	else {
		return -1;
	}
}

int Translator::send_command_response( struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		auto p = begin(Translator::path_list);
		auto u = begin(Translator::uid_list);
		for( ; u != end(Translator::uid_list); ++p, ++u ) {
			if(*u == inst->translator_uid) {
				return t_p->handle_command_response(*p, len, message);
			}
		}
		return -1;
	}
	else {
		return -1;
	}
}

int Translator::update_request( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		HostAPI* h_p = t_p->__lookup_host(uid);
		if(h_p !=  NULL) {
			return h_p->update_request(uid, len, message);
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

int Translator::send_response( struct transform_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		HostAPI* h_p = t_p->__lookup_host(uid);
		if(h_p !=  NULL) {
			return h_p->send_response(uid, len, message);
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

int Translator::send_update_response( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		t_p->mode = 1;
		ClientAPI* c_p = t_p->client_p;
		return c_p->send_update_response(uid, len, message);
	}
	else {
		return -1;
	}
}

int Translator::logger_transform( struct transform_instance* inst, log_severity severity, const char* message ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__logger(severity, message);
	}
	else {
		return -1;
	}
}

int Translator::logger_inject( struct inject_instance* inst, log_severity severity, const char* message ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__logger(severity, message);
	}
	else {
		return -1;
	}
}

int Translator::logger_debug( struct debug_instance* inst, log_severity severity, const char* message ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__logger(severity, message);
	}
	else {
		return -1;
	}
}

int Translator::logger_command( struct command_instance* inst, log_severity severity, const char* message ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__logger(severity, message);
	}
	else {
		return -1;
	}
}

const char* Translator::__get_path() {
	auto u = begin(Translator::uid_list);
	auto p = begin(Translator::path_list);
	for( ; u != end(Translator::uid_list); ++p, ++u ) {
		if(*u == t_uid) {
			return *p;
		}
	}
	return NULL;
}

const char* Translator::get_transform_path( struct transform_instance* inst ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__get_path();
	}
	else {
		return NULL;
	}
}

const char* Translator::get_debug_path( struct debug_instance* inst ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__get_path();
	}
	else {
		return NULL;
	}
}

const char* Translator::get_inject_path( struct inject_instance* inst ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__get_path();
	}
	else {
		return NULL;
	}
}

const char* Translator::get_command_path( struct command_instance* inst ) {
	Translator* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__get_path();
	}
	else {
		return NULL;
	}
}

int Translator::create_var( const char* json_message ) {
	return 0;
}

const char* Translator::read_var( const char* json_message ) {
	return "";
}

int Translator::update_var( const char* json_message ) {
	return 0;
}

int Translator::delete_var( const char* json_message ) {
	return 0;
}

int Translator::handle_request( uint32_t uid, size_t len, uint8_t* message ) {
	return tla->handle_request(t_inst, len, message);
}

int Translator::handle_inject_request( uint32_t uid, size_t len, uint8_t* message ) {
	return ila->handle_inject_request(i_inst, len, message);
}

int Translator::handle_update_request( uint32_t uid, size_t len, uint8_t* message ) {
	return ila->handle_update_request(i_inst, len, message);
}

int Translator::handle_response( uint32_t uid, size_t len, uint8_t* message ) {
	if(mode == 0) {
		return tla->handle_response(t_inst, len, message);
	}
	else if(mode == 1) {
		return ila->handle_response(i_inst, len, message);
	}
	else {
		return -1;
	}
}

int Translator::handle_update_response( uint32_t uid, size_t len, uint8_t* message ) {
	return ila->handle_update_response(i_inst, len, message);
}

int Translator::handle_inject_response( uint32_t uid, size_t len, uint8_t* message ) {
	return cla->handle_inject_response(c_inst, len, message);
}

int Translator::handle_command_response( const char* target, size_t len, uint8_t* message ) {
	cmd_bus = CommandBus::get_command_bus();
	return cmd_bus->handle_command_response(target, len, message);
}

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
	try {
		HostAPI* h_p = host_repository.at(uid);
		return h_p;
	}
	catch (const std::out_of_range& oor) {
		return NULL;
	}
}

int Translator::__logger( log_severity severity, const char* message ) {
	if(severity == FATAL) {
		std::cerr << "FATAL: " << message;
		return 0;
	}
	else if(severity == ERROR) {
		std::cerr << "ERROR: " << message;
		return 0;
	}
	else if(severity == DEBUG) {
		std::cout << "DEBUG: " << message;
		return 0;
	}
	else if(severity == INFO) {
		std::cout << "INFO: " << message;
		return 0;
	}
	else {
		std::cerr << "UNKNOWN: " << message;
		return -1;
	}
}
