/*
 *    Class that represents a value at the display of the tree model.
 *
 *    Class that represents a value at the display of the tree model.
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
static const char __date__[] = "2024/07/31";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "TLTestDisplay.hpp"
#include "rapidjson/document.h" // rapidjason's DOM-style API
#include <iostream>

#include "debug/SwDebugLib.hpp"

TLTestDisplay::TLTestDisplay()
{
	SWDEBUG1( struct transform_instance, NULL, "TLTestDisplay::TLTestDisplay" );
	my_inst = (transform_instance*)0;
	tt_api = (translator_transform_api*)0;
	sticky = true;
	observable = true;
	function = std::string("UNDEFINED");
}

TLTestDisplay::~TLTestDisplay()
{
	SWDEBUG1( struct transform_instance, NULL, "TLTestDisplay::~TLTestDisplay" );
}

int TLTestDisplay::open( struct transform_instance* inst, struct translator_transform_api* tt_api )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestDisplay::open",
			" struct transform_instance*, struct translator_inject_api* ");
	my_inst = inst;
	this->tt_api = tt_api;
	my_inst->translator_api = tt_api;
	my_inst->error_code = translator_success;
	my_inst->status_code = translator_ok;
	my_inst->visible = true;
	my_inst->child_uid = 0;
	my_inst->children_uids = NULL;
	my_inst->num_children = 0;
	translator_error_strings = tt_api->get_translator_error_strings();
	translator_status_strings = tt_api->get_translator_status_strings();
	return 0;
}

int TLTestDisplay::close( )
{
	SWDEBUG1( struct transform_instance, NULL, "TLTestDisplay::close" );
	return 0;
}

int TLTestDisplay::config( char* json_message )
{
	SWDEBUG1( struct transform_instance, NULL, "TLTestDisplay::config" );
	std::string note = "json_message = ";
	note += json_message;
	SWDEBUG_LOG(__FILE__, note);
	return __parse_config(json_message);
}

int TLTestDisplay::select( uint32_t index )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestDisplay::select",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int TLTestDisplay::deselect( uint32_t index )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestDisplay::deselect",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

bool TLTestDisplay::is_selected( uint32_t uid )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestDisplay::is_selected",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

enum translator_error_code TLTestDisplay::get_error_code( )
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestDisplay::get_error_code" );
	return my_inst->error_code;
}

const char* TLTestDisplay::get_error_string( )
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestDisplay::get_error_string" );
	return translator_error_strings[my_inst->error_code];
}

enum translator_status TLTestDisplay::get_status_code( )
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestDisplay::get_status_code" );
	return my_inst->status_code;
}

const char* TLTestDisplay::get_status_string( )
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestDisplay::get_status_string" );
	return translator_status_strings[my_inst->status_code];
}

int TLTestDisplay::handle_request( size_t len, uint8_t* message )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestDisplay::handle_request",
			" size_t, uint8_t* ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

int TLTestDisplay::handle_response( size_t len, uint8_t* message )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestDisplay::handle_response",
			" size_t, uint8_t* ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}
int TLTestDisplay::apply( )
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestDisplay::app;y" );
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

int TLTestDisplay::__parse_config( char* json_message )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestDisplay::__parse_config",
			" char* ");
	// 1. Parse a JSON text string to a document.
	/* json_message should be in the form:
	 * {
	 * 	"properties" : {
	 * 		"visible" : "true",
	 * 		"sticky" : "false",
	 * 		"observable" : "true",
	 * 		"function" : "ENTER"
	 * 	}
	 * }
	 */
	int rval1 = -1, rval2 = -1, rval3 = -1,  rval5 = -1;
	rapidjson::Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
	
	// In-situ parsing, decode strings directly in the source string.
	// Source must be string.
	char buffer[strlen(json_message)+1];
	memcpy(buffer, json_message, strlen(json_message)+1);
	if(document.ParseInsitu(buffer).HasParseError())
	{
		my_inst->error_code = translator_format_error;
		my_inst->status_code = translator_broken;
		std::cerr << "TLTestDisplay::__parse(): HasParseError" << std::endl;
		return -1;
	}
	// Parsing to document succeeded

	// 2. Access values in document.
	if(!document.IsObject())
	{
		my_inst->error_code = translator_format_error;
		my_inst->status_code = translator_broken;
		std::cerr << "TLTestDisplay::__parse(): !document.IsObject()" << std::endl;
		return -1;
	}
	const rapidjson::Value& properties = document["properties"]; // Using a reference for consecutive access is handy and faster.
	if(!properties.IsObject())
	{
		my_inst->error_code = translator_format_error;
		my_inst->status_code = translator_broken;
		std::cerr << "TLTestDisplay::__parse(): !properties.IsObject()" << std::endl;
		return -1;
	}
	if(properties.HasMember("visible"))
	{
		rval1 = __setVisible(properties["visible"].GetString());
	}
	if(properties.HasMember("sticky"))
	{
		rval2 = __setSticky(properties["sticky"].GetString());
	}
	if(properties.HasMember("observable"))
	{
		rval3 = __setObservable(properties["observable"].GetString());
	}
        std::cerr << "TLTestDisplay::__parse(): rval3 = " << rval3 << std::endl;
        std::cerr << "TLTestDisplay::__parse(): rval2 = " << rval2 << std::endl;
        std::cerr << "TLTestDisplay::__parse(): rval1 = " << rval1 << std::endl;
	if(rval3) return rval3;
	if(rval2) return rval2;
	if(rval1) return rval1;
	return 0;
}

int TLTestDisplay::__setVisible( const char* val )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestDisplay::__setVisible",
			" const char* ");
	if(!strcmp(val, "false"))
	{
		my_inst->visible = false;
	}
	else if(!strcmp(val, "true"))
	{
		my_inst->visible = true;
	}
	else
	{
		my_inst->error_code = translator_format_error;
		my_inst->status_code = translator_broken;
		return -1;
	}
	return 0;
}

int TLTestDisplay::__setSticky( const char* val )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestDisplay::__setSticky",
			" const char* ");
	if(!strcmp(val, "false"))
	{
		sticky = false;
	}
	else if(!strcmp(val, "true"))
	{
		sticky = true;
	}
	else
	{
		my_inst->error_code = translator_format_error;
		my_inst->status_code = translator_broken;
		return -1;
	}
	return 0;
}

int TLTestDisplay::__setObservable( const char* val )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestDisplay::__setObservable",
			" const char* ");
	if(!strcmp(val, "false"))
	{
		observable = false;
	}
	else if(!strcmp(val, "true"))
	{
		observable = true;
	}
	else
	{
		my_inst->error_code = translator_format_error;
		my_inst->status_code = translator_broken;
		return -1;
	}
	return 0;
}

int TLTestDisplay::__setFunction( const char* val )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestDisplay::__setFunction",
			" const char* ");
	function = std::string(val);
	return 0;
}
