/*
 *    Class that represents an aggregation module collecting values applied
 *    at the leaf of the tree model.
 *
 *    Class that represents an aggregation module collecting values applied
 *    at the leaf of the tree model.
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

#ifndef DLTESTINTERMEDIATE_HPP_
#define DLTESTINTERMEDIATE_HPP_

#include <stddef.h>
#include <string>
#include <stack>
#include "api/debug_library_api.h"

class DLTestIntermediate
{
public:
	DLTestIntermediate();
	~DLTestIntermediate();

	int open(struct debug_instance* inst, struct translator_debug_api* td_api );
	int close( );
	int config( char* json_message );
	int select( uint32_t index );
	int deselect( uint32_t index );
	bool is_selected( uint32_t uid );
	enum translator_error_code get_error_code( translator_error_code code );
	const char* get_error_string( translator_error_code code );
	enum translator_status get_status_code( translator_status code );
	const char* get_status_string( translator_status code );
	int handle_request( size_t len, uint8_t* message );
	int handle_response( size_t len, uint8_t* message );
	int handle_update_request( size_t len, uint8_t* message );
	int handle_update_response( size_t len, uint8_t* message );
	int handle_inject_request( size_t len, uint8_t* message );
	int handle_inject_response( size_t len, uint8_t* message );
	int handle_command_request( size_t len, uint8_t* message );
	int apply( );

private:
	int __parse_config( char* json_message );
	int __setVisible( const char* val );
	int __setSticky( const char* val );
	int __setObservable( const char* val );
	int __handle_digit_request(const std::string& value, const std::string& button);
	int __handle_enter_request(const std::string& button);
	int __handle_operator_request(const std::string& op, const std::string& button);
	int __handle_dot_request(const std::string& button);
	int __handle_expr_response(const std::string& expr);

	debug_instance* my_inst;
	translator_debug_api* td_api;
	bool sticky;
	bool observable;
	std::string result;
};

#endif /* DLTESTINTERMEDIATE_HPP_ */
