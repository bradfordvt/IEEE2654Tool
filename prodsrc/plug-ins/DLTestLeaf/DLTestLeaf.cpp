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
static const char __date__[] = "2024/04/07";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "DLTestLeaf.hpp"
#include "rapidjson/document.h" // rapidjason's DOM-style API
#include <sstream>
#include "IEEE2654.pb.h"
#include "BUTTON.pb.h"
#include "COMMAND.pb.h"

DLTestLeaf::DLTestLeaf()
{
	my_inst = (debug_instance*)0;
	td_api = (translator_debug_api*)0;
}

DLTestLeaf::~DLTestLeaf()
{
}

int DLTestLeaf::open( struct debug_instance* inst, struct translator_debug_api* td_api )
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
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::open";
	s += "(";
	s += ")";
	s += "\n";
	return td_api->logger(my_inst, log_severity::INFO, s.c_str());
}

int DLTestLeaf::close( )
{
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::close";
	s += "(";
	s += ")";
	s += "\n";
	return td_api->logger(my_inst, log_severity::INFO, s.c_str());
}

int DLTestLeaf::config( char* json_message )
{
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::config";
	s += "(";
	s += json_message;
	s += ")";
	s += "\n";
	return td_api->logger(my_inst, log_severity::INFO, s.c_str());
}

int DLTestLeaf::select( uint32_t index )
{
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::select";
	s += "(";
	std::ostringstream ss1;
	ss1 << index;
	s += ss1.str();
	s += ")";
	s += "\n";
	return td_api->logger(my_inst, log_severity::INFO, s.c_str());
}

int DLTestLeaf::deselect( uint32_t index )
{
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::deselect";
	s += "(";
	std::ostringstream ss1;
	ss1 << index;
	s += ss1.str();
	s += ")";
	s += "\n";
	return td_api->logger(my_inst, log_severity::INFO, s.c_str());
}

bool DLTestLeaf::is_selected( uint32_t uid )
{
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::is_selected";
	s += "(";
	std::ostringstream ss1;
	ss1 << uid;
	s += ss1.str();
	s += ")";
	s += "\n";
	int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
	return false;
}

enum translator_error_code DLTestLeaf::get_error_code( translator_error_code code )
{
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::get_error_code";
	s += "(";
	std::ostringstream ss1;
	ss1 << code;
	s += ss1.str();
	s += "): ";
	std::ostringstream ss2;
	ss2 << my_inst->error_code;
	s += ss2.str();
	s += "\n";
	int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
	return my_inst->error_code;
}

const char* DLTestLeaf::get_error_string( translator_error_code code )
{
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::get_error_string";
	s += "(";
	std::ostringstream ss1;
	ss1 << code;
	s += ss1.str();
	s += "): ";
	s += translator_error_strings[my_inst->error_code];
	s += "\n";
	int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
	return translator_error_strings[my_inst->error_code];
}

enum translator_status DLTestLeaf::get_status_code( translator_status code )
{
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::get_status_code";
	s += "(";
	std::ostringstream ss1;
	ss1 << code;
	s += ss1.str();
	s += "): ";
	std::ostringstream ss2;
	ss2 << my_inst->status_code;
	s += ss2.str();
	s += "\n";
	int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
	return my_inst->status_code;
}

const char* DLTestLeaf::get_status_string( translator_status code )
{
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::get_status_code";
	s += "(";
	std::ostringstream ss1;
	ss1 << code;
	s += ss1.str();
	s += "): ";
	s += translator_status_strings[my_inst->status_code];
	s += "\n";
	int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
	return translator_status_strings[my_inst->status_code];
}

int DLTestLeaf::handle_request( size_t len, uint8_t* message )
{
	// This is a leaf node, thus no children to send a request
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::handle_request";
	s += "(";
	s += "): ";
	s += "THIS SHOULD NOT BE CALLED!";
	s += "\n";
	int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code = translator_failed;
	return -1;
}

int DLTestLeaf::handle_response( size_t len, uint8_t* message )
{
	::IEEE2654::IEEE2654Message msg = ::IEEE2654::IEEE2654Message();
	msg.ParseFromString(std::string((const char*)message, len));
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::handle_response";
	s += "(";
	s += "): ";
	s += "msg.metaname: ";
	s += msg.metaname();
	s += " ";
	if(msg.metaname() == "PRESS")
	{
		::BUTTON::PRESS btn = ::BUTTON::PRESS();
		btn.ParseFromString(msg.serialized());
		if(btn.uid() != my_inst->translator_uid)
		{
			s += "btn.uid: ";
			std::ostringstream ss1;
			ss1 << btn.uid();
			s += ss1.str();
			s += " != my_inst->translator_uid: ";
			std::ostringstream ss2;
			ss2 << my_inst->translator_uid;
			s += ss2.str();
			s += "\n";
			int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
			my_inst->error_code = translator_message_error;
			my_inst->status_code= translator_failed;
			return -1;
		}
		s += "btn.function: ";
		s += btn.function();
		s += " btn.uid: ";
		std::ostringstream ss1;
		ss1 << btn.uid();
		s += ss1.str();
		s += "\n";
		int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
		return ret;
	}
	else if(msg.metaname() == "ERROR")
	{
		::IEEE2654::IEEE2654Error err = ::IEEE2654::IEEE2654Error();
		err.ParseFromString(msg.serialized());
		s += "err.uid: ";
		std::ostringstream ss1;
		ss1 << err.uid();
		s += ss1.str();
		s += " err.code: ";
		std::ostringstream ss2;
		ss2 << err.code();
		s += ss2.str();
		s += " err.message: ";
		s += err.message();
		s += "\n";
		int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
		my_inst->error_code = translator_response_failed;
		my_inst->status_code = translator_failed;
		return -1;
	}
	else
	{
		s += "UNKNOWN METANAME!\n";
		int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
		my_inst->error_code = translator_unknown_metaname;
		my_inst->status_code = translator_failed;
		return -1;
	}
}

