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

static const char __authors__[] = "Bradford G. Van Treuren";
static const char __contact__[] = "bradvt59@gmail.com";
static const char __copyright__[] = "Copyright (C) 2024, Bradford G. Van Treuren";
static const char __credits__[] = "Bradford G. Van Treuren";
static const char __date__[] = "2024/05/04";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "TLTestController.hpp"
#include "rapidjson/document.h" // rapidjason's DOM-style API
#include <sstream>

#include "debug/SwDebugLib.hpp"

TLTestController::TLTestController()
{
	SWDEBUG1( struct transform_instance, NULL, "TLTestController::TLTestController" );
	my_inst = (transform_instance*)0;
	tt_api = (translator_transform_api*)0;
	sticky = true;
	observable = true;
	display = "0";
}

TLTestController::~TLTestController()
{
	SWDEBUG1( struct transform_instance, NULL, "TLTestController::~TLTestController" );
}

int TLTestController::open( struct transform_instance* inst, struct translator_transform_api* tt_api )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestController::open",
			" struct transform_instance*, struct translator_inject_api* ");
	my_inst = inst;
	this->tt_api = tt_api;
	my_inst->translator_api = tt_api;
	my_inst->error_code = translator_success;
	my_inst->status_code = translator_ok;
	my_inst->visible = true;
	my_inst->child_uid = 0;
	my_inst->children_uids = NULL;
	translator_error_strings = tt_api->get_translator_error_strings();
	translator_status_strings = tt_api->get_translator_status_strings();
	my_inst->num_children = 0;
	return 0;
}

int TLTestController::close( )
{
	SWDEBUG1( struct transform_instance, NULL, "TLTestController::close" );
	return 0;
}

int TLTestController::config( char* json_message )
{
	SWDEBUG1( struct transform_instance, NULL, "TLTestController::config" );
	std::string note = "json_message = ";
	note += json_message;
	SWDEBUG_LOG(__FILE__, note);
	return __parse_config(json_message);
}

int TLTestController::select( uint32_t index )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestController::select",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int TLTestController::deselect( uint32_t index )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestController::deselect",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

bool TLTestController::is_selected( uint32_t uid )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestController::is_selected",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

enum translator_error_code TLTestController::get_error_code( )
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestController::get_error_code" );
	return my_inst->error_code;
}

const char* TLTestController::get_error_string( )
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestController::get_error_string" );
	return translator_error_strings[my_inst->error_code];
}

enum translator_status TLTestController::get_status_code( )
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestController::get_status_code" );
	return my_inst->status_code;
}

const char* TLTestController::get_status_string( )
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestController::get_status_string" );
	return translator_status_strings[my_inst->status_code];
}

int TLTestController::handle_request( size_t len, uint8_t* message )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestController::handle_request",
			" size_t, uint8_t* ");
	// Deserialize the channel wrapper message
	std::string s(reinterpret_cast<const char*>(message), len);
	std::cerr << "s = " << s << std::endl;
	::IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(s);
	my_inst->child_uid = rvf.uid();
	if(rvf.metaname() == "EXPR")
	{
		return __handle_expr_request(rvf);
	}
	else if(rvf.metaname() == "READ")
	{
		return __handle_read_request(rvf);
	}
	else if(rvf.metaname() == "SHOW")
	{
		return __handle_show_request(rvf);
	}
	else
	{
		my_inst->error_code = translator_unknown_metaname;
		my_inst->status_code = translator_failed;
		return __send_error_response(__FILE__, __LINE__, get_error_string());
	}
}

int TLTestController::handle_response( size_t len, uint8_t* message )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestController::handle_response",
			" size_t, uint8_t* ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int TLTestController::apply( ) {
	SWDEBUG1( struct transform_instance, my_inst, "TLTestController::apply" );
	// Nothing to do
	return 0;
}

int TLTestController::__parse_config( char* json_message )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestController::__parse_config",
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

int TLTestController::__setVisible( const char* val )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestController::__setVisible",
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

int TLTestController::__setSticky( const char* val )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestController::__setSticky",
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

int TLTestController::__setObservable( const char* val )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestController::__setObservable",
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

