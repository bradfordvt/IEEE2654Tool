/*
 *    Translator.hpp
 *
 *    Class to implement the Translator architectural element.
 *
 *    Class to implement the Translator architectural element.
 *    The class implements the Translator element of the message
 *    layer.  It implements the node of the IEEE2654Tree model.
 *    It also implements the API functions the TransformLibrary,
 *    DebufLibrary, InjectLibrary, and CommandLibrary libraries
 *    call when communicating with the IEEE2654 Tool application.
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

#ifndef INCLUDE_MODEL_TRANSLATOR_HPP_
#define INCLUDE_MODEL_TRANSLATOR_HPP_

#include <map>
#include <vector>

#include "api/translator_api.h"
#include "api/transform_library_api.h"
#include "api/debug_library_api.h"
#include "api/inject_library_api.h"
#include "api/command_library_api.h"
// #include "channel/ClientAPI.hpp"
// #include "channel/HostAPI.hpp"
// #include "bus/CommandBus.hpp"
// #include "bus/CommandInterface.hpp"
// #include "bus/InjectInterface.hpp"

#include "parser/TranslatorRep.hpp"

#include "wrapper/TransformLibraryWrapper.hpp"
#include "wrapper/DebugLibraryWrapper.hpp"
#include "wrapper/InjectLibraryWrapper.hpp"
#include "wrapper/CommandLibraryWrapper.hpp"

class ClientAPI;
class HostAPI;
class CommandBus;
class CommandInterface;
class InjectInterface;
class TransformLibraryWrapper;
class DebugLibraryWrapper;
class InjectLibraryWrapper;
class CommandLibraryWrapper;


class Translator {
#ifdef TEST
	friend class Translator_TestCases;
#endif
public:
	Translator(const TranslatorRep& tr);
	// Translator(const char* path, const char* tlibbase, const char* dlibbase, const char* ilibbase, const char* clibbase);
	~Translator();

	friend bool operator==(const Translator& lhs, const Translator& rhs);

	// static Translator* find_translator_by_uid(uint32_t uid);
	// static Translator* find_translator_by_path(const char* path);

#if 0
	// Transform/Inject Libraries shared callbacks
	static int transform_send_request( struct transform_instance* inst, uint32_t uid, size_t len, uint8_t* message );
// 	static int inject_send_request( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	static int send_inject_request( struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	static int send_inject_response( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	static int send_command_response( struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	static int update_request( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	static int send_response( struct transform_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	static int send_update_response( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	static int logger_transform( struct transform_instance* inst, LOG_TYPE severity, const char* message );
	static int logger_inject( struct inject_instance* inst, LOG_TYPE severity, const char* message );
	static int logger_debug( struct debug_instance* inst, LOG_TYPE severity, const char* message );
	static int logger_command( struct command_instance* inst, LOG_TYPE severity, const char* message );
	static int create_var( const char* json_message );
	static const char* read_var( const char* json_message );
	static int update_var( const char* json_message );
	static int delete_var( const char* json_message );
	static const char* get_transform_path( struct transform_instance* inst );
	static const char* get_debug_path( struct debug_instance* inst );
	static const char* get_inject_path( struct inject_instance* inst );
	static const char* get_command_path( struct command_instance* inst );
#endif

	// int send_command_request(const char* target, size_t len, uint8_t* message);

	int handle_request( uint32_t uid, size_t len, uint8_t* message );
	// int handle_response( uint32_t uid, size_t len, uint8_t* message );
	int handle_update_request( uint32_t uid, size_t len, uint8_t* message );
	int handle_update_response( uint32_t uid, size_t len, uint8_t* message );
	// int handle_inject_request( uint32_t uid, size_t len, uint8_t* message );
	int handle_inject_response( uint32_t uid, size_t len, uint8_t* message );
	int handle_command_request( const char* target, size_t len, uint8_t* message );
	// int handle_command_response( const char* target, size_t len, uint8_t* message );

	ClientAPI* get_ClientAPI();
	HostAPI* get_HostAPI(int index);
	CommandInterface* get_CommandInterface();
	InjectInterface* get_InjectInterface();
	int get_num_children();
	Translator* get_child(int index);
	uint32_t get_uid();

#if 0
	int set_client( uint32_t uid, ClientAPI& client );
	int add_host( uint32_t uid, HostAPI& host );
#endif

	int send_response(uint32_t uid, size_t len, uint8_t* message);
	// New code
	int send_inject_request(uint32_t uid, size_t len, uint8_t* message);
	int send_inject_response(uint32_t uid, size_t len, uint8_t* message);
	int handle_inject_request( uint32_t uid, size_t len, uint8_t* message );
 	int send_command_response( uint32_t uid, size_t len, uint8_t* message );
	int handle_command_response( const char* target, size_t len, uint8_t* message );
	int inject_send_request(uint32_t uid, size_t len, uint8_t* message);
	int transform_send_request(uint32_t uid, size_t len, uint8_t* message);
	int handle_response( uint32_t uid, size_t len, uint8_t* message );
	int update_request(uint32_t uid, size_t len, uint8_t* message);
	int send_update_response( uint32_t uid, size_t len, uint8_t* message );
	int send_transform_response( uint32_t uid, size_t len, uint8_t* message );
	int logger_transform( LOG_TYPE severity, const char* message );
	int logger_inject( LOG_TYPE severity, const char* message );
	int logger_debug( LOG_TYPE severity, const char* message );
	int logger_command( LOG_TYPE severity, const char* message );
	const char* get_path();
	const char* get_module_name();
	const char* get_instance_name();

	void dump(size_t indent);

private:
	Translator();
	Translator(const Translator& t);
	Translator& operator=(const Translator& t);
#if 0
	static Translator* __lookup_translator(uint32_t translator_uid);
	HostAPI* __lookup_host(uint32_t uid);
#endif
	const char* __get_path();
	int __logger(LOG_TYPE severity, const char* message);
	Translator* __get_child_by_uid(uint32_t uid);

	// static uint32_t translator_count;
	static CommandBus* cmd_bus;
	uint32_t t_uid;
	int mode;
	translator_transform_api ttapi;
	translator_inject_api tiapi;
	translator_debug_api tdapi;
	translator_command_api tcapi;
	void* tlib_handle;
	void* dlib_handle;
	void* ilib_handle;
	void* clib_handle;
	transform_library_api* tla;
	debug_library_api* dla;
	inject_library_api* ila;
	command_library_api* cla;
	transform_instance* t_inst;
	debug_instance* d_inst;
	inject_instance* i_inst;
	command_instance* c_inst;
	// ClientAPI* client_p;
	TranslatorRep trep;

	InjectInterface* ii_p; // IF between InjectLibrary and CommandLibrary
	CommandInterface* ci_p; // IF between CommandLibrary and CommandBus

	TransformLibraryWrapper* tlw_p;
	DebugLibraryWrapper* dlw_p;
	InjectLibraryWrapper* ilw_p;
	CommandLibraryWrapper* clw_p;

	// Associative arrays
	// static std::vector<Translator*> translator_list;
	// static std::vector<uint32_t> uid_list;
	// static std::vector<const char*> path_list;

	// std::map<uint32_t, HostAPI*> host_repository;
};

#endif /* INCLUDE_MODEL_TRANSLATOR_HPP_ */
