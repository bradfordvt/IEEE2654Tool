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
static const char __date__[] = "2024/03/22";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "ILTestDisplay.hpp"
#include "rapidjson/document.h" // rapidjason's DOM-style API
#include "IEEE2654.pb.h"
#include "DISPLAY.pb.h"
#include "Command_DISPLAY.pb.h"

#include "debug/SwDebugLib.hpp"

ILTestDisplay::ILTestDisplay()
{
	SWDEBUG1( struct inject_instance, NULL, "ILTestDisplay::ILTestDisplay" );
	my_inst = (inject_instance*)0;
	ti_api = (translator_inject_api*)0;
	visible = true;
	sticky = true;
	observable = true;
	response_received = false;
	response_failed = false;
	function = std::string("UNDEFINED");
}

ILTestDisplay::~ILTestDisplay()
{
	SWDEBUG1( struct inject_instance, NULL, "ILTestDisplay::~ILTestDisplay" );
}

int ILTestDisplay::open( struct inject_instance* inst, struct translator_inject_api* ti_api )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplay::open",
			" struct inject_instance*, struct translator_inject_api* ");
	my_inst = inst;
	this->ti_api = ti_api;
	my_inst->translator_api = ti_api;
	my_inst->error_code = translator_success;
	my_inst->status_code = translator_ok;
	my_inst->visible = true;
	my_inst->child_uid = 0;
	my_inst->children_uids = NULL;
	my_inst->num_children = 0;
	translator_error_strings = ti_api->get_translator_error_strings();
	translator_status_strings = ti_api->get_translator_status_strings();
	return 0;
}

int ILTestDisplay::close( )
{
	SWDEBUG1( struct inject_instance, NULL, "ILTestDisplay::close" );
	return 0;
}

int ILTestDisplay::config( char* json_message )
{
	SWDEBUG1( struct inject_instance, NULL, "ILTestDisplay::config" );
	std::string note = "json_message = ";
	note += json_message;
	SWDEBUG_LOG(__FILE__, note);
	return __parse_config(json_message);
}

int ILTestDisplay::select( uint32_t index )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestDisplay::select",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int ILTestDisplay::deselect( uint32_t index )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestDisplay::deselect",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

bool ILTestDisplay::is_selected( uint32_t uid )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestDisplay::is_selected",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

enum translator_error_code ILTestDisplay::get_error_code( )
{
	SWDEBUG1( struct inject_instance, my_inst, "ILTestDisplay::get_error_code" );
	return my_inst->error_code;
}

const char* ILTestDisplay::get_error_string( )
{
	SWDEBUG1( struct inject_instance, my_inst, "ILTestDisplay::get_error_string" );
	return translator_error_strings[my_inst->error_code];
}

enum translator_status ILTestDisplay::get_status_code( )
{
	SWDEBUG1( struct inject_instance, my_inst, "ILTestDisplay::get_status_code" );
	return my_inst->status_code;
}

const char* ILTestDisplay::get_status_string( )
{
	SWDEBUG1( struct inject_instance, my_inst, "ILTestDisplay::get_status_string" );
	return translator_status_strings[my_inst->status_code];
}

int ILTestDisplay::handle_request( size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestDisplay::handle_request",
			" size_t, uint8_t* ");
	// This is a display node, thus no children to send a request
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int ILTestDisplay::handle_response( size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestDisplay::handle_response",
			" size_t, uint8_t* ");
	IEEE2654::IEEE2654Message msg = ::IEEE2654::IEEE2654Message();
	msg.ParseFromString(std::string((const char*)message, len));
	if(msg.metaname() == "SHOW")
	{
		::DISPLAY::SHOW show = ::DISPLAY::SHOW();
		show.ParseFromString(msg.serialized());
		if(show.uid() != my_inst->translator_uid)
		{
			SWDEBUG_LOG(__FILE__, "ILTestDisplay::handle_response(): uid's don't match!");
			my_inst->error_code = translator_message_error;
			my_inst->status_code = translator_failed;
			response_received = true;
			response_failed = true;
			int ret = -1;
			return ret;
		}
		value = show.value();
		response_received = true;
		response_failed = false;
		int ret = 0;
		return ret;
	}
	if(msg.metaname() == "READ")
	{
		::DISPLAY::READ read = ::DISPLAY::READ();
		read.ParseFromString(msg.serialized());
		if(read.uid() != my_inst->translator_uid)
		{
			SWDEBUG_LOG(__FILE__, "ILTestDisplay::handle_response(): uid's don't match!");
			my_inst->error_code = translator_message_error;
			my_inst->status_code = translator_failed;
			response_received = true;
			response_failed = true;
			int ret = -1;
			return ret;
		}
		value = read.value();
		response_received = true;
		response_failed = false;
		int ret = 0;
		return ret;
	}
	else if(msg.metaname() == "ERROR")
	{
		::IEEE2654::IEEE2654Error err = ::IEEE2654::IEEE2654Error();
		err.ParseFromString(msg.serialized());
		err.set_uid(my_inst->translator_uid);
		my_inst->error_code = translator_response_failed;
		my_inst->status_code = translator_failed;
		value = msg.serialized();
		err.set_code(translator_response_failed);
		::IEEE2654::IEEE2654Message wrapper = ::IEEE2654::IEEE2654Message();
		wrapper.set_uid(my_inst->translator_uid);
		wrapper.set_metaname("ERROR");
		wrapper.set_serialized(err.SerializeAsString());
		int ret = __sendInjectResponse(wrapper);
		return ret;
	}
	else
	{
		my_inst->error_code = translator_unknown_metaname;
		my_inst->status_code = translator_failed;
		int ret = -1;
		return ret;
	}
}