int TLTestController::__handle_expr_request(::IEEE2654::IEEE2654Message& wrapper)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestController::__handle_expr_request",
			" ::IEEE2654::IEEE2654Message& ");
	std::string result;
	// Compute the expression and return the result in the response
	exp.ParseFromString(wrapper.serialized());
	// Find type (int or float) of operands
	std::string operand1(exp.operand1());
	std::string operand2(exp.operand2());
	std::stringstream ss;
	if(operand1.find('.') == std::string::npos)
	{
		// operand1 is an integer
		if(operand2.find('.') == std::string::npos)
		{
			// operand2 is an integer
			int o2 = std::stoi(operand2);
			int o1 = std::stoi(operand1);
			if(exp.op() == "+")
			{
				int r = o1 + o2;
				ss << r;
				ss >> result;
			}
			else if(exp.op() == "-")
			{
				int r = o1 - o2;
				ss << r;
				ss >> result;
			}
			else if(exp.op() == "*")
			{
				int r = o1 * o2;
				ss << r;
				ss >> result;
			}
			else if(exp.op() == "/")
			{
				int r = o1 / o2;
				ss << r;
				ss >> result;
			}
			else
			{
				result = "";
			}
		}
		else
		{
			// operand2 is a float
			float o2 = std::stof(operand2);
			int o1 = std::stof(operand1);
			if(exp.op() == "+")
			{
				float r = o1 + o2;
				ss << r;
				ss >> result;
			}
			else if(exp.op() == "-")
			{
				float r = o1 - o2;
				ss << r;
				ss >> result;
			}
			else if(exp.op() == "*")
			{
				float r = o1 * o2;
				ss << r;
				ss >> result;
			}
			else if(exp.op() == "/")
			{
				float r = o1 / o2;
				ss << r;
				ss >> result;
			}
			else
			{
				result = "";
			}
		}
	}
	else
	{
		// operand1 is a float
		if(operand2.find('.') == std::string::npos)
		{
			// operand2 is an integer
			int o2 = atoi(operand2.c_str());
			float o1 = atof(operand1.c_str());
			if(exp.op() == "+")
			{
				float r = o1 + o2;
				ss << r;
				ss >> result;
			}
			else if(exp.op() == "-")
			{
				float r = o1 - o2;
				ss << r;
				ss >> result;
			}
			else if(exp.op() == "*")
			{
				float r = o1 * o2;
				ss << r;
				ss >> result;
			}
			else if(exp.op() == "/")
			{
				float r = o1 / o2;
				ss << r;
				ss >> result;
			}
			else
			{
				result = "";
			}
		}
		else
		{
			// operand2 is a float
			float o2 = atof(operand2.c_str());
			float o1 = atof(operand1.c_str());
			if(exp.op() == "+")
			{
				float r = o1 + o2;
				ss << r;
				ss >> result;
			}
			else if(exp.op() == "-")
			{
				float r = o1 - o2;
				ss << r;
				ss >> result;
			}
			else if(exp.op() == "*")
			{
				float r = o1 * o2;
				ss << r;
				ss >> result;
			}
			else if(exp.op() == "/")
			{
				float r = o1 / o2;
				ss << r;
				ss >> result;
			}
			else
			{
				result = "";
			}
		}
	}
	display = result;
	exp.set_result(result);
	std::string resp;
	exp.SerializeToString(&resp);
	wrapper.set_serialized(resp);
	return __send_response(wrapper);
}

int TLTestController::__handle_read_request(::IEEE2654::IEEE2654Message& wrapper)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestController::__handle_read_request",
			" ::IEEE2654::IEEE2654Message& ");
	::DISPLAY::READ disp;
	disp.ParseFromString(wrapper.serialized());
	disp.set_value(display);
	std::string resp;
	disp.SerializeToString(&resp);
	wrapper.set_serialized(resp);
	return __send_response(wrapper);
}

int TLTestController::__handle_show_request(::IEEE2654::IEEE2654Message& wrapper)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestController::__handle_show_request",
			" ::IEEE2654::IEEE2654Message& ");
	::DISPLAY::SHOW disp;
	disp.ParseFromString(wrapper.serialized());
	disp.set_value(display);
	std::string resp;
	disp.SerializeToString(&resp);
	wrapper.set_serialized(resp);
	return __send_response(wrapper);
}

int TLTestController::__send_error_response( const char* file, int line, const char* message )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestController::__send_error_response",
			" ::IEEE2654::IEEE2654Message& ");
        ::IEEE2654::IEEE2654Error err = ::IEEE2654::IEEE2654Error();
        err.set_uid(my_inst->child_uid);
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
        wrapper.set_uid(my_inst->child_uid);
        wrapper.set_metaname("IEEE2654Error");
        wrapper.set_serialized(err.SerializeAsString());
        wrapper.set_message_type(IEEE2654::RESPONSE);
        int ret = __send_response(wrapper);
        return ret;
}

int TLTestController::__send_response( ::IEEE2654::IEEE2654Message& wrapper )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestController::__send_request",
			" ::IEEE2654::IEEE2654Message& ");
	std::string s = wrapper.SerializeAsString();
	// Translator has not yet been registered with Repository so can't log
	// return td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
        return tt_api->send_response(my_inst, my_inst->child_uid, s.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(s.c_str())));
}
