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

#include "ILTestLeaf.hpp"
#include "rapidjson/document.h" // rapidjason's DOM-style API
#include "IEEE2654.pb.h"
#include "BUTTON.pb.h"
#include "Command_BUTTON.pb.h"

#include "debug/SwDebugLib.hpp"

// Needed to satisfy Protobuf linking
const char protobuf_c_empty_string[] = "";

ILTestLeaf::ILTestLeaf()
{
	SWDEBUG1( struct inject_instance, NULL, "ILTestLeaf::ILTestLeaf" );
	my_inst = (inject_instance*)0;
	ti_api = (translator_inject_api*)0;
	visible = true;
	sticky = true;
	observable = true;
	response_received = false;
	function = std::string("UNDEFINED");
	std::cerr << "Exiting class ILTestLeaf::ILTestLeaf()" << std::endl;
}

ILTestLeaf::~ILTestLeaf()
{
	SWDEBUG1( struct inject_instance, NULL, "ILTestLeaf::~ILTestLeaf" );
}

int ILTestLeaf::open( struct inject_instance* inst, struct translator_inject_api* ti_api )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestLeaf::open",
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
	std::cerr << "Exiting class ILTestLeaf::open()" << std::endl;
	return 0;
}

int ILTestLeaf::close( )
{
	SWDEBUG1( struct inject_instance, NULL, "ILTestLeaf::close" );
	return 0;
}

int ILTestLeaf::config( char* json_message )
{
	SWDEBUG1( struct inject_instance, NULL, "ILTestLeaf::config" );
	std::string note = "json_message = ";
	note += json_message;
	SWDEBUG_LOG(__FILE__, note);
        // std::cerr << "json_message = " << json_message << std::endl;
	return __parse_config(json_message);
}

int ILTestLeaf::select( uint32_t index )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestLeaf::select",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int ILTestLeaf::deselect( uint32_t index )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestLeaf::deselect",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

bool ILTestLeaf::is_selected( uint32_t uid )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestLeaf::is_selected",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

enum translator_error_code ILTestLeaf::get_error_code( )
{
	SWDEBUG1( struct inject_instance, my_inst, "ILTestLeaf::get_error_code" );
	return my_inst->error_code;
}

const char* ILTestLeaf::get_error_string( )
{
	SWDEBUG1( struct inject_instance, my_inst, "ILTestLeaf::get_error_string" );
	return translator_error_strings[my_inst->error_code];
}

enum translator_status ILTestLeaf::get_status_code( )
{
	SWDEBUG1( struct inject_instance, my_inst, "ILTestLeaf::get_status_code" );
	return my_inst->status_code;
}

const char* ILTestLeaf::get_status_string( )
{
	SWDEBUG1( struct inject_instance, my_inst, "ILTestLeaf::get_status_string" );
	return translator_status_strings[my_inst->status_code];
}

int ILTestLeaf::handle_request( size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestLeaf::handle_request",
			" size_t, uint8_t* ");
	// This is a leaf node, thus no children to send a request
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int ILTestLeaf::handle_response( size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestLeaf::handle_response",
			" size_t, uint8_t* ");
	IEEE2654::IEEE2654Message msg = ::IEEE2654::IEEE2654Message();
	msg.ParseFromString(std::string((const char*)message, len));
	response_received = true;
	if(msg.metaname() == "PRESS")
	{
		::BUTTON::PRESS btn = ::BUTTON::PRESS();
		btn.ParseFromString(msg.serialized());
		if(btn.function() != function)
		{
			my_inst->error_code = translator_message_error;
			my_inst->status_code = translator_failed;
			__logger(ERROR, __FILE__, __LINE__, "The BUTTON function does not match the Translator defined function");

			return -1;
		}
		if(btn.uid() != my_inst->translator_uid)
		{
			my_inst->error_code = translator_message_error;
			my_inst->status_code = translator_failed;
			__logger(ERROR, __FILE__, __LINE__, "The BUTTON uid does not match the Translator defined uid");
			return -2;
		}
		my_inst->error_code = translator_success;
		my_inst->status_code = translator_ok;
		return 0;
	}
	else if(msg.metaname() == "IEEE2654Error")
	{
		my_inst->error_code = translator_response_failed;
		my_inst->status_code = translator_failed;
		std::string err_msg("IEEE2654Error message received with message\n\"");
		::IEEE2654::IEEE2654Error err = ::IEEE2654::IEEE2654Error();
		err.ParseFromString(msg.serialized());
		err_msg += err.message();
		err_msg += "\"";
		__logger(ERROR, __FILE__, __LINE__, err_msg.c_str());
		return -5;
	}
	else
	{
		my_inst->error_code = translator_unknown_metaname;
		my_inst->status_code = translator_failed;
		__logger(ERROR, __FILE__, __LINE__, get_error_string());
		return -6;
	}
}

