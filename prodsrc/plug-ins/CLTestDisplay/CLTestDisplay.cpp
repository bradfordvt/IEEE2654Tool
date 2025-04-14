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

#include "CLTestDisplay.hpp"
#include "rapidjson/document.h" // rapidjason's DOM-style API
#include "IEEE2654.pb.h"
#include "Imperative_DISPLAY.pb.h"
#include "Command_DISPLAY.pb.h"

#include "debug/SwDebugLib.hpp"

CLTestDisplay::CLTestDisplay()
{
	SWDEBUG1( struct command_instance, NULL, "CLTestDisplay::CLTestDisplay" );
	my_inst = (command_instance*)0;
	tc_api = (translator_command_api*)0;
	sticky = true;
	observable = true;
	response_received = false;
	value = "0";
	function = std::string("UNDEFINED");
}

CLTestDisplay::~CLTestDisplay()
{
	SWDEBUG1( struct command_instance, NULL, "CLTestDisplay::~CLTestDisplay" );
}

int CLTestDisplay::open( struct command_instance* inst, struct translator_command_api* tc_api_ )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplay::open",
			" struct command_instance*, struct translator_inject_api* ");
	my_inst = inst;
	tc_api = tc_api_;
	my_inst->translator_api = tc_api;
	my_inst->error_code = translator_success;
	my_inst->status_code = translator_ok;
	my_inst->visible = true;
	my_inst->child_uid = 0;
	my_inst->children_uids = NULL;
	my_inst->num_children = 0;
	return 0;
}

int CLTestDisplay::close( )
{
	SWDEBUG1( struct command_instance, NULL, "CLTestDisplay::close" );
	return 0;
}

int CLTestDisplay::config( char* json_message )
{
	SWDEBUG1( struct command_instance, NULL, "CLTestDisplay::config" );
	std::string note = "json_message = ";
	note += json_message;
	SWDEBUG_LOG(__FILE__, note);
	return __parse_config(json_message);
}

enum translator_error_code CLTestDisplay::get_error_code( )
{
	SWDEBUG1( struct command_instance, my_inst, "CLTestDisplay::get_error_code" );
	return my_inst->error_code;
}

const char* CLTestDisplay::get_error_string( )
{
	SWDEBUG1( struct command_instance, my_inst, "CLTestDisplay::get_error_string" );
	return translator_error_strings[my_inst->error_code];
}

enum translator_status CLTestDisplay::get_status_code( )
{
	SWDEBUG1( struct command_instance, my_inst, "CLTestDisplay::get_status_code" );
	return my_inst->status_code;
}

const char* CLTestDisplay::get_status_string( )
{
	SWDEBUG1( struct command_instance, my_inst, "CLTestDisplay::get_status_string" );
	return translator_status_strings[my_inst->status_code];
}

