/*
 *    HostInterfaceRep.cpp
 *
 *    Class to implement the intermediate parser representation for the
 *    HostInterface architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    HostInterface architectural element.
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

#include "parser/HostInterfaceRep.hpp"
#include "debug/Verify.hpp"

HostInterfaceRep::HostInterfaceRep() : name(), protocol("IEEE2654.proto"), key(-1), channel(-1), translator(-1) {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::ChannelRep");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::ChannelRep");
}

HostInterfaceRep::HostInterfaceRep(const std::string& _name) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::ChannelRep",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::ChannelRep",
                        " const std::string& " );
	name = _name;
	protocol = "IEEE2654.proto";
	key = -1;
	channel = -1;
	translator = -1;
}

HostInterfaceRep::HostInterfaceRep(const HostInterfaceRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::ChannelRep",
                        " const ChannelRep& " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::ChannelRep",
                        " const ChannelRep& " );
	name = l.name;
	protocol = l.protocol;
	key = l.key;
	channel = l.channel;
	translator = l.translator;
}

HostInterfaceRep::~HostInterfaceRep() {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::~ChannelRep");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::~ChannelRep");
}

HostInterfaceRep& HostInterfaceRep::operator=(const HostInterfaceRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::operator=",
                        " const ChannelRep& " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::operator=",
                        " const ChannelRep& " );
	name = l.name;
	protocol = l.protocol;
	channel = l.channel;
	translator = l.translator;
	return *this;
}

bool operator==(const HostInterfaceRep& lhs, const HostInterfaceRep& rhs) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::operator==",
                        " const ChannelRep&, const ChannelRep& " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::operator==",
                        " const ChannelRep&, const ChannelRep& " );
	return (lhs.name == rhs.name) && \
		(lhs.protocol == rhs.protocol) && \
		(lhs.channel == rhs.channel) && \
		(lhs.translator == rhs.translator);
}

bool HostInterfaceRep::set_name(const std::string& _name) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::set_name",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::set_name",
                        " const std::string& " );
	name = _name;
	return true;
}

const std::string& HostInterfaceRep::get_name() {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::get_name");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::get_name");
	return name;
}

bool HostInterfaceRep::set_channel(int ch) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::set_channel",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::set_channel",
                        " int " );
	channel = ch;
	return true;
}

int HostInterfaceRep::get_channel() {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::get_channel");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::get_channel");
	return channel;
}

bool HostInterfaceRep::set_translator(int t) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::set_translator",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::set_translator",
                        " int " );
	translator = t;
	return true;
}

int HostInterfaceRep::get_translator() {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::get_translator");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::get_translator");
	return translator;
}

bool HostInterfaceRep::set_key(int k) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::set_key",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::set_key",
                        " int " );
	key = k;
	return true;
}

int HostInterfaceRep::get_key() {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::get_key");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::get_key");
	return key;
}

bool HostInterfaceRep::set_protocol(const std::string& _protocol) {
	SWDEBUGP2( 5, Verify::PARSER, "ChannelRep::set_protocol",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ChannelRep::set_protocol",
                        " const std::string& " );
	protocol = _protocol;
	return true;
}

const std::string& HostInterfaceRep::get_protocol() {
	SWDEBUGP1( 5, Verify::PARSER, "ChannelRep::get_protocol");
	SWDEBUG1( 5, Verify::TRACE, "ChannelRep::get_protocol");
	return protocol;
}

