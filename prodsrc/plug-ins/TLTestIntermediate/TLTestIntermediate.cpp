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

static const char __authors__[] = "Bradford G. Van Treuren";
static const char __contact__[] = "bradvt59@gmail.com";
static const char __copyright__[] = "Copyright (C) 2024, Bradford G. Van Treuren";
static const char __credits__[] = "Bradford G. Van Treuren";
static const char __date__[] = "2024/05/01";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "TLTestIntermediate.hpp"
#include "rapidjson/document.h" // rapidjason's DOM-style API
#include <iostream>

#include "debug/SwDebugLib.hpp"

TLTestIntermediate::TLTestIntermediate() : stk()
{
	SWDEBUG1( struct transform_instance, NULL, "TLTestIntermediate::TLTestIntermediate" );
	my_inst = (transform_instance*)0;
	tt_api = (translator_transform_api*)0;
	sticky = true;
	observable = true;
	response_received = false;
	equation = std::string("");
	result = std::string("");
	input = std::string("");
}

TLTestIntermediate::~TLTestIntermediate()
{
	SWDEBUG1( struct transform_instance, NULL, "TLTestIntermediate::~TLTestIntermediate" );
}

int TLTestIntermediate::open( struct transform_instance* inst, struct translator_transform_api* _tt_api )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestIntermediate::open",
			" struct transform_instance*, struct translator_inject_api* ");
	my_inst = inst;
	tt_api = _tt_api;
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

int TLTestIntermediate::close( )
{
	SWDEBUG1( struct transform_instance, NULL, "TLTestIntermediate::close" );
	return 0;
}

int TLTestIntermediate::config( char* json_message )
{
	SWDEBUG1( struct transform_instance, NULL, "TLTestIntermediate::config" );
	std::string note = "json_message = ";
	note += json_message;
	SWDEBUG_LOG(__FILE__, note);
	return __parse_config(json_message);
}

int TLTestIntermediate::select( uint32_t /* index */ )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::select",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int TLTestIntermediate::deselect( uint32_t /* index */ )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::deselect",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

bool TLTestIntermediate::is_selected( uint32_t /* uid */ )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::is_selected",
			" uint32_t ");
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

enum translator_error_code TLTestIntermediate::get_error_code( )
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestIntermediate::get_error_code" );
	return my_inst->error_code;
}

const char* TLTestIntermediate::get_error_string( )
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestIntermediate::get_error_string" );
	return translator_error_strings[my_inst->error_code];
}

enum translator_status TLTestIntermediate::get_status_code( )
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestIntermediate::get_status_code" );
	return my_inst->status_code;
}

const char* TLTestIntermediate::get_status_string( )
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestIntermediate::get_status_string" );
	return translator_status_strings[my_inst->status_code];
}

