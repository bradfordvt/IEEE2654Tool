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

#include "CLTestLeaf.hpp"
#include "rapidjson/document.h" // rapidjason's DOM-style API
#include "IEEE2654.pb.h"
// #include "Imperative_KEYPAD.pb.h"
#include "Command_BUTTON.pb.h"

CLTestLeaf::CLTestLeaf()
{
	my_inst = (command_instance*)0;
	tc_api = (translator_command_api*)0;
	sticky = true;
	observable = true;
	function = std::string("UNDEFINED");
}

CLTestLeaf::~CLTestLeaf()
{
}

int CLTestLeaf::open( struct command_instance* inst, struct translator_command_api* tc_api )
{
	my_inst = inst;
	this->tc_api = tc_api;
	my_inst->translator_api = tc_api;
	my_inst->error_code = translator_success;
	my_inst->status_code = translator_ok;
	my_inst->visible = true;
	my_inst->child_uid = 0;
	my_inst->children_uids = NULL;
	my_inst->num_children = 0;
	return 0;
}

int CLTestLeaf::close( )
{
	return 0;
}

int CLTestLeaf::config( char* json_message )
{
	return __parse_config(json_message);
}

enum translator_error_code CLTestLeaf::get_error_code( )
{
	return my_inst->error_code;
}

const char* CLTestLeaf::get_error_string( )
{
	return translator_error_strings[my_inst->error_code];
}

enum translator_status CLTestLeaf::get_status_code( )
{
	return my_inst->status_code;
}

const char* CLTestLeaf::get_status_string( )
{
	return translator_status_strings[my_inst->status_code];
}

int CLTestLeaf::handle_command_request( size_t len, uint8_t* message )
{
        IEEE2654::IEEE2654Message msg = ::IEEE2654::IEEE2654Message();
        msg.ParseFromString(std::string(reinterpret_cast<const char*>(message), len));
        if(msg.metaname() == "BUTTON")
        {
                ::Imperative_KEYPAD::BUTTON btn = ::Imperative_KEYPAD::BUTTON();
                btn.ParseFromString(msg.serialized());
                if(btn.function() == "PRESS")
		{
			::Command_BUTTON::PRESS press = ::Command_BUTTON::PRESS();
			press.set_uid(my_inst->translator_uid);
			std::string serialized_message;
			press.SerializeToString(&serialized_message);
			int ret = __send_inject_request("PRESS", serialized_message);
			return ret;
		}
		else if(btn.function() == "RELEASE")
		{
			std::string serialized_message;
			btn.SerializeToString(&serialized_message);
			int ret = __sendImperativeResponse("RELEASE", serialized_message);
			return ret;
		}
		else
                {
                        my_inst->error_code = translator_message_error;
                        my_inst->status_code = translator_failed;
                        int ret = __sendImperativeErrorResponse(__FILE__, __LINE__, "The BUTTON function was not RELEASE or PRESS");
                        return -1;
                }
	}
	else
        {
                my_inst->error_code = translator_message_error;
                my_inst->status_code = translator_failed;
                int ret = __sendImperativeErrorResponse(__FILE__, __LINE__, "The metaname was not BUTTON");
                return -1;
        }
}

int CLTestLeaf::handle_inject_response( size_t len, uint8_t* message )
{
        IEEE2654::IEEE2654Message msg = ::IEEE2654::IEEE2654Message();
        msg.ParseFromString(std::string(reinterpret_cast<const char*>(message), len));
        if(msg.metaname() == "PRESS")
        {
		::Command_BUTTON::PRESS press = ::Command_BUTTON::PRESS();
                press.ParseFromString(msg.serialized());
                ::Imperative_KEYPAD::BUTTON btn = ::Imperative_KEYPAD::BUTTON();
		btn.set_uid(my_inst->translator_uid);
		btn.set_function("PRESS");
		std::string serialized_message;
		btn.SerializeToString(&serialized_message);
		int ret = __sendImperativeResponse("PRESS", serialized_message);
		return ret;
	}
	else
	{
                my_inst->error_code = translator_message_error;
                my_inst->status_code = translator_failed;
                int ret = __sendImperativeErrorResponse(__FILE__, __LINE__, "The COMMAND was not PRESS");
                return -1;
	}
}

int CLTestLeaf::apply( ) {
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

int CLTestLeaf::__send_inject_request( const char* metaname, std::string& msg )
{
	::IEEE2654::IEEE2654Message wrapper = ::IEEE2654::IEEE2654Message();
	wrapper.set_uid(my_inst->translator_uid);
	wrapper.set_metaname(metaname);
	wrapper.set_serialized(msg);
	std::string serialized_message;
	wrapper.SerializeToString(&serialized_message);
	return tc_api->send_inject_request(my_inst, my_inst->translator_uid, serialized_message.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(serialized_message.c_str())));
}

int CLTestLeaf::__sendImperativeResponse( const char* metaname, std::string& message )
{
	::IEEE2654::IEEE2654Message wrapper = ::IEEE2654::IEEE2654Message();
	wrapper.set_uid(my_inst->translator_uid);
	wrapper.set_metaname(metaname);
	wrapper.set_serialized(message);
	std::string serialized_message;
	wrapper.SerializeToString(&serialized_message);
	return tc_api->send_command_response(my_inst, my_inst->translator_uid, serialized_message.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(serialized_message.c_str())));
}

int CLTestLeaf::__sendImperativeErrorResponse( const char* file, int line, const char* message )
{
	::IEEE2654::IEEE2654Error error = ::IEEE2654::IEEE2654Error();
	error.set_uid(my_inst->translator_uid);
	std::string s("Error detected in file:\n\t");
	s += file;
	s += "\n\tline number:\n\t";
	s += std::to_string(line);
	s += "\n";
	s += message;
	s += "\n";
	error.set_uid(my_inst->translator_uid);
	error.set_message(s);
	error.set_code(my_inst->error_code);
	std::string serialized_error;
	error.SerializeToString(&serialized_error);

	::IEEE2654::IEEE2654Message wrapper = ::IEEE2654::IEEE2654Message();
	wrapper.set_uid(my_inst->translator_uid);
	wrapper.set_metaname("IEEE2654ERROR");
	wrapper.set_serialized(serialized_error);
	std::string sm;
	wrapper.SerializeToString(&sm);
	return tc_api->send_command_response(my_inst, my_inst->translator_uid, sm.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(sm.c_str())));
}

int CLTestLeaf::__parse_config( char* json_message )
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

int CLTestLeaf::__setVisible( const char* val )
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

int CLTestLeaf::__setSticky( const char* val )
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

int CLTestLeaf::__setObservable( const char* val )
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

int CLTestLeaf::__setFunction( const char* val )
{
	function = std::string(val);
	return 0;
}