int ILTestDisplay::handle_update_request( size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestDisplay::handle_update_request",
			" size_t, uint8_t* ");
	// This is a display node that does not have a value that can be updated
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int ILTestDisplay::handle_update_response( size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestDisplay::handle_update_response",
			" size_t, uint8_t* ");
	// This is a display node that does not have a value that can be updated
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int ILTestDisplay::handle_inject_request( size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestDisplay::handle_inject_request",
			" size_t, uint8_t* ");
	IEEE2654::IEEE2654Message msg = ::IEEE2654::IEEE2654Message();
	msg.ParseFromString(std::string((const char*)message, len));
	response_received = false;
	response_failed = false;
	if(msg.metaname() == "SHOW")
	{
		::Command_DISPLAY::SHOW cmd = ::Command_DISPLAY::SHOW();
		cmd.ParseFromString(msg.serialized());
		::DISPLAY::SHOW show = ::DISPLAY::SHOW();
		show.set_uid(my_inst->translator_uid);
		show.set_value(cmd.value());
		::IEEE2654::IEEE2654Message wrapper = ::IEEE2654::IEEE2654Message();
		wrapper.set_uid(my_inst->translator_uid);
		wrapper.set_metaname("SHOW");
		wrapper.set_serialized(show.SerializeAsString());
		int ret = __sendRequest(wrapper);
		if(ret != 0)
		{
			my_inst->error_code = translator_message_error;
			my_inst->status_code = translator_failed;
			int ret = __sendInjectErrorResponse(__FILE__, __LINE__, "The request for SHOW returned an error code");
			return -1;
		}
		else
		{
			if(response_received)
			{
				::DISPLAY::SHOW show = ::DISPLAY::SHOW();
				show.ParseFromString(msg.serialized());
				::Command_DISPLAY::SHOW cmd = ::Command_DISPLAY::SHOW();
				cmd.set_uid(my_inst->translator_uid);
				cmd.set_value(value);
				::IEEE2654::IEEE2654Message wrapper = ::IEEE2654::IEEE2654Message();
				wrapper.set_uid(my_inst->translator_uid);
				wrapper.set_metaname("SHOW");
				wrapper.set_serialized(cmd.SerializeAsString());
				int ret = __sendInjectResponse(wrapper);
				return ret;
			}
			else
			{
				SWDEBUG_LOG(__FILE__, "ILTestDisplay::handle_inject_request(): disp.function ERROR 1");
				my_inst->error_code = translator_message_error;
				my_inst->status_code = translator_failed;
				int ret = __sendInjectErrorResponse(__FILE__, __LINE__, "The DISPLAY function was not SHOW");
				return ret;
			}
		}
	}
	else if(msg.metaname() == "READ")
	{
		::Command_DISPLAY::READ cmd = ::Command_DISPLAY::READ();
		cmd.ParseFromString(msg.serialized());
		::DISPLAY::READ read = ::DISPLAY::READ();
		read.set_uid(my_inst->translator_uid);
		read.set_value(cmd.value());
		::IEEE2654::IEEE2654Message wrapper = ::IEEE2654::IEEE2654Message();
		wrapper.set_uid(my_inst->translator_uid);
		wrapper.set_metaname("READ");
		wrapper.set_serialized(read.SerializeAsString());
		int ret = __sendRequest(wrapper);
		if(ret != 0)
		{
			my_inst->error_code = translator_message_error;
			my_inst->status_code = translator_failed;
			int ret = __sendInjectErrorResponse(__FILE__, __LINE__, "The request for READ returned an error code");
			return -1;
		}
		else
		{
			if(response_received)
			{
				::DISPLAY::SHOW show = ::DISPLAY::SHOW();
				show.ParseFromString(msg.serialized());
				::Command_DISPLAY::READ cmd = ::Command_DISPLAY::READ();
				cmd.set_uid(my_inst->translator_uid);
				cmd.set_value(value);
				::IEEE2654::IEEE2654Message wrapper = ::IEEE2654::IEEE2654Message();
				wrapper.set_uid(my_inst->translator_uid);
				wrapper.set_metaname("READ");
				wrapper.set_serialized(cmd.SerializeAsString());
				int ret = __sendInjectResponse(wrapper);
				return ret;
			}
			else
			{
				SWDEBUG_LOG(__FILE__, "ILTestDisplay::handle_inject_request(): disp.function ERROR 1");
				my_inst->error_code = translator_message_error;
				my_inst->status_code = translator_failed;
				int ret = __sendInjectErrorResponse(__FILE__, __LINE__, "The DISPLAY function was not READ");
				return ret;
			}
		}
	}
	else if(response_failed)
	{
		::IEEE2654::IEEE2654Error err = ::IEEE2654::IEEE2654Error();
		err.ParseFromString(value);
		err.set_uid(my_inst->translator_uid);
		err.set_code(translator_response_failed);
		::IEEE2654::IEEE2654Message wrapper = ::IEEE2654::IEEE2654Message();
		wrapper.set_uid(my_inst->translator_uid);
		wrapper.set_metaname("ERROR");
		wrapper.set_serialized(err.SerializeAsString());
		int ret = __sendInjectResponse(wrapper);
		return ret;
	}
	else
	{
		my_inst->error_code = translator_unknown_metaname;
		my_inst->status_code = translator_failed;
		int ret = __sendInjectErrorResponse(__FILE__, __LINE__,
				get_error_string());
		return ret;
	}
}