int TLTestIntermediate::handle_request( size_t len, uint8_t* message )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::handle_request",
			" size_t, uint8_t* ");
	// Deserialize the channel wrapper message
	std::string s(reinterpret_cast<const char*>(message), len);
	IEEE2654::IEEE2654Message wrapper;
	wrapper.ParseFromString(s);
	my_inst->child_uid = wrapper.uid();
	if(wrapper.metaname() == "PRESS")
	{
		::BUTTON::PRESS btn = ::BUTTON::PRESS();
		btn.ParseFromString(wrapper.serialized());
		if(btn.function() == "ZERO")
		{
			return __handle_digit_request(std::string("0"), wrapper.serialized());
		}
		else if(btn.function() == "ONE")
		{
			return __handle_digit_request(std::string("1"), wrapper.serialized());
		}
		else if(btn.function() == "TWO")
		{
			return __handle_digit_request(std::string("2"), wrapper.serialized());
		}
		else if(btn.function() == "THREE")
		{
			return __handle_digit_request(std::string("3"), wrapper.serialized());
		}
		else if(btn.function() == "FOUR")
		{
			return __handle_digit_request(std::string("4"), wrapper.serialized());
		}
		else if(btn.function() == "FIVE")
		{
			return __handle_digit_request(std::string("5"), wrapper.serialized());
		}
		else if(btn.function() == "SIX")
		{
			return __handle_digit_request(std::string("6"), wrapper.serialized());
		}
		else if(btn.function() == "SEVEN")
		{
			return __handle_digit_request(std::string("7"), wrapper.serialized());
		}
		else if(btn.function() == "EIGHT")
		{
			return __handle_digit_request(std::string("8"), wrapper.serialized());
		}
		else if(btn.function() == "NINE")
		{
			return __handle_digit_request(std::string("9"), wrapper.serialized());
		}
		else if(btn.function() == "ENTER")
		{
			return __handle_enter_request(wrapper.serialized());
		}
		else if(btn.function() == "PLUS")
		{
			return __handle_operator_request(std::string("+"), wrapper.serialized());
		}
		else if(btn.function() == "MINUS")
		{
			return __handle_operator_request(std::string("-"), wrapper.serialized());
		}
		else if(btn.function() == "MULTIPLY")
		{
			return __handle_operator_request(std::string("*"), wrapper.serialized());
		}
		else if(btn.function() == "DIVIDE")
		{
			return __handle_operator_request(std::string("/"), wrapper.serialized());
		}
		else if(btn.function() == "DOT")
		{
			return __handle_dot_request(wrapper.serialized());
		}
		else
		{
			my_inst->error_code = translator_message_error;
			my_inst->status_code = translator_failed;
			return __send_error_response();
		}
	}
	else if(wrapper.metaname() == "READ")
	{
		::DISPLAY::READ disp = ::DISPLAY::READ();
		if(disp.ParseFromString(wrapper.serialized())) {
			return __handle_read_request(disp);
		}
		else {
			my_inst->error_code = translator_message_error;
			my_inst->status_code = translator_failed;
			return __send_error_response();
		}
	}
	else if(wrapper.metaname() == "SHOW")
	{
		::DISPLAY::SHOW disp = ::DISPLAY::SHOW();
		if(disp.ParseFromString(wrapper.serialized())) {
			return __handle_show_request(disp);
		}
		else {
			my_inst->error_code = translator_message_error;
			my_inst->status_code = translator_failed;
			return __send_error_response();
		}
	}
	else {
		my_inst->error_code = translator_unknown_metaname;
		my_inst->status_code = translator_failed;
		return __send_error_response();
	}
}

int TLTestIntermediate::handle_response( size_t len, uint8_t* message )
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::handle_response",
			" size_t, uint8_t* ");
	// Deserialize the channel wrapper message
	::IEEE2654::IEEE2654Message wrapper;
	std::string s(reinterpret_cast<const char*>(message), len);
	wrapper.ParseFromString(s);
	// my_inst->child_uid = wrapper.uid();
	if(wrapper.metaname() == "EXPR")
	{
		// return __handle_expr_response(wrapper.serialized());
                response_received = true;
		return 0;
	}
	else if(wrapper.metaname() == "READ")
	{
		return __handle_read_response(wrapper.serialized());
	}
	else if(wrapper.metaname() == "SHOW")
	{
		return __handle_show_response(wrapper.serialized());
	}
	else
	{
		my_inst->error_code = translator_unknown_metaname;
		my_inst->status_code = translator_failed;
		std::string m("The msg.metaname was not EXPR but was ");
                m += wrapper.metaname();
                __logger(ERROR, __FILE__, __LINE__, m.c_str());
                response_received = true;
		return -1;
		// return __send_error_response();
	}
}

int TLTestIntermediate::apply( ) {
	SWDEBUG1( struct transform_instance, my_inst, "TLTestIntermediate::apply" );
	// Nothing to do
	return 0;
}

int TLTestIntermediate::__parse_config( char* json_message )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestIntermediate::__parse_config",
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

int TLTestIntermediate::__setVisible( const char* val )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestIntermediate::__setVisible",
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

int TLTestIntermediate::__setSticky( const char* val )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestIntermediate::__setSticky",
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

