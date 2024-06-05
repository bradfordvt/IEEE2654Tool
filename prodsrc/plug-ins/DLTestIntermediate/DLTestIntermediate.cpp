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
static const char __date__[] = "2024/05/03";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "DLTestIntermediate.hpp"
#include "rapidjson/document.h" // rapidjason's DOM-style API
#include "IEEE2654.pb.h"
#include "Imperative_EXPRESSION.pb.h"

DLTestIntermediate::DLTestIntermediate()
{
	my_inst = (debug_instance*)0;
	td_api = (translator_debug_api*)0;
	sticky = true;
	observable = true;
}

DLTestIntermediate::~DLTestIntermediate()
{
}

int DLTestIntermediate::open( struct debug_instance* inst, struct translator_debug_api* td_api )
{
	my_inst = inst;
	this->td_api = td_api;
	my_inst->translator_api = td_api;
	my_inst->error_code = translator_success;
	my_inst->status_code = translator_ok;
	my_inst->visible = true;
	my_inst->child_uid = 0;
	my_inst->children_uids = NULL;
	my_inst->num_children = 0;
	std::string s("DLTestIntermediate::open(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return 0;
}

int DLTestIntermediate::close( )
{
	std::string s("DLTestIntermediate::close(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return 0;
}

int DLTestIntermediate::config( char* json_message )
{
	std::string s("DLTestIntermediate::config(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ", " + json_message;
	s = s + ") called.\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return __parse_config(json_message);
}

int DLTestIntermediate::select( uint32_t index )
{
	std::string s("DLTestIntermediate::select(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, INFO, s.c_str());
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int DLTestIntermediate::deselect( uint32_t index )
{
	std::string s("DLTestIntermediate::deselect(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, INFO, s.c_str());
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

bool DLTestIntermediate::is_selected( uint32_t uid )
{
	std::string s("DLTestIntermediate::is_selected(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, INFO, s.c_str());
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

enum translator_error_code DLTestIntermediate::get_error_code( translator_error_code code )
{
	std::string s("DLTestIntermediate::get_error_code(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return my_inst->error_code;
}

const char* DLTestIntermediate::get_error_string( translator_error_code code )
{
	std::string s("DLTestIntermediate::get_error_string(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return translator_error_strings[my_inst->error_code];
}

enum translator_status DLTestIntermediate::get_status_code( translator_status code )
{
	std::string s("DLTestIntermediate::get_status_code(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return my_inst->status_code;
}

const char* DLTestIntermediate::get_status_string( translator_status code )
{
	std::string s("DLTestIntermediate::get_status_string(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return translator_status_strings[my_inst->status_code];
}

int DLTestIntermediate::handle_request( size_t len, uint8_t* message )
{
	// Deserialize the channel wrapper message
	std::string s(reinterpret_cast<const char*>(message), len);
	::IEEE2654::IEEE2654Message rvf;
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
		std::string s("DLTestIntermediate::handle_request(");
		s = s + std::to_string(my_inst->translator_uid);
		s = s + ") calledi with an unknown metaname.\n";
		td_api->logger(my_inst, INFO, s.c_str());
		my_inst->error_code = translator_unknown_metaname;
		my_inst->status_code = translator_failed;
		return -1;
	}
}

int DLTestIntermediate::handle_response( size_t len, uint8_t* message )
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
		std::string s("DLTestIntermediate::handle_response(");
		s = s + std::to_string(my_inst->translator_uid);
		s = s + ") calledi with an unknown metaname.\n";
		td_api->logger(my_inst, INFO, s.c_str());
		my_inst->error_code = translator_unknown_metaname;
		my_inst->status_code = translator_failed;
		return -1;
	}
}

int DLTestIntermediate::handle_update_request( size_t len, uint8_t* message )
{
	// Deserialize the channel wrapper message
	std::string sm(reinterpret_cast<const char*>(message), len);
	::IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(sm);
	my_inst->child_uid = rvf.uid();
	std::string s("DLTestIntermediate::handle_update_request(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") calledi with metaname: ";
	s = s + rvf.metaname();
	s = s + "\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return 0;
}

int DLTestIntermediate::handle_update_response( size_t len, uint8_t* message )
{
	// Deserialize the channel wrapper message
	std::string sm(reinterpret_cast<const char*>(message), len);
	::IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(sm);
	my_inst->child_uid = rvf.uid();
	std::string s("DLTestIntermediate::handle_update_response(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") calledi with metaname: ";
	s = s + rvf.metaname();
	s = s + "\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return 0;
}

int DLTestIntermediate::handle_inject_request( size_t len, uint8_t* message )
{
	// Deserialize the channel wrapper message
	std::string sm(reinterpret_cast<const char*>(message), len);
	::IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(sm);
	my_inst->child_uid = rvf.uid();
	std::string s("DLTestIntermediate::handle_inject_request(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") calledi with metaname: ";
	s = s + rvf.metaname();
	s = s + "\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return 0;
}

int DLTestIntermediate::handle_inject_response( size_t len, uint8_t* message )
{
	// Deserialize the channel wrapper message
	std::string sm(reinterpret_cast<const char*>(message), len);
	::IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(sm);
	my_inst->child_uid = rvf.uid();
	std::string s("DLTestIntermediate::handle_inject_response(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") calledi with metaname: ";
	s = s + rvf.metaname();
	s = s + "\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return 0;
}

int DLTestIntermediate::handle_command_request( size_t len, uint8_t* message )
{
	// Deserialize the channel wrapper message
	std::string sm(reinterpret_cast<const char*>(message), len);
	::IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(sm);
	my_inst->child_uid = rvf.uid();
	std::string s("DLTestIntermediate::handle_command_request(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") calledi with metaname: ";
	s = s + rvf.metaname();
	s = s + "\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return 0;
}

int DLTestIntermediate::apply( ) {
	// Nothing to do
	std::string s("DLTestIntermediate::apply(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return 0;
}

int DLTestIntermediate::__parse_config( char* json_message )
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

int DLTestIntermediate::__setVisible( const char* val )
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

int DLTestIntermediate::__setSticky( const char* val )
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

int DLTestIntermediate::__setObservable( const char* val )
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

int DLTestIntermediate::__handle_digit_request(const std::string& value, const std::string& button)
{
	std::string s("DLTestIntermediate::handle_request(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called with digit " + value + ".\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return 0;
}

int DLTestIntermediate::__handle_enter_request(const std::string& button)
{
	std::string s("DLTestIntermediate::handle_request(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called with enter.\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return 0;
}

int DLTestIntermediate::__handle_operator_request(const std::string& op, const std::string& button)
{
	std::string s("DLTestIntermediate::handle_request(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called with operator " + op + ".\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return 0;
}

int DLTestIntermediate::__handle_dot_request(const std::string& button)
{
	std::string s("DLTestIntermediate::handle_request(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called with dot.\n";
	td_api->logger(my_inst, INFO, s.c_str());
	return 0;
}

int DLTestIntermediate::__handle_expr_response(const std::string& expr)
{
	std::string s("DLTestIntermediate::handle_response(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called with expression result = ";
	// Deserialize the response
	Imperative_EXPRESSION::EXPR e;
	e.ParseFromString(expr);
	my_inst->child_uid = e.uid();
	if(e.uid() == my_inst->translator_uid)
	{
		result = e.result();
		s = s + ") called with expression result = ";
		s = s + result + ".\n";
		td_api->logger(my_inst, INFO, s.c_str());
		return 0;
	}
	else
	{
		s = s + ") called with wrong uid = ";
		s = s + std::to_string(e.uid());
		s = s + ".\n";
		td_api->logger(my_inst, INFO, s.c_str());
		my_inst->error_code = translator_response_failed;
		my_inst->status_code = translator_failed;
		return -1;
	}
}
