/*
 *    ChannelRep.cpp
 *
 *    Class to implement the intermediate parser representation for the
 *    Channel architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    Channel architectural element.
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

#include "parser/ChannelRep.hpp"
#include "debug/Verify.hpp"

ChannelRep::ChannelRep() : name(), protocol(), method(), key(-1), client_interface(-1), host_interface(-1) {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::ChannelRep");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::ChannelRep");
}

ChannelRep::ChannelRep(const std::string& _name) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::ChannelRep",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::ChannelRep",
                        " const std::string& " );
	name = _name;
	protocol = "IEEE2654.proto";
	method = "reference";
	key = -1;
	client_interface = -1;
	host_interface = -1;
}

ChannelRep::ChannelRep(const ChannelRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::ChannelRep",
                        " const ChannelRep& " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::ChannelRep",
                        " const ChannelRep& " );
	name = l.name;
	protocol = l.protocol;
	method = l.method;
	key = l.key;
	client_interface = l.client_interface;
	host_interface = l.host_interface;
}

ChannelRep::~ChannelRep() {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::~ChannelRep");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::~ChannelRep");
}

ChannelRep& ChannelRep::operator=(const ChannelRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::operator=",
                        " const ChannelRep& " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::operator=",
                        " const ChannelRep& " );
	name = l.name;
	protocol = l.protocol;
	method = l.method;
	key = l.key;
	client_interface = l.client_interface;
	host_interface = l.host_interface;
	return *this;
}

bool operator==(const ChannelRep& lhs, const ChannelRep& rhs) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::operator==",
                        " const ChannelRep&, const ChannelRep& " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::operator==",
                        " const ChannelRep&, const ChannelRep& " );
	return lhs.name == rhs.name && lhs.protocol == rhs.protocol &&
		lhs.method == rhs.method && lhs.key == rhs.key &&
		lhs.client_interface == rhs.client_interface &&
		lhs.host_interface == rhs.host_interface;
}

bool ChannelRep::set_name(const std::string& _name) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::set_name",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::set_name",
                        " const std::string& " );
	name = _name;
	return true;
}

const std::string& ChannelRep::get_name() {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::get_name");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::get_name");
	return name;
}

bool ChannelRep::set_key(int n) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::set_key",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::set_key",
                        " int " );
	key = n;
	return true;
}

int ChannelRep::get_key() {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::get_key");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::get_key");
	return key;
}

bool ChannelRep::set_client_interface(int n) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::set_client_interface",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::set_client_interface",
                        " int " );
	client_interface = n;
	return true;
}

int ChannelRep::get_client_interface() {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::get_client_interface");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::get_client_interface");
	return client_interface;
}

bool ChannelRep::set_host_interface(int n) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::set_host_interface",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::set_host_interface",
                        " int " );
	host_interface = n;
	return true;
}

int ChannelRep::get_host_interface() {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::get_host_interface");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::get_host_interface");
	return host_interface;
}

bool ChannelRep::set_protocol(const std::string& _protocol) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::set_protocol",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::set_protocol",
                        " const std::string& " );
	protocol = _protocol;
	return true;
}

const std::string& ChannelRep::get_protocol() {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::get_protocol");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::get_protocol");
	return protocol;
}

bool ChannelRep::set_method(const std::string& _method) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::set_method",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::set_method",
                        " const std::string& " );
	method = _method;
	return true;
}

const std::string& ChannelRep::get_method() {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::get_method");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::get_method");
	return method;
}