int TLTestIntermediate::__setObservable( const char* val )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestIntermediate::__setObservable",
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

int TLTestIntermediate::__handle_digit_request(const std::string& value, const std::string& button)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::__handle_digit_request",
			" const std::string&, const5 std::string& ");
	// Add button value to the current input
	input = input + value;
	return __send_response(button, "PRESS");
}

int TLTestIntermediate::__handle_enter_request(const std::string& button)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::__handle_enter_request",
			" const std::string& ");
	// Store current input on stack
	// std::string* s_p = new std::string(input);
	// stk.push(*s_p);
	stk.push(input);
	input = "";
	return __send_response(button, "PRESS");
}

int TLTestIntermediate::__handle_operator_request(const std::string& op, const std::string& button)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::__handle_operator_request",
			" const std::string&, const5 std::string& ");
	std::string second(stk.top());
	stk.pop();
	std::string first(stk.top());
	stk.pop();

	// Create an expression request for next highest level in hierarchy
	expr.set_operand1(first);
	expr.set_operand2(second);
	expr.set_op(op);
	expr.set_term(std::string("="));
	expr.set_result(std::string(""));
	result = "";
	
	wrapper.set_uid(my_inst->translator_uid);
	wrapper.set_metaname("EXPR");
	std::string s;
	expr.SerializeToString(&s);
	wrapper.set_serialized(s);
	response_received = false;
	int ret = __send_request(wrapper);
	if(ret != 0) {
		my_inst->error_code = translator_unknown_metaname;
                my_inst->status_code = translator_failed;
                __logger(ERROR, __FILE__, __LINE__, get_error_string());
		int ret2 = __send_error_response();
                return ret;

	}
	else {
		if(response_received == true) {
			return __send_response(button, "PRESS");
		}
		else {
			return -1;
		}
	}
}

int TLTestIntermediate::__handle_dot_request(const std::string& button)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::__handle_dot_request",
			" const std::string& ");
	// Add dot to the current input
	input = input + ".";
	return __send_response(button, "PRESS");
}

int TLTestIntermediate::__handle_expr_response(const std::string& expr)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::__handle_expr_response",
			" const std::string& ");
	// Deserialize the response
	Imperative_EXPRESSION::EXPR e;
	e.ParseFromString(expr);
	// my_inst->child_uid = e.uid();
	if(e.uid() == my_inst->translator_uid)
	{
		result = e.result();
		// Push the result back on the stack for next operation
		// std::string* s_p = new std::string(e.result());
		// stk.push(*s_p);
		stk.push(e.result());
		my_inst->error_code = translator_success;
		my_inst->status_code = translator_ok;
		response_received = true;
		return 0;
	}
	else
	{
		my_inst->error_code = translator_response_failed;
		my_inst->status_code = translator_failed;
		response_received = true;
		return -1;
	}
}

int TLTestIntermediate::__handle_read_request(const ::DISPLAY::READ& disp)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::__handle_read_request",
			" ::DISPLAY::READ& ");
	wrapper.set_uid(my_inst->translator_uid);
	wrapper.set_metaname("READ");
	std::string s;
	::DISPLAY::READ d;
	d.set_uid(my_inst->translator_uid);
	d.set_value("0");
	d.SerializeToString(&s);
	wrapper.set_serialized(s);
	response_received = false;
	int ret = __send_request(wrapper);
	if(ret != 0) {
		my_inst->error_code = translator_unknown_metaname;
                my_inst->status_code = translator_failed;
                __logger(ERROR, __FILE__, __LINE__, get_error_string());
		int ret2 = __send_error_response();
                return ret;

	}
	else {
		if(response_received == true) {
			d.set_uid(my_inst->child_uid);
			d.SerializeToString(&s);
			return __send_response(s, "READ");
		}
		else {
			return -1;
		}
	}
}

