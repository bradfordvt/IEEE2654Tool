/*
 *    TopModuleRep.cpp
 *
 *    Class to implement the intermediate parser representation for the
 *    TopModule architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    TopModule architectural element.
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
static const char __date__[] = "2024/06/09";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <iostream>
#include "parser/TopModuleRep.hpp"
#include "debug/Verify.hpp"

TopModuleRep::TopModuleRep() : module_name() {
	SWDEBUGP1( 5, Verify::PARSER, "TopModuleRep::TopModuleRep");
	SWDEBUG1( 5, Verify::TRACE, "TopModuleRep::TopModuleRep");
	num_translators = 0;
	num_channels = 0;
	num_host_interfaces = 0;
	num_client_interfaces = 0;
	num_command_interfaces = 0;
	num_inject_interfaces = 0;
	translator = 0;
}

TopModuleRep::TopModuleRep(const std::string& _module_name) {
	SWDEBUGP2( 5, Verify::PARSER, "TopModuleRep::TopModuleRep",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "TopModuleRep::TopModuleRep",
                        " const std::string& " );
	module_name = _module_name;
	num_translators = 0;
	num_channels = 0;
	num_host_interfaces = 0;
	num_client_interfaces = 0;
	num_command_interfaces = 0;
	num_inject_interfaces = 0;
	translator = 0;
}

TopModuleRep::TopModuleRep(const TopModuleRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "TopModuleRep::TopModuleRep",
                        " const TopModuleRep& " );
	SWDEBUG2( 5, Verify::TRACE, "TopModuleRep::TopModuleRep",
                        " const TopModuleRep& " );
	module_name = l.module_name;
	num_translators = l.num_translators;
	num_channels = l.num_channels;
	num_host_interfaces = l.num_host_interfaces;
	num_client_interfaces = l.num_client_interfaces;
	num_command_interfaces = l.num_command_interfaces;
	num_inject_interfaces = l.num_inject_interfaces;
	translator = l.translator;
}

TopModuleRep::~TopModuleRep() {
	SWDEBUGP1( 5, Verify::PARSER, "TopModuleRep::~TopModuleRep");
	SWDEBUG1( 5, Verify::TRACE, "TopModuleRep::~TopModuleRep");
}

TopModuleRep& TopModuleRep::operator=(const TopModuleRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "TopModuleRep::operator=",
                        " const TopModuleRep& " );
	SWDEBUG2( 5, Verify::TRACE, "TopModuleRep::operator=",
                        " const TopModuleRep& " );
	module_name = l.module_name;
	num_translators = l.num_translators;
	num_channels = l.num_channels;
	num_host_interfaces = l.num_host_interfaces;
	num_client_interfaces = l.num_client_interfaces;
	num_command_interfaces = l.num_command_interfaces;
	num_inject_interfaces = l.num_inject_interfaces;
	translator = l.translator;
	return *this;
}

bool TopModuleRep::set_module_name(const std::string& _module_name) {
	SWDEBUGP2( 5, Verify::PARSER, "TopModuleRep::set_module_name",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "TopModuleRep::set_module_name",
                        " const std::string& " );
	module_name = _module_name;
	return true;
}

const std::string& TopModuleRep::get_module_name() {
	SWDEBUGP1( 5, Verify::PARSER, "TopModuleRep::get_module_name");
	SWDEBUG1( 5, Verify::TRACE, "TopModuleRep::get_module_name");
	return module_name;
}

bool TopModuleRep::set_translator(int t) {
	SWDEBUGP2( 5, Verify::PARSER, "TopModuleRep::set_translator",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TopModuleRep::set_translator",
                        " int " );
	translator = t;
	return true;
}

int TopModuleRep::get_translator() {
	SWDEBUGP1( 5, Verify::PARSER, "TopModuleRep::get_translator");
	SWDEBUG1( 5, Verify::TRACE, "TopModuleRep::get_translator");
	return translator;
}

bool TopModuleRep::set_num_translators(int count) {
	SWDEBUGP2( 5, Verify::PARSER, "TopModuleRep::set_num_translators",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TopModuleRep::set_num_translators",
                        " int " );
	num_translators = count;
	return true;
}

int TopModuleRep::get_num_translators() {
	SWDEBUGP1( 5, Verify::PARSER, "TopModuleRep::get_num_translators");
	SWDEBUG1( 5, Verify::TRACE, "TopModuleRep::get_num_translators");
	return num_translators;
}

bool TopModuleRep::set_num_channels(int count) {
	SWDEBUGP2( 5, Verify::PARSER, "TopModuleRep::set_num_channels",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TopModuleRep::set_num_channels",
                        " int " );
	num_channels = count;
	return true;
}

int TopModuleRep::get_num_channels() {
	SWDEBUGP1( 5, Verify::PARSER, "TopModuleRep::get_num_channels");
	SWDEBUG1( 5, Verify::TRACE, "TopModuleRep::get_num_channels");
	return num_channels;
}

bool TopModuleRep::set_num_host_interfaces(int count) {
	SWDEBUGP2( 5, Verify::PARSER, "TopModuleRep::set_num_host_interfaces",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TopModuleRep::set_num_host_interfaces",
                        " int " );
	num_host_interfaces = count;
	return true;
}

int TopModuleRep::get_num_host_interfaces() {
	SWDEBUGP1( 5, Verify::PARSER, "TopModuleRep::get_num_host_interfaces");
	SWDEBUG1( 5, Verify::TRACE, "TopModuleRep::get_num_host_interfaces");
	return num_host_interfaces;
}

bool TopModuleRep::set_num_client_interfaces(int count) {
	SWDEBUGP2( 5, Verify::PARSER, "TopModuleRep::set_num_client_interfaces",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TopModuleRep::set_num_client_interfaces",
                        " int " );
	num_client_interfaces = count;
	return true;
}

int TopModuleRep::get_num_client_interfaces() {
	SWDEBUGP1( 5, Verify::PARSER, "TopModuleRep::get_num_client_interfaces");
	SWDEBUG1( 5, Verify::TRACE, "TopModuleRep::get_num_client_interfaces");
	return num_client_interfaces;
}

bool TopModuleRep::set_num_command_interfaces(int count) {
	SWDEBUGP2( 5, Verify::PARSER, "TopModuleRep::set_num_command_interfaces",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TopModuleRep::set_num_command_interfaces",
                        " int " );
	num_command_interfaces = count;
	return true;
}

int TopModuleRep::get_num_command_interfaces() {
	SWDEBUGP1( 5, Verify::PARSER, "TopModuleRep::get_num_command_interfaces");
	SWDEBUG1( 5, Verify::TRACE, "TopModuleRep::get_num_command_interfaces");
	return num_command_interfaces;
}

bool TopModuleRep::set_num_inject_interfaces(int count) {
	SWDEBUGP2( 5, Verify::PARSER, "TopModuleRep::set_num_inject_interfaces",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TopModuleRep::set_num_inject_interfaces",
                        " int " );
	num_inject_interfaces = count;
	return true;
}

int TopModuleRep::get_num_inject_interfaces() {
	SWDEBUGP1( 5, Verify::PARSER, "TopModuleRep::get_num_inject_interfaces");
	SWDEBUG1( 5, Verify::TRACE, "TopModuleRep::get_num_inject_interfaces");
	return num_inject_interfaces;
}

void TopModuleRep::dump(size_t indent) {
	SWDEBUGP2( 5, Verify::PARSER, "TopModuleRep::dump",
                        " size_t " );
	SWDEBUG2( 5, Verify::TRACE, "TopModuleRep::dump",
                        " size_t " );
	std::string ind;
        indent == 0 ? ind = std::string(indent, '\t') : ind = std::string("");
        std::string ind2(indent + 1, '\t');
        std::cerr << ind << "TopModuleRep contents:" << std::endl;
        std::cerr << ind2 << "module_name = " << module_name << std::endl;
        std::cerr << ind2 << "num_translators = " << num_translators << std::endl;
        std::cerr << ind2 << "num_channels = " << num_channels << std::endl;
        std::cerr << ind2 << "num_host_interfaces = " << num_host_interfaces << std::endl;
        std::cerr << ind2 << "num_client_interfaces = " << num_client_interfaces << std::endl;
        std::cerr << ind2 << "num_command_interfaces = " << num_command_interfaces << std::endl;
        std::cerr << ind2 << "num_inject_interfaces = " << num_inject_interfaces << std::endl;
        std::cerr << ind2 << "translator = " << translator << std::endl;
	int translator;
}

