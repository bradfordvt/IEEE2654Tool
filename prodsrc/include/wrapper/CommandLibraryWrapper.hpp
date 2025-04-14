/*
 *    CommandLibraryWrapper.hpp
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

#ifndef INCLUDE_BUS_COMMANDLIBRARYWRAPPER_HPP_
#define INCLUDE_BUS_COMMANDLIBRARYWRAPPER_HPP_

// #include <stdint.h>
// #include <stddef.h>
#include "model/Translator.hpp"
// #include "parser/CommandInterfaceRep.hpp"

class Translator;

class CommandLibraryWrapper {
public:
	CommandLibraryWrapper(uint32_t uid, const CommandLibraryRep& clr);
	CommandLibraryWrapper(const CommandLibraryWrapper& cr);
	~CommandLibraryWrapper();

	friend bool operator==(const CommandLibraryWrapper& lhs, const CommandLibraryWrapper& rhs);

	static const char** get_translator_error_strings();
	static const char** get_translator_status_strings();
	static int send_inject_request(struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message);
	static int send_command_response(struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message);
	static int logger(struct command_instance* inst, LOG_TYPE severity, const char* message);
	static const char* get_path(struct command_instance* inst);
	static int create_var(const char* json_message);
	static const char* read_var(const char* json_message);
	static int update_var(const char* json_message);
	static int delete_var(const char* json_message);

	struct translator_command_api* get_translator_command_api();

	// Wrapper methods to CommandLibrary
	int open();
	int close();
	int config(char* json_message);
	translator_error_code get_error_code();
	const char* get_error_string();
	translator_status get_status_code();
	const char* get_status_string();
	int handle_command_request(size_t len, uint8_t* message);
	int handle_inject_response(size_t len, uint8_t* message);
	int apply();

	// Status method about construction
	bool get_sanity();
private:
	// uint32_t uid;
	translator_command_api tcapi;
	command_library_api* cla;
	command_instance* c_inst;
	CommandLibraryRep clrep;
	void* clib_handle;
	bool sanity;
};


#endif /* INCLUDE_BUS_COMMANDLIBRARYWRAPPER_HPP_ */
