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
static const char __date__[] = "2024/05/05";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "DLTestController.hpp"
#include "rapidjson/document.h" // rapidjason's DOM-style API
#include "IEEE2654.pb.h"
#include <iostream>
#include <sstream>

DLTestController::DLTestController()
{
	my_inst = (debug_instance*)0;
	td_api = (translator_debug_api*)0;
	sticky = true;
	observable = true;
}

DLTestController::~DLTestController()
{
}

int DLTestController::open( struct debug_instance* inst, struct translator_debug_api* td_api )
{
	my_inst = inst;
	this->td_api = td_api;
	my_inst->translator_api = td_api;
	my_inst->error_code = translator_success;
	my_inst->status_code = translator_ok;
	my_inst->child_uid = 0;
	my_inst->children_uids = NULL;
	my_inst->num_children = 0;
	my_inst->visible = 0;
	translator_error_strings = td_api->get_translator_error_strings();
	translator_status_strings = td_api->get_translator_status_strings();
	std::string s("DLTestController::open(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	std::cerr << s  << std::endl;
	return 0;
	// Translator has not yet been registered with Repository so can't log
	// return td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
}

int DLTestController::close( )
{
	std::string s("DLTestController::close(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	return 0;
}

int DLTestController::config( char* json_message )
{
	std::string s("DLTestController::config(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ", " + json_message;
	s = s + ") called.\n";
	std::cerr << s  << std::endl;
	return 0;
	// Translator has not yet been registered with Repository so can't log
	// return td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
}

int DLTestController::select( uint32_t index )
{
	std::string s("DLTestController::select(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int DLTestController::deselect( uint32_t index )
{
	std::string s("DLTestController::deselect(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

bool DLTestController::is_selected( uint32_t uid )
{
	std::string s("DLTestController::is_selected(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return false;
}

enum translator_error_code DLTestController::get_error_code( translator_error_code code )
{
	std::string s("DLTestController::get_error_code(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ")(code: ";
	s += code;
        s += ")	called.\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	return my_inst->error_code;
}

const char* DLTestController::get_error_string( translator_error_code code )
{
	std::string s("DLTestController::get_error_string(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ")(code: ";
	s += code;
        s += ")	called.\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	return translator_error_strings[my_inst->error_code];
}

enum translator_status DLTestController::get_status_code( translator_status code )
{
	std::string s("DLTestController::get_status_code(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ")(code: ";
	s += code;
        s += ")	called.\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	return my_inst->status_code;
}

const char* DLTestController::get_status_string( translator_status code )
{
	std::string s("DLTestController::get_status_string(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ")(code: ";
	s += code;
        s += ")	called.\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	return translator_status_strings[my_inst->status_code];
}

int DLTestController::handle_request( size_t len, uint8_t* message )
{
	std::string si = "DLTestController";
	si += "(";
	std::ostringstream ssi;
	ssi << td_api->translator;
	si += ssi.str();
	si += ")";
	si += "::handle_request";
	si += "(";
	si += "): ";
	si += "message = ";
	si += (const char*)message;
	si += "\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, si.c_str());
	// Deserialize the channel wrapper message
	std::string sm(reinterpret_cast<const char*>(message), len);
	::IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(sm);
	my_inst->child_uid = rvf.uid();
	std::string s("DLTestController::handle_request(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called with metaname: ";
	s = s + rvf.metaname();
	s = s + ".\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	my_inst->error_code = translator_unknown_metaname;
	my_inst->status_code = translator_failed;
	return 0;
}

int DLTestController::handle_response( size_t len, uint8_t* message )
{
	std::string si = "DLTestController";
	si += "(";
	std::ostringstream ssi;
	ssi << td_api->translator;
	si += ssi.str();
	si += ")";
	si += "::handle_response";
	si += "(";
	si += "): ";
	si += "message = ";
	si += (const char*)message;
	si += "\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, si.c_str());
	std::string s("DLTestController::handle_response(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called but not supported!\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int DLTestController::handle_update_request( size_t len, uint8_t* message )
{
	std::string si = "DLTestController";
	si += "(";
	std::ostringstream ssi;
	ssi << td_api->translator;
	si += ssi.str();
	si += ")";
	si += "::handle_update_request";
	si += "(";
	si += "): ";
	si += "message = ";
	si += (const char*)message;
	si += "\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, si.c_str());
	// Deserialize the channel wrapper message
	std::string sm(reinterpret_cast<const char*>(message), len);
	::IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(sm);
	my_inst->child_uid = rvf.uid();
	std::string s("DLTestController::handle_update_request(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called with metaname: ";
	s = s + rvf.metaname();
	s = s + ".\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	my_inst->error_code = translator_unknown_metaname;
	my_inst->status_code = translator_failed;
	return 0;
}

int DLTestController::handle_update_response( size_t len, uint8_t* message )
{
	std::string si = "DLTestController";
	si += "(";
	std::ostringstream ssi;
	ssi << td_api->translator;
	si += ssi.str();
	si += ")";
	si += "::handle_update_response";
	si += "(";
	si += "): ";
	si += "message = ";
	si += (const char*)message;
	si += "\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, si.c_str());
	// Deserialize the channel wrapper message
	std::string sm(reinterpret_cast<const char*>(message), len);
	::IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(sm);
	my_inst->child_uid = rvf.uid();
	std::string s("DLTestController::handle_update_response(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called with metaname: ";
	s = s + rvf.metaname();
	s = s + ".\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	my_inst->error_code = translator_unknown_metaname;
	my_inst->status_code = translator_failed;
	return 0;
}

int DLTestController::handle_inject_request( size_t len, uint8_t* message )
{
	std::string si = "DLTestController";
	si += "(";
	std::ostringstream ssi;
	ssi << td_api->translator;
	si += ssi.str();
	si += ")";
	si += "::handle_inject_request";
	si += "(";
	si += "): ";
	si += "message = ";
	si += (const char*)message;
	si += "\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, si.c_str());
	// Deserialize the channel wrapper message
	std::string sm(reinterpret_cast<const char*>(message), len);
	::IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(sm);
	my_inst->child_uid = rvf.uid();
	std::string s("DLTestController::handle_inject_request(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called with metaname: ";
	s = s + rvf.metaname();
	s = s + ".\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	my_inst->error_code = translator_unknown_metaname;
	my_inst->status_code = translator_failed;
	return 0;
}

int DLTestController::handle_inject_response( size_t len, uint8_t* message )
{
	std::string si = "DLTestController";
	si += "(";
	std::ostringstream ssi;
	ssi << td_api->translator;
	si += ssi.str();
	si += ")";
	si += "::handle_inject_response";
	si += "(";
	si += "): ";
	si += "message = ";
	si += (const char*)message;
	si += "\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, si.c_str());
	// Deserialize the channel wrapper message
	std::string sm(reinterpret_cast<const char*>(message), len);
	::IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(sm);
	my_inst->child_uid = rvf.uid();
	std::string s("DLTestController::handle_inject_response(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called with metaname: ";
	s = s + rvf.metaname();
	s = s + ".\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	my_inst->error_code = translator_unknown_metaname;
	my_inst->status_code = translator_failed;
	return 0;
}

int DLTestController::handle_command_request( size_t len, uint8_t* message )
{
	std::string si = "DLTestController";
	si += "(";
	std::ostringstream ssi;
	ssi << td_api->translator;
	si += ssi.str();
	si += ")";
	si += "::handle_command_request";
	si += "(";
	si += "): ";
	si += "message = ";
	si += (const char*)message;
	si += "\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, si.c_str());
	// Deserialize the channel wrapper message
	std::string sm(reinterpret_cast<const char*>(message), len);
	::IEEE2654::IEEE2654Message rvf;
	rvf.ParseFromString(sm);
	my_inst->child_uid = rvf.uid();
	std::string s("DLTestController::handle_command_request(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called with metaname: ";
	s = s + rvf.metaname();
	s = s + ".\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	my_inst->error_code = translator_unknown_metaname;
	my_inst->status_code = translator_failed;
	return 0;
}

int DLTestController::apply( ) {
	// Nothing to do
	std::string s("DLTestController::apply(");
	s = s + std::to_string(my_inst->translator_uid);
	s = s + ") called.\n";
	td_api->logger(my_inst, LOG_TYPE::NOTICE, s.c_str());
	return 0;
}

#if 0
int DLTestController::__parse_config( char* json_message )
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

int DLTestController::__setVisible( const char* val )
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

int DLTestController::__setSticky( const char* val )
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

int DLTestController::__setObservable( const char* val )
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
#endif