int ILTestLeaf::handle_update_request( size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestLeaf::handle_update_request",
			" size_t, uint8_t* ");
	// This is a leaf node that does not have a value that can be updated
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int ILTestLeaf::handle_update_response( size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestLeaf::handle_update_response",
			" size_t, uint8_t* ");
	// This is a leaf node that does not have a value that can be updated
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int ILTestLeaf::handle_inject_request( size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestLeaf::handle_inject_request",
			" size_t, uint8_t* ");
	IEEE2654::IEEE2654Message msg = ::IEEE2654::IEEE2654Message();
	msg.ParseFromString(std::string((const char*)message, len));
	if(msg.metaname() == "PRESS")
	{
		::Command_BUTTON::PRESS cmd = ::Command_BUTTON::PRESS();
		cmd.ParseFromString(msg.serialized());
		::BUTTON::PRESS btn = ::BUTTON::PRESS();
		btn.set_uid(my_inst->translator_uid);
		btn.set_function(function);
		::IEEE2654::IEEE2654Message wrapper = ::IEEE2654::IEEE2654Message();
		wrapper.set_uid(my_inst->translator_uid);
		wrapper.set_metaname("PRESS");
		wrapper.set_serialized(btn.SerializeAsString());
		int ret = __sendRequest(wrapper);
		if(ret != 0) {
			int ret1 = __sendInjectErrorResponse(__FILE__, __LINE__,
					get_error_string());
			return ret1;
		}
		else {
			if(response_received == true) {
				int ret3 = __sendInjectResponse(msg);
				return ret3;
			}
			else {
				my_inst->error_code = translator_response_failed;
				my_inst->status_code = translator_failed;
				int ret4 = __sendInjectErrorResponse(__FILE__, __LINE__,
						get_error_string());
				return ret4;
			}
		}
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

int ILTestLeaf::apply( ) {
	SWDEBUG1( struct inject_instance, my_inst, "ILTestLeaf::apply" );
	return 0;
}

int ILTestLeaf::__parse_config( char* json_message )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestLeaf::__parse_config",
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
	int rval1 = -1, rval2 = -1, rval3 = -1, rval4 = -1, rval5 = -1;
	rapidjson::Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
	
	// In-situ parsing, decode strings directly in the source string.
	// Source must be string.
	char buffer[strlen(json_message)+1];
	memcpy(buffer, json_message, strlen(json_message)+1);
	// std::cerr << "ILTestLeaf::__parse(): buffer = " << buffer << std::endl;
	if(document.ParseInsitu(buffer).HasParseError())
	{
		my_inst->error_code = translator_format_error;
		my_inst->status_code = translator_broken;
		SWDEBUG_LOG( __FILE__, "ILTestLeaf::__parse(): HasParseError");
		return -1;
	}
	// Parsing to document succeeded

	// 2. Access values in document.
	if(!document.IsObject())
	{
		my_inst->error_code = translator_format_error;
		my_inst->status_code = translator_broken;
		SWDEBUG_LOG(__FILE__, "ILTestLeaf::__parse(): !document.IsObject()" );
		return -1;
	}
	const rapidjson::Value& properties = document["properties"]; // Using a reference for consecutive access is handy and faster.
	if(!properties.IsObject())
	{
		my_inst->error_code = translator_format_error;
		my_inst->status_code = translator_broken;
		SWDEBUG_LOG(__FILE__, "ILTestLeaf::__parse(): !properties.IsObject()");
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

int ILTestLeaf::__setVisible( const char* val )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestLeaf::__setVisible",
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

int ILTestLeaf::__setSticky( const char* val )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestLeaf::__setSticky",
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

int ILTestLeaf::__setObservable( const char* val )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestLeaf::__setObservable",
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

int ILTestLeaf::__setFunction( const char* val )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestLeaf::__setFunction",
			" const char* ");
	function = std::string(val);
	return 0;
}

int ILTestLeaf::__sendRequest( ::IEEE2654::IEEE2654Message& wrapper )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestLeaf::__sendRequest",
			" ::IEEE2654::IEEE2654Message& ");
	std::string s = std::string(wrapper.SerializeAsString());
	return ti_api->send_request(my_inst, my_inst->translator_uid, s.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(s.c_str())));
}

int ILTestLeaf::__sendInjectResponse( ::IEEE2654::IEEE2654Message& wrapper )
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestLeaf::__sendInjectResponse",
			" ::IEEE2654::IEEE2654Message& ");
	std::string s = wrapper.SerializeAsString();
	return ti_api->send_inject_response(my_inst, my_inst->translator_uid, s.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(s.c_str())));
}

int ILTestLeaf::__sendInjectErrorResponse(const char* file, int line, const char* message)
{
	SWDEBUG2( struct inject_instance, my_inst, "ILTestLeaf::__sendInjectErrorResponse",
			" const char*, int, const char* ");
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
	wrapper.set_metaname("IEEE2654ERROR");
	wrapper.set_serialized(err.SerializeAsString());
	wrapper.set_message_type(IEEE2654::RESPONSE);
	int ret = __sendInjectResponse(wrapper);
	return ret;
}

int ILTestLeaf::__logger(LOG_TYPE lt, const char* filename, int line, const char* message) {
	SWDEBUG2( struct inject_instance, my_inst, "ILTestLeaf::__logger",
			" LOG_TYPE, const char*, int, const char* ");
	std::string err_msg("ILTestLeaf::handle_response(): ");
	if(lt == FATAL) err_msg += "Fatal error ";
	else if(lt == ERROR) err_msg += "Error ";
	else if(lt == WARNING) err_msg += "Warning ";
	else if(lt == DEBUG) err_msg += "A DEBUG message ";
	else if(lt == NOTICE) err_msg += "A NOTICE message ";
	else err_msg += "Unknown ";
	err_msg += "detected at\nFile(";
	err_msg += filename;
	err_msg += ") at\nLine(";
	err_msg += line;
	err_msg += ") found\nSymptom(";
	err_msg += message;
	err_msg += ")";
	return ti_api->logger(my_inst, lt, err_msg.c_str());
}