int CLTestDisplay::handle_command_request( size_t len, uint8_t* message )
{
	SWDEBUG2( struct command_instance, my_inst, "CLTestDisplay::handle_command_request",
			" size_t, uint8_t* ");
	std::string s(reinterpret_cast<const char*>(message), len);
        IEEE2654::IEEE2654Message msg = ::IEEE2654::IEEE2654Message();
        msg.ParseFromString(s);
	std::string ss(msg.serialized());
        // msg.ParseFromArray((void*)message, len);
	// std::cerr << "msg.serialized() = " << msg.serialized() << std::endl;
        if(msg.metaname() == "DISPLAY")
        {
                ::Imperative_DISPLAY::DISPLAY disp = ::Imperative_DISPLAY::DISPLAY();
                disp.ParseFromString(ss);
                if(disp.function() == "SHOW")
		{
			::Command_DISPLAY::SHOW show = ::Command_DISPLAY::SHOW();
			show.set_uid(my_inst->translator_uid);
			show.set_value(disp.value());
			std::string serialized_message;
			show.SerializeToString(&serialized_message);
			response_received = false;
			int ret = __send_inject_request("SHOW", serialized_message);
			if(ret != 0)
			{
				my_inst->error_code = translator_message_error;
				my_inst->status_code = translator_failed;
				int ret1 = __sendImperativeErrorResponse(__FILE__, __LINE__, "The request for SHOW returned an error code");
				return ret1;
			}
			else
			{
				if(response_received == true) {
					disp.set_value(value);
					disp.SerializeToString(&serialized_message);
					int ret2 = __sendImperativeResponse("DISPLAY", serialized_message);
					return ret2;
				}
				else {
					SWDEBUG_LOG(__FILE__, "CLTestDisplay::handle_command_request(): btn.function ERROR 1");
					my_inst->error_code = translator_message_error;
					my_inst->status_code = translator_failed;
					int ret3 = __sendImperativeErrorResponse(__FILE__, __LINE__, "The DISPLAY function was not SHOW");
					return ret3;

				}
			}
		}
		else if(disp.function() == "READ")
		{
			::Command_DISPLAY::READ read = ::Command_DISPLAY::READ();
			read.set_uid(my_inst->translator_uid);
			read.set_value(disp.value());
			std::string serialized_message;
			read.SerializeToString(&serialized_message);
			response_received = false;
			int ret = __send_inject_request("READ", serialized_message);
			if(ret != 0)
			{
				my_inst->error_code = translator_message_error;
				my_inst->status_code = translator_failed;
				int ret1 = __sendImperativeErrorResponse(__FILE__, __LINE__, "The request for READ returned an error code");
				return ret1;
			}
			else
			{
				if(response_received == true) {
					int ret2 = __sendImperativeResponse("DISPLAY", ss);
					return ret2;
				}
				else {
					SWDEBUG_LOG(__FILE__, "CLTestDisplay::handle_command_request(): btn.function ERROR 1");
					my_inst->error_code = translator_message_error;
					my_inst->status_code = translator_failed;
					int ret3 = __sendImperativeErrorResponse(__FILE__, __LINE__, "The DISPLAY function was not READ");
					return ret3;
				}

			}
		}
		else
                {
                        my_inst->error_code = translator_message_error;
                        my_inst->status_code = translator_failed;
                        int ret = __sendImperativeErrorResponse(__FILE__, __LINE__, "The DISPLAY function was not SHOW or READ");
                        return ret;
                }
	}
	else
        {
                my_inst->error_code = translator_message_error;
                my_inst->status_code = translator_failed;
                int ret = __sendImperativeErrorResponse(__FILE__, __LINE__, "The metaname was not DISPLAY");
                return ret;
        }
}

int CLTestDisplay::handle_inject_response( size_t len, uint8_t* message )
{
	SWDEBUG2( struct command_instance, my_inst, "CLTestDisplay::handle_inject_response",
			" size_t, uint8_t* ");
        IEEE2654::IEEE2654Message msg = ::IEEE2654::IEEE2654Message();
        msg.ParseFromString(std::string(reinterpret_cast<const char*>(message), len));
	response_received = true;
        if(msg.metaname() == "SHOW")
        {
		::Command_DISPLAY::SHOW show = ::Command_DISPLAY::SHOW();
                show.ParseFromString(msg.serialized());
		if(show.uid() == my_inst->translator_uid)
		{
			my_inst->error_code = translator_success;
			my_inst->status_code = translator_ok;
			value = show.value();
			return 0;
		}
		else
		{
			my_inst->error_code = translator_response_failed;
			my_inst->status_code = translator_failed;
			__logger(ERROR, __FILE__, __LINE__, "The COMMAND uid does not match the Translator defined uid");
			return -2;
		}
	}
	else if(msg.metaname() == "READ")
        {
		::Command_DISPLAY::READ read = ::Command_DISPLAY::READ();
                read.ParseFromString(msg.serialized());
		if(read.uid() == my_inst->translator_uid)
		{
			my_inst->error_code = translator_success;
			my_inst->status_code = translator_ok;
			return 0;
		}
		else
		{
			my_inst->error_code = translator_response_failed;
			my_inst->status_code = translator_failed;
			__logger(ERROR, __FILE__, __LINE__, "The COMMAND uid does not match the Translator defined uid");
			return -2;
		}
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
                my_inst->error_code = translator_message_error;
                my_inst->status_code = translator_failed;
                return -6;
	}
}

