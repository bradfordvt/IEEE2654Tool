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

TLTestIntermediate::TLTestIntermediate()
{
	my_inst = (transform_instance*)0;
	tt_api = (translator_transform_api*)0;
	sticky = true;
	observable = true;
	equation = std::string("");
}

TLTestIntermediate::~TLTestIntermediate()
{
}

int TLTestIntermediate::open( struct transform_instance* inst, struct translator_transform_api* tt_api )
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

int TLTestIntermediate::close( )
{
	return 0;
}

int TLTestIntermediate::config( char* json_message )
{
	return __parse_config(json_message);
}

int TLTestIntermediate::select( uint32_t index )
{
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int TLTestIntermediate::deselect( uint32_t index )
{
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

bool TLTestIntermediate::is_selected( uint32_t uid )
{
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

enum translator_error_code TLTestIntermediate::get_error_code( )
{
	return my_inst->error_code;
}

const char* TLTestIntermediate::get_error_string( )
{
	return translator_error_strings[my_inst->error_code];
}

enum translator_status TLTestIntermediate::get_status_code( )
{
	return my_inst->status_code;
}

const char* TLTestIntermediate::get_status_string( )
{
	return translator_status_strings[my_inst->status_code];
}

int TLTestIntermediate::handle_request( size_t len, uint8_t* message )
{
	// Deserialize the channel wrapper message
	std::string s(reinterpret_cast<const char*>(message), len);
	IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(s);
	my_inst->child_uid = rvf.uid();
	if(rvf.metaname() == "ZERO")
	{
		return __handle_digit_request(std::string("0"), rvf.serialized());
	}
	else if(rvf.metaname() == "ONE")
	{
		return __handle_digit_request(std::string("1"), rvf.serialized());
	}
	else if(rvf.metaname() == "TWO")
	{
		return __handle_digit_request(std::string("2"), rvf.serialized());
	}
	else if(rvf.metaname() == "THREE")
	{
		return __handle_digit_request(std::string("3"), rvf.serialized());
	}
	else if(rvf.metaname() == "FOUR")
	{
		return __handle_digit_request(std::string("4"), rvf.serialized());
	}
	else if(rvf.metaname() == "FIVE")
	{
		return __handle_digit_request(std::string("5"), rvf.serialized());
	}
	else if(rvf.metaname() == "SIX")
	{
		return __handle_digit_request(std::string("6"), rvf.serialized());
	}
	else if(rvf.metaname() == "SEVEN")
	{
		return __handle_digit_request(std::string("7"), rvf.serialized());
	}
	else if(rvf.metaname() == "EIGHT")
	{
		return __handle_digit_request(std::string("8"), rvf.serialized());
	}
	else if(rvf.metaname() == "NINE")
	{
		return __handle_digit_request(std::string("9"), rvf.serialized());
	}
	else if(rvf.metaname() == "ENTER")
	{
		return __handle_enter_request(rvf.serialized());
	}
	else if(rvf.metaname() == "PLUS")
	{
		return __handle_operator_request(std::string("+"), rvf.serialized());
	}
	else if(rvf.metaname() == "MINUS")
	{
		return __handle_operator_request(std::string("-"), rvf.serialized());
	}
	else if(rvf.metaname() == "MULTIPLY")
	{
		return __handle_operator_request(std::string("*"), rvf.serialized());
	}
	else if(rvf.metaname() == "DIVIDE")
	{
		return __handle_operator_request(std::string("/"), rvf.serialized());
	}
	else if(rvf.metaname() == "DOT")
	{
		return __handle_dot_request(rvf.serialized());
	}
	else
	{
		my_inst->error_code = translator_unknown_metaname;
		my_inst->status_code = translator_failed;
		return __send_error_response(rvf);
	}
}

int TLTestIntermediate::handle_response( size_t len, uint8_t* message )
{
	// Deserialize the channel wrapper message
	std::string s(reinterpret_cast<const char*>(message), len);
	::IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(s);
	my_inst->child_uid = rvf.uid();
	if(rvf.metaname() == "EXPR")
	{
		return __handle_expr_response(rvf.serialized());
	}
	else
	{
		my_inst->error_code = translator_unknown_metaname;
		my_inst->status_code = translator_failed;
		return __send_error_response(rvf);
	}
}

int TLTestIntermediate::apply( ) {
	// Nothing to do
	return 0;
}

int TLTestIntermediate::__parse_config( char* json_message )
{
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
	if(rval3) return rval3;
	if(rval2) return rval2;
	if(rval1) return rval1;
	return 0;
}

int TLTestIntermediate::__setVisible( const char* val )
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

int TLTestIntermediate::__setSticky( const char* val )
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

int TLTestIntermediate::__setObservable( const char* val )
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

int TLTestIntermediate::__handle_digit_request(const std::string& value, const std::string& button)
{
	// Add button value to the current input
	input = input + value;
	return __send_response(button);
}

int TLTestIntermediate::__handle_enter_request(const std::string& button)
{
	// Store current input on stack
	// std::string* s_p = new std::string(input);
	// stk.push(*s_p);
	stk.push(input);
	input = "";
	return __send_response(button);
}

int TLTestIntermediate::__handle_operator_request(const std::string& op, const std::string& button)
{
	// Process the data on the stack
	// std::string sec = stk.top();
	// stk.pop();
	// std::string second(sec);
	// delete &sec;

	// std::string frst = stk.top();
	// stk.pop();
	// std::string first(frst);
	// delete &frst;

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
	
	wrapper.set_uid(my_inst->child_uid);
	wrapper.set_metaname(std::string(op));
	std::string s;
	expr.SerializeToString(&s);
	wrapper.set_serialized(s);
	return __send_request(wrapper);
}

int TLTestIntermediate::__handle_dot_request(const std::string& button)
{
	// Add dot to the current input
	input = input + ".";
	return __send_response(button);
}

int TLTestIntermediate::__handle_expr_response(const std::string& expr)
{
	// Deserialize the response
	Imperative_EXPRESSION::EXPR e;
	e.ParseFromString(expr);
	my_inst->child_uid = e.uid();
	if(e.uid() == my_inst->translator_uid)
	{
		result = e.result();
		// Push the result back on the stack for next operation
		std::string* s_p = new std::string(e.result());
		stk.push(*s_p);
		return 0;
	}
	else
	{
		my_inst->error_code = translator_response_failed;
		my_inst->status_code = translator_failed;
		return -1;
	}
}

int TLTestIntermediate::__send_error_response(::IEEE2654::IEEE2654Message rvf)
{
	IEEE2654::IEEE2654Error err;
	err.set_uid(rvf.uid());
	err.set_code(get_error_code());
	err.set_message(get_error_string());
	std::string s;
	err.SerializeToString(&s);
	__send_response(s);
	return -1;
}


int TLTestIntermediate::__send_request(::IEEE2654::IEEE2654Message wrapper)
{
	std::string s;
	wrapper.SerializeToString(&s);
	return tt_api->send_request(my_inst, my_inst->translator_uid, s.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(s.c_str())));
}

int TLTestIntermediate::__send_response(const std::string& button)
{
	::IEEE2654::IEEE2654Message wrapper;
	wrapper.set_uid(my_inst->child_uid);
	wrapper.set_metaname("ERROR");
	wrapper.set_serialized(button);
	std::string s;
	wrapper.SerializeToString(&s);
	return tt_api->send_response(my_inst, my_inst->translator_uid, s.length(), const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(s.c_str())));
}
