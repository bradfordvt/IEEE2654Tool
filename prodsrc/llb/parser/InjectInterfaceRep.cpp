/*
 *    InjectInterfaceRep.cpp
 *
 *    Class to implement the intermediate parser representation for the
 *    InjectInterface architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    InjectInterface architectural element.
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

#include "parser/InjectInterfaceRep.hpp"
#include "debug/Verify.hpp"

InjectInterfaceRep::InjectInterfaceRep() : name(), protocol("IEEE2654.proto"), translator(0) {
	SWDEBUGP1( 5, Verify::PARSER, "InjectInterfaceRep::InjectInterfaceRep");
	SWDEBUG1( 5, Verify::TRACE, "InjectInterfaceRep::InjectInterfaceRep");
}

InjectInterfaceRep::InjectInterfaceRep(const std::string& _name) {
	SWDEBUGP2( 5, Verify::PARSER, "InjectInterfaceRep::InjectInterfaceRep",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "InjectInterfaceRep::InjectInterfaceRep",
                        " const std::string& " );
	name = _name;
	protocol = "IEEE2654.proto";
	translator = 0;
}

InjectInterfaceRep::InjectInterfaceRep(const InjectInterfaceRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "InjectInterfaceRep::InjectInterfaceRep",
                        " const InjectInterfaceRep& " );
	SWDEBUG2( 5, Verify::TRACE, "InjectInterfaceRep::InjectInterfaceRep",
                        " const InjectInterfaceRep& " );
	name = l.name;
	protocol = l.protocol;
	translator = l.translator;
}

InjectInterfaceRep::~InjectInterfaceRep() {
	SWDEBUGP1( 5, Verify::PARSER, "InjectInterfaceRep::~InjectInterfaceRep");
	SWDEBUG1( 5, Verify::TRACE, "InjectInterfaceRep::~InjectInterfaceRep");
}

InjectInterfaceRep& InjectInterfaceRep::operator=(const InjectInterfaceRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "InjectInterfaceRep::operator=",
                        " const InjectInterfaceRep& " );
	SWDEBUG2( 5, Verify::TRACE, "InjectInterfaceRep::operator=",
                        " const InjectInterfaceRep& " );
	name = l.name;
	protocol = l.protocol;
	translator = l.translator;
	return *this;
}

bool operator==(const InjectInterfaceRep& lhs, const InjectInterfaceRep& rhs) {
	SWDEBUGP2( 5, Verify::PARSER, "InjectInterfaceRep::operator==",
                        " const InjectInterfaceRep&, const InjectInterfaceRep& " );
	SWDEBUG2( 5, Verify::TRACE, "InjectInterfaceRep::operator==",
                        " const InjectInterfaceRep&, const InjectInterfaceRep& " );
	return lhs.name == rhs.name && lhs.protocol == rhs.protocol &&
		lhs.translator == rhs.translator;
}

bool InjectInterfaceRep::set_name(const std::string& _name) {
	SWDEBUGP2( 5, Verify::PARSER, "InjectInterfaceRep::set_name",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "InjectInterfaceRep::set_name",
                        " const std::string& " );
	this->name = _name;
	return true;
}

const std::string& InjectInterfaceRep::get_name() {
	SWDEBUGP1( 5, Verify::PARSER, "InjectInterfaceRep::get_name");
	SWDEBUG1( 5, Verify::TRACE, "InjectInterfaceRep::get_name");
	return name;
}

bool InjectInterfaceRep::set_translator(int t) {
	SWDEBUGP2( 5, Verify::PARSER, "InjectInterfaceRep::set_translator",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "InjectInterfaceRep::set_translator",
                        " int " );
	translator = t;
	return true;
}

int InjectInterfaceRep::get_translator() {
	SWDEBUGP1( 5, Verify::PARSER, "InjectInterfaceRep::get_translator");
	SWDEBUG1( 5, Verify::TRACE, "InjectInterfaceRep::get_translator");
	return translator;
}

bool InjectInterfaceRep::set_key(int k) {
	SWDEBUGP2( 5, Verify::PARSER, "InjectInterfaceRep::set_key",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "InjectInterfaceRep::set_key",
                        " int " );
	key = k;
	return true;
}

int InjectInterfaceRep::get_key() {
	SWDEBUGP1( 5, Verify::PARSER, "InjectInterfaceRep::get_key");
	SWDEBUG1( 5, Verify::TRACE, "InjectInterfaceRep::get_key");
	return key;
}

bool InjectInterfaceRep::set_protocol(const std::string& _protocol) {
	SWDEBUGP2( 5, Verify::PARSER, "InjectInterfaceRep::set_protocol",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "InjectInterfaceRep::set_protocol",
                        " const std::string& " );
	protocol = _protocol;
	return true;
}

const std::string& InjectInterfaceRep::get_protocol() {
	SWDEBUGP1( 5, Verify::PARSER, "InjectInterfaceRep::get_protocol");
	SWDEBUG1( 5, Verify::TRACE, "InjectInterfaceRep::get_protocol");
	return protocol;
}

