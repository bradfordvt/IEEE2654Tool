/*
 *    ClientInterfaceRep.cpp
 *
 *    Class to implement the intermediate parser representation for the
 *    ClientInterface architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    ClientInterface architectural element.
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

#include "parser/ClientInterfaceRep.hpp"
#include "debug/Verify.hpp"

ClientInterfaceRep::ClientInterfaceRep() : name(), protocol("IEEE2654.proto"), channel(0), key(-1), translator(-1) {
	SWDEBUGP1( 5, Verify::PARSER, "ClientInterfaceRep::ClientInterfaceRep");
	SWDEBUG1( 5, Verify::TRACE, "ClientInterfaceRep::ClientInterfaceRep");
}

ClientInterfaceRep::ClientInterfaceRep(const std::string& _name) {
	SWDEBUGP2( 5, Verify::PARSER, "ClientInterfaceRep::ClientInterfaceRep",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ClientInterfaceRep::ClientInterfaceRep",
                        " const std::string& " );
	name = _name;
	protocol = "IEEE2654.proto";
	channel = 0;
	key = -1;
	translator = -1;
}

ClientInterfaceRep::ClientInterfaceRep(const ClientInterfaceRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "ClientInterfaceRep::ClientInterfaceRep",
                        " const ClientInterfaceRep& " );
	SWDEBUG2( 5, Verify::TRACE, "ClientInterfaceRep::ClientInterfaceRep",
                        " const ClientInterfaceRep& " );
	name = l.name;
	protocol = l.protocol;
	channel = l.channel;
	key = l.key;
	translator = l.translator;
}

ClientInterfaceRep::~ClientInterfaceRep() {
	SWDEBUGP1( 5, Verify::PARSER, "ClientInterfaceRep::~ClientInterfaceRep");
	SWDEBUG1( 5, Verify::TRACE, "ClientInterfaceRep::~ClientInterfaceRep");
}

ClientInterfaceRep& ClientInterfaceRep::operator=(const ClientInterfaceRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "ClientInterfaceRep::operator=",
                        " const ClientInterfaceRep& " );
	SWDEBUG2( 5, Verify::TRACE, "ClientInterfaceRep::operator=",
                        " const ClientInterfaceRep& " );
	name = l.name;
	protocol = l.protocol;
	channel = l.channel;
	return *this;
}

bool operator==(const ClientInterfaceRep& lhs, const ClientInterfaceRep& rhs) {
	SWDEBUGP2( 5, Verify::PARSER, "ClientInterfaceRep::operator==",
                        " const ClientInterfaceRep&, const ClientInterfaceRep& " );
	SWDEBUG2( 5, Verify::TRACE, "ClientInterfaceRep::operator==",
                        " const ClientInterfaceRep&, const ClientInterfaceRep& " );
	return lhs.name == rhs.name && lhs.protocol == rhs.protocol &&
		lhs.translator == rhs.translator && lhs.key == rhs.key &&
		lhs.channel == rhs.channel;
}

bool ClientInterfaceRep::set_name(const std::string& _name) {
	SWDEBUGP2( 5, Verify::PARSER, "ClientInterfaceRep::set_name",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ClientInterfaceRep::set_name",
                        " const std::string& " );
	name = _name;
	return true;
}

const std::string& ClientInterfaceRep::get_name() {
	SWDEBUGP1( 5, Verify::PARSER, "ClientInterfaceRep::get_name");
	SWDEBUG1( 5, Verify::TRACE, "ClientInterfaceRep::get_name");
	return name;
}

bool ClientInterfaceRep::set_channel(int ch) {
	SWDEBUGP2( 5, Verify::PARSER, "ClientInterfaceRep::set_channel",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "ClientInterfaceRep::set_channel",
                        " int " );
	channel = ch;
	return true;
}

int ClientInterfaceRep::get_channel() {
	SWDEBUGP1( 5, Verify::PARSER, "ClientInterfaceRep::get_channel");
	SWDEBUG1( 5, Verify::TRACE, "ClientInterfaceRep::get_channel");
	return channel;
}

bool ClientInterfaceRep::set_translator(int t) {
	SWDEBUGP2( 5, Verify::PARSER, "ClientInterfaceRep::set_translator",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "ClientInterfaceRep::set_translator",
                        " int " );
	translator = t;
	return true;
}

int ClientInterfaceRep::get_translator() {
	SWDEBUGP1( 5, Verify::PARSER, "ClientInterfaceRep::get_translator");
	SWDEBUG1( 5, Verify::TRACE, "ClientInterfaceRep::get_translator");
	return translator;
}

bool ClientInterfaceRep::set_key(int k) {
	SWDEBUGP2( 5, Verify::PARSER, "ClientInterfaceRep::set_key",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "ClientInterfaceRep::set_key",
                        " int " );
	key = k;
	return true;
}

int ClientInterfaceRep::get_key() {
	SWDEBUGP1( 5, Verify::PARSER, "ClientInterfaceRep::get_key");
	SWDEBUG1( 5, Verify::TRACE, "ClientInterfaceRep::get_key");
	return key;
}

bool ClientInterfaceRep::set_protocol(const std::string& _protocol) {
	SWDEBUGP2( 5, Verify::PARSER, "ClientInterfaceRep::set_protocol",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ClientInterfaceRep::set_protocol",
                        " const std::string& " );
	protocol = _protocol;
	return true;
}

const std::string& ClientInterfaceRep::get_protocol() {
	SWDEBUGP1( 5, Verify::PARSER, "ClientInterfaceRep::get_protocol");
	SWDEBUG1( 5, Verify::TRACE, "ClientInterfaceRep::get_protocol");
	return protocol;
}