int TLTestIntermediate::__handle_read_response(const std::string& disp)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::__handle_read_response",
			" const std::string& ");
	// Deserialize the response
	::DISPLAY::READ d;
	if(d.ParseFromString(disp))
	{
		if(d.uid() == my_inst->translator_uid)
		{
			value = d.value();
			my_inst->error_code = translator_success;
			my_inst->status_code = translator_ok;
			response_received = true;
			return 0;
		}
		else
		{
			my_inst->error_code = translator_response_failed;
			my_inst->status_code = translator_failed;
			response_received = true;
			return -1;
		}
	}
	else
	{
		my_inst->error_code = translator_response_failed;
		my_inst->status_code = translator_failed;
		response_received = true;
		return -1;
	}
}

int TLTestIntermediate::__handle_show_request(const ::DISPLAY::SHOW& disp)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::__handle_show_request",
			" ::DISPLAY::SHOW& ");
	wrapper.set_uid(my_inst->translator_uid);
	wrapper.set_metaname("SHOW");
	std::string s;
	::DISPLAY::SHOW d;
	d.set_uid(my_inst->translator_uid);
	d.set_value("0");
	d.SerializeToString(&s);
	wrapper.set_serialized(s);
	response_received = false;
	int ret = __send_request(wrapper);
	if(ret != 0) {
		my_inst->error_code = translator_unknown_metaname;
                my_inst->status_code = translator_failed;
                __logger(ERROR, __FILE__, __LINE__, get_error_string());
		int ret2 = __send_error_response();
                return ret;

	}
	else {
		if(response_received == true) {
			d.set_uid(my_inst->child_uid);
			d.set_value(value);
			d.SerializeToString(&s);
			return __send_response(s, "SHOW");
		}
		else {
			return -1;
		}
	}
}

int TLTestIntermediate::__handle_show_response(const std::string& disp)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::__handle_show_response",
			" const std::string& ");
	// Deserialize the response
	::DISPLAY::SHOW d;
	if(d.ParseFromString(disp))
	{
		if(d.uid() == my_inst->translator_uid)
		{
			value = d.value();
			my_inst->error_code = translator_success;
			my_inst->status_code = translator_ok;
			response_received = true;
			return 0;
		}
		else
		{
			my_inst->error_code = translator_response_failed;
			my_inst->status_code = translator_failed;
			response_received = true;
			return -1;
		}
	}
	else
	{
		my_inst->error_code = translator_response_failed;
		my_inst->status_code = translator_failed;
		response_received = true;
		return -1;
	}
}

int TLTestIntermediate::__send_error_response()
{
	SWDEBUG1( struct transform_instance, my_inst, "TLTestIntermediate::__send_error_response" );
	IEEE2654::IEEE2654Error err;
	err.set_uid(my_inst->child_uid);
	err.set_code(get_error_code());
	err.set_message(get_error_string());
	std::string s;
	err.SerializeToString(&s);
	__send_response(s, "IEEE2654Error");
	return -1;
}


int TLTestIntermediate::__send_request(::IEEE2654::IEEE2654Message wrapper)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::__send_request",
			" ::IEEE2654::IEEE2654Message& ");
	std::string s;
	wrapper.SerializeToString(&s);
	return tt_api->send_request(my_inst, my_inst->translator_uid, s.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(s.c_str())));
}

int TLTestIntermediate::__send_response(const std::string& button, const char* meta)
{
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::__send_response",
			" const std::string&, const5 std::string& ");
	::IEEE2654::IEEE2654Message wrapper;
	wrapper.set_uid(my_inst->child_uid);
	wrapper.set_metaname(meta);
	wrapper.set_serialized(button);
	std::string s;
	wrapper.SerializeToString(&s);
	return tt_api->send_response(my_inst, my_inst->child_uid, s.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(s.c_str())));
}

int TLTestIntermediate::__logger(LOG_TYPE lt, const char* filename, int line, const char* message) {
	SWDEBUG2( struct transform_instance, my_inst, "TLTestIntermediate::__logger",
			" LOG_TYPE, const char*, int, const char* ");
	std::string err_msg;
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
        return tt_api->logger(my_inst, lt, err_msg.c_str());
}