int DLTestLeaf::handle_update_request( size_t len, uint8_t* message )
{
	// This is a leaf node that does not have a value that can be updated
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::handle_update_request";
	s += "(";
	s += "): ";
	s += "THIS SHOULD NOT BE CALLED!";
	s += "\n";
	int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code= translator_failed;
	return -1;
}

int DLTestLeaf::handle_update_response( size_t len, uint8_t* message )
{
	// This is a leaf node that does not have a value that can be updated
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::handle_update_response";
	s += "(";
	s += "): ";
	s += "THIS SHOULD NOT BE CALLED!";
	s += "\n";
	int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
	my_inst->error_code = translator_unsupported_feature;
	my_inst->status_code= translator_failed;
	return -1;
}

int DLTestLeaf::handle_inject_request( size_t len, uint8_t* message )
{
	IEEE2654::IEEE2654Message msg = ::IEEE2654::IEEE2654Message();
	msg.ParseFromString(std::string((const char*)message, len));
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::handle_inject_request";
	s += "(";
	s += "): ";
	s += "msg.metaname: ";
	s += msg.metaname();
	s += " ";
	if(msg.metaname() == "PRESS")
	{
		::COMMAND::PRESS cmd = ::COMMAND::PRESS();
		cmd.ParseFromString(msg.serialized());
		::BUTTON::PRESS btn = ::BUTTON::PRESS();
		btn.set_function(cmd.function());
		s += cmd.function();
		s += "\n";
		int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
		return ret;
	}
	else
	{
		s += "Unkown metaname: ";
		s += "\n";
		int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
		my_inst->error_code = translator_unknown_metaname;
		my_inst->status_code = translator_failed;
		return ret;
	}
}

// int DLTestLeaf::handle_inject_response( size_t len, uint8_t* message )
// {
// 	IEEE2654::IEEE2654Message msg = ::IEEE2654::IEEE2654Message();
// 	msg.ParseFromString(std::string((const char*)message, len));
// 	std::string s = "DLTestLeaf";
// 	s += "(";
// 	std::ostringstream ss;
// 	ss << td_api->translator;
// 	s += ss.str();
// 	s += ")";
// 	s += "::handle_inject_response";
// 	s += "(";
// 	s += "): ";
// 	s += "msg.metaname: ";
// 	s += msg.metaname();
// 	s += " ";
// 	if(msg.metaname() == "PRESS")
// 	{
// 		::COMMAND::PRESS cmd = ::COMMAND::PRESS();
// 		cmd.ParseFromString(msg.serialized());
// 		::BUTTON::PRESS btn = ::BUTTON::PRESS();
// 		btn.set_function(cmd.function());
// 		s += cmd.function();
// 		s += "\n";
// 		int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
// 		return ret;
// 	}
// 	else
// 	{
// 		s += "Unkown metaname: ";
// 		s += "\n";
// 		int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
// 		my_inst->error_code = translator_unknown_metaname;
// 		my_inst->status_code = translator_failed;
// 		return ret;
// 	}
// }

int DLTestLeaf::handle_command_request( size_t len, uint8_t* message )
{
	IEEE2654::IEEE2654Message msg = ::IEEE2654::IEEE2654Message();
	msg.ParseFromString(std::string((const char*)message, len));
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::handle_command_request";
	s += "(";
	s += "): ";
	s += "msg.metaname: ";
	s += msg.metaname();
	s += " ";
	if(msg.metaname() == "PRESS")
	{
		::COMMAND::PRESS cmd = ::COMMAND::PRESS();
		cmd.ParseFromString(msg.serialized());
		::BUTTON::PRESS btn = ::BUTTON::PRESS();
		btn.set_function(cmd.function());
		s += cmd.function();
		s += "\n";
		int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
		return ret;
	}
	else
	{
		s += "Unkown metaname: ";
		s += "\n";
		int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
		my_inst->error_code = translator_unknown_metaname;
		my_inst->status_code = translator_failed;
		return ret;
	}
}

int DLTestLeaf::apply( )
{
	std::string s = "DLTestLeaf";
	s += "(";
	std::ostringstream ss;
	ss << td_api->translator;
	s += ss.str();
	s += ")";
	s += "::apply";
	s += "(";
	s += "): ";
	s += "Apply function called for active library for this instance.";
	s += "\n";
	int ret = td_api->logger(my_inst, log_severity::INFO, s.c_str());
	return 0;
}