int CLTestDisplay::apply( ) {
	SWDEBUG1( struct command_instance, my_inst, "CLTestDisplay::apply" );
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

int CLTestDisplay::__send_inject_request( const char* metaname, std::string& msg )
{
	SWDEBUG2( struct command_instance, my_inst, "CLTestDisplay::__send_inject_request",
			" const char*, std::string& ");
	::IEEE2654::IEEE2654Message wrapper = ::IEEE2654::IEEE2654Message();
	wrapper.set_uid(my_inst->translator_uid);
	wrapper.set_metaname(metaname);
	wrapper.set_serialized(msg);
	std::string serialized_message;
	wrapper.SerializeToString(&serialized_message);
	return tc_api->send_inject_request(my_inst, my_inst->translator_uid, serialized_message.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(serialized_message.c_str())));
}

int CLTestDisplay::__sendImperativeResponse( const char* metaname, std::string& message )
{
	SWDEBUG2( struct command_instance, my_inst, "CLTestDisplay::__sendImperativeResponse",
			" const char*, std::string& ");
	::IEEE2654::IEEE2654Message wrapper = ::IEEE2654::IEEE2654Message();
	wrapper.set_uid(my_inst->translator_uid);
	wrapper.set_metaname(metaname);
	wrapper.set_serialized(message);
	std::string serialized_message;
	wrapper.SerializeToString(&serialized_message);
	return tc_api->send_command_response(my_inst, my_inst->translator_uid, serialized_message.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(serialized_message.c_str())));
}

int CLTestDisplay::__sendImperativeErrorResponse( const char* file, int line, const char* message )
{
	SWDEBUG2( struct command_instance, my_inst, "CLTestDisplay::__sendImperativeErrorResponse",
			" const char*, int, const char* ");
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
	wrapper.set_metaname("IEEE2654Error");
	wrapper.set_serialized(serialized_error);
	std::string sm;
	wrapper.SerializeToString(&sm);
	std::cerr << "sm = " << sm << std::endl;
	return tc_api->send_command_response(my_inst, my_inst->translator_uid, sm.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(sm.c_str())));
}

int CLTestDisplay::__parse_config( char* json_message )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplay::__parse_config",
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
	int rval1 = -1, rval2 = -1, rval3 = -1;
	rapidjson::Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
	
	// In-situ parsing, decode strings directly in the source string.
	// Source must be string.
	char buffer[strlen(json_message)+1];
	memcpy(buffer, json_message, strlen(json_message)+1);
	std::cerr << "buffer = " << buffer << std::endl;
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

int CLTestDisplay::__setVisible( const char* val )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplay::__setVisible",
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

int CLTestDisplay::__setSticky( const char* val )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplay::__setSticky",
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

int CLTestDisplay::__setObservable( const char* val )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplay::__setObservable",
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

int CLTestDisplay::__setFunction( const char* val )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplay::__setFunction",
			" const char* ");
	function = std::string(val);
	return 0;
}

int CLTestDisplay::__logger(LOG_TYPE lt, const char* filename, int line, const char* message) {
	SWDEBUG2( struct command_instance, my_inst, "CLTestDisplay::__logger",
			" LOG_TYPE, const char*, int, const char* ");
        std::string err_msg("CLTestDisplay::__logger(): ");
        if(lt == FATAL) err_msg += "Fatal error ";
        else if(lt == ERROR) err_msg += "Error ";
        else if(lt == WARNING) err_msg += "Warning ";
        else if(lt == DEBUG) err_msg += "A DEBUG message ";
        else if(lt == NOTICE) err_msg += "A NOTICE message ";
        else err_msg += "Unknown ";
        err_msg += "detected at\nFile(";
        err_msg += filename;
        err_msg += ") at\nLine(";
        err_msg += int(line);
        err_msg += ") found\nSymptom(";
        err_msg += message;
        err_msg += ")";
        return tc_api->logger(my_inst, lt, err_msg.c_str());
}

