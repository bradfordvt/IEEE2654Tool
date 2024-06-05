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

static const char __authors__[] = "Bradford G. Van Treuren";
static const char __contact__[] = "bradvt59@gmail.com";
static const char __copyright__[] = "Copyright (C) 2024, Bradford G. Van Treuren";
static const char __credits__[] = "Bradford G. Van Treuren";
static const char __date__[] = "2024/03/22";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "TLTestLeaf.hpp"
#include "rapidjson/document.h" // rapidjason's DOM-style API

TLTestLeaf::TLTestLeaf()
{
	my_inst = (transform_instance*)0;
	tt_api = (translator_transform_api*)0;
	sticky = true;
	observable = true;
	function = std::string("UNDEFINED");
}

TLTestLeaf::~TLTestLeaf()
{
}

int TLTestLeaf::open( struct transform_instance* inst, struct translator_transform_api* tt_api )
{
	my_inst = inst;
	this->tt_api = tt_api;
	my_inst->translator_api = tt_api;
	my_inst->error_code = translator_success;
	my_inst->status_code = translator_ok;
	my_inst->visible = true;
	my_inst->child_uid = 0;
	my_inst->children_uids = NULL;
	my_inst->num_children = 0;
	return 0;
}

int TLTestLeaf::close( )
{
	return 0;
}

int TLTestLeaf::config( char* json_message )
{
	return __parse_config(json_message);
}

int TLTestLeaf::select( uint32_t index )
{
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int TLTestLeaf::deselect( uint32_t index )
{
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

bool TLTestLeaf::is_selected( uint32_t uid )
{
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

enum translator_error_code TLTestLeaf::get_error_code( )
{
	return my_inst->error_code;
}

const char* TLTestLeaf::get_error_string( )
{
	return translator_error_strings[my_inst->error_code];
}

enum translator_status TLTestLeaf::get_status_code( )
{
	return my_inst->status_code;
}

const char* TLTestLeaf::get_status_string( )
{
	return translator_status_strings[my_inst->status_code];
}

int TLTestLeaf::handle_request( size_t len, uint8_t* message )
{
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

int TLTestLeaf::handle_response( size_t len, uint8_t* message )
{
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}
int TLTestLeaf::apply( )
{
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

int TLTestLeaf::__parse_config( char* json_message )
{
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
	int rval1 = -1, rval2 = -1, rval3 = -1, rval4 = -1, rval5 = -1;
	rapidjson::Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
	
	// In-situ parsing, decode strings directly in the source string.
	// Source must be string.
	char buffer[sizeof(json_message)];
	memcpy(buffer, json_message, sizeof(json_message));
	if(document.ParseInsitu(buffer).HasParseError())
	{
		my_inst->error_code = translator_format_error;
		my_inst->status_code = translator_broken;
		return -1;
	}
	// Parsing to document succeeded

	// 2. Access values in document.
	if(!document.IsObject())
	{
		my_inst->error_code = translator_format_error;
		my_inst->status_code = translator_broken;
		return -1;
	}
	const rapidjson::Value& properties = document["properties"]; // Using a reference for consecutive access is handy and faster.
	if(!properties.IsObject())
	{
		my_inst->error_code = translator_format_error;
		my_inst->status_code = translator_broken;
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
	if(properties.HasMember("function"))
	{
		rval4 = __setFunction(properties["function"].GetString());
	}
	if(rval4) return rval4;
	if(rval3) return rval3;
	if(rval2) return rval2;
	if(rval1) return rval1;
	return 0;
}

int TLTestLeaf::__setVisible( const char* val )
{
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

int TLTestLeaf::__setSticky( const char* val )
{
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

int TLTestLeaf::__setObservable( const char* val )
{
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

int TLTestLeaf::__setFunction( const char* val )
{
	function = std::string(val);
	return 0;
}
