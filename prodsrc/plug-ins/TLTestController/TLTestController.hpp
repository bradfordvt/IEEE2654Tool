/*
 *    Class that represents a controller module collecting expressions from
 *    lower levels of the tree model and evaluates the expression returning
 *    the result of the expression.
 *
 *    Class that represents a controller module collecting expressions from
 *    lower levels of the tree model and evaluates the expression returning
 *    the result of the expression.
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

#ifndef TLTESTCONTROLLER_HPP_
#define TLTESTCONTROLLER_HPP_

#include <stddef.h>
#include <string>
#include <stack>
#include "api/transform_library_api.h"
#include "Imperative_EXPRESSION.pb.h"
#include "DISPLAY.pb.h"
#include "IEEE2654.pb.h"

class TLTestController
{
public:
	TLTestController();
	~TLTestController();

	int open(struct transform_instance* inst, struct translator_transform_api* tt_api );
	int close( );
	int config( char* json_message );
	int select( uint32_t index );
	int deselect( uint32_t index );
	bool is_selected( uint32_t uid );
	enum translator_error_code get_error_code( );
	const char* get_error_string( );
	enum translator_status get_status_code( );
	const char* get_status_string( );
	int handle_request( size_t len, uint8_t* message );
	int handle_response( size_t len, uint8_t* message );
	int apply( );

private:
	int __parse_config( char* json_message );
	int __setVisible( const char* val );
	int __setSticky( const char* val );
	int __setObservable( const char* val );
	int __handle_expr_request(::IEEE2654::IEEE2654Message& wrapper);
	int __handle_read_request(::IEEE2654::IEEE2654Message& wrapper);
	int __handle_show_request(::IEEE2654::IEEE2654Message& wrapper);
	int __send_error_response( const char* file, int line, const char* message );
	int __send_response( ::IEEE2654::IEEE2654Message& wrapper );

	transform_instance* my_inst;
	const char** translator_error_strings;
	const char** translator_status_strings;
	translator_transform_api* tt_api;
	bool sticky;
	bool observable;
	Imperative_EXPRESSION::EXPR exp;
	std::string display;
	// IEEE2654::IEEE2654Message wrapper;
};

#endif /* TLTESTCONTROLLER_HPP_ */