int ILTestDisplay::apply( ) {
	SWDEBUG1( struct inject_instance, my_inst, "ILTestDisplay::apply" );
	return 0;
}

int ILTestDisplay::__parse_config( char* json_message )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplay::__parse_config",
			" char* ");
	// 1. Parse a JSON text string to a document.
	/* json_message should be in the form:
	 * {
	 * 	"properties" : {
	 * 		"visible" : "true",
	 * 		"sticky" : "false",
	 * 		"observable" : "true"
	 * 	}
	 * }
	 */
	int rval1 = -1, rval2 = -1, rval3 = -1, rval5 = -1;
	rapidjson::Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
	
	// In-situ parsing, decode strings directly in the source string.
	// Source must be string.
	char buffer[strlen(json_message)+1];
	memcpy(buffer, json_message, strlen(json_message)+1);
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
	if(rval3) return rval3;
	if(rval2) return rval2;
	if(rval1) return rval1;
	return 0;
}

int ILTestDisplay::__setVisible( const char* val )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplay::__setVisible",
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

int ILTestDisplay::__setSticky( const char* val )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplay::__setSticky",
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

int ILTestDisplay::__setObservable( const char* val )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplay::__setObservable",
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

int ILTestDisplay::__setFunction( const char* val )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplay::__setFunctio0n",
			" const char* ");
	function = std::string(val);
	return 0;
}

int ILTestDisplay::__sendRequest( ::IEEE2654::IEEE2654Message& wrapper )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestDisplay::__sendRequest",
			" ::IEEE2654::IEEE2654Message& ");
	std::string s = std::string(wrapper.SerializeAsString());
	return ti_api->send_request(my_inst, my_inst->translator_uid, s.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(s.c_str())));
}

int ILTestDisplay::__sendInjectResponse( ::IEEE2654::IEEE2654Message& wrapper )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestDisplay::__sendInjectResponse",
			" ::IEEE2654::IEEE2654Message& ");
	std::string s = wrapper.SerializeAsString();
	return ti_api->send_inject_response(my_inst, my_inst->translator_uid, s.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(s.c_str())));
}

int ILTestDisplay::__sendInjectErrorResponse(const char* file, int line, const char* message)
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestDisplay::__sendInjectErrorResponse",
			" ::IEEE2654::IEEE2654Message& ");
	::IEEE2654::IEEE2654Error err = ::IEEE2654::IEEE2654Error();
	err.set_uid(my_inst->translator_uid);
	std::string s("Error <");
	s += message;
	s += ">\n\tdetected in file: ";
	s += file;
	s += "\n\tat line: ";
	s += std::to_string(line);
	s += ".\n";
	err.set_message(s);
	err.set_code(my_inst->error_code);
	::IEEE2654::IEEE2654Message wrapper = ::IEEE2654::IEEE2654Message();
	wrapper.set_uid(my_inst->translator_uid);
	wrapper.set_metaname("DISPLAY");
	wrapper.set_serialized(err.SerializeAsString());
	wrapper.set_message_type(IEEE2654::RESPONSE);
	int ret = __sendInjectResponse(wrapper);
	return ret;
}

