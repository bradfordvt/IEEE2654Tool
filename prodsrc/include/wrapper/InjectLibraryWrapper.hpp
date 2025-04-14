/*
 *    InjectLibraryWrapper.hpp
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

#ifndef INCLUDE_WRAPPER_INJECTLIBRARYWRAPPER_HPP_
#define INCLUDE_WRAPPER_INJECTLIBRARYWRAPPER_HPP_

#include "parser/InjectInterfaceRep.hpp"
#include "parser/InjectLibraryRep.hpp"
#include "api/translator_api.h"
#include "api/inject_library_api.h"

class InjectLibraryWrapper {
public:
	InjectLibraryWrapper(uint32_t uid, const InjectLibraryRep& ilr);
	InjectLibraryWrapper(const InjectLibraryWrapper& cr);
	~InjectLibraryWrapper();

	friend bool operator==(const InjectLibraryWrapper& lhs, const InjectLibraryWrapper& rhs);

	static const char** get_translator_error_strings();
	static const char** get_translator_status_strings();
	static int send_request(struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message);
	static int send_inject_response(struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message);
	static int update_request(struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message);
	static int send_update_response(struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message);
	static int logger(struct inject_instance* inst, LOG_TYPE severity, const char* message);
	static const char* get_path(struct inject_instance* inst);
	static int create_var(const char* json_message);
	static const char* read_var(const char* json_message);
	static int update_var(const char* json_message);
	static int delete_var(const char* json_message);

	struct translator_inject_api* get_translator_inject_api();


	// Wrapper methods to InjectLibrary
	int open();
	int close();
	int config(char* json_message);
	int select(uint32_t index);
	int deselect(uint32_t index);
	bool is_selected(uint32_t uid);
	translator_error_code get_error_code();
	const char* get_error_string();
	translator_status get_status_code();
	const char* get_status_string();
	int handle_request(size_t len, uint8_t* message);
	int handle_response(size_t len, uint8_t* message);
	int handle_update_request(size_t len, uint8_t* message);
	int handle_update_response(size_t len, uint8_t* message);
	int handle_inject_request(size_t len, uint8_t* message);
	int apply();

	// Status method about construction
	bool get_sanity();

private:
	// uint32_t uid;
	translator_inject_api tiapi;
	inject_library_api* ila;
	inject_instance* inst;
	InjectLibraryRep ilrep;
	void* ilib_handle;
	bool sanity;
};


#endif /* INCLUDE_WRAPPER_INJECTLIBRARYWRAPPER_HPP_ */
