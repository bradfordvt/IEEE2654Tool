/*
 *    Class that represents a value at the leaf of the tree model.
 *
 *    Class that represents a value at the leaf of the tree model.
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

#ifndef ILTESTLEAF_HPP_
#define ILTESTLEAF_HPP_

#include <stddef.h>
#include <string>
#include "api/inject_library_api.h"
#include "IEEE2654.pb.h"

class ILTestLeaf
{
public:
	ILTestLeaf();
	~ILTestLeaf();

	int open(struct inject_instance* inst, struct translator_inject_api* ti_api );
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
	int handle_update_request( size_t len, uint8_t* message );
	int handle_update_response( size_t len, uint8_t* message );
	int handle_inject_request( size_t len, uint8_t* message );
	int apply( );

private:
	int __parse_config( char* json_message );
	int __setVisible( const char* val );
	int __setSticky( const char* val );
	int __setObservable( const char* val );
	int __setFunction( const char* val );
	int __sendRequest( ::IEEE2654::IEEE2654Message& wrapper );
	int __sendInjectResponse( ::IEEE2654::IEEE2654Message& wrapper );
	int __sendInjectErrorResponse( const char* file, int line, const char* message );

	inject_instance* my_inst;
	translator_inject_api* ti_api;
	bool visible;
	bool sticky;
	bool observable;
	std::string function;
};

#endif /* ILTESTLEAF_HPP_ */
