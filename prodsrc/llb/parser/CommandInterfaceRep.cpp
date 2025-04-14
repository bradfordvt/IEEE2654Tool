/*
 *    CommandInterfaceRep.cpp
 *
 *    Class to implement the intermediate parser representation for the
 *    CommandInterface architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    CommandInterface architectural element.
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

#include "parser/CommandInterfaceRep.hpp"

CommandInterfaceRep::CommandInterfaceRep() : name(), protocol("IEEE2654.proto"), translator(0) {
}

CommandInterfaceRep::CommandInterfaceRep(const std::string& _name) {
	name = _name;
	protocol = "IEEE2654.proto";
	translator = 0;
	key = -1;
	uid = -1;
}

CommandInterfaceRep::CommandInterfaceRep(const CommandInterfaceRep& l) {
	name = l.name;
	protocol = l.protocol;
	translator = l.translator;
	key = l.key;
	uid = l.uid;
}

CommandInterfaceRep::~CommandInterfaceRep() {
}

CommandInterfaceRep& CommandInterfaceRep::operator=(const CommandInterfaceRep& l) {
	name = l.name;
	protocol = l.protocol;
	translator = l.translator;
	key = l.key;
	uid = l.uid;
	return *this;
}

bool CommandInterfaceRep::set_name(const std::string& _name) {
	name = _name;
	return true;
}

const std::string& CommandInterfaceRep::get_name() {
	return name;
}

bool CommandInterfaceRep::set_translator(int t) {
	translator = t;
	return true;
}

int CommandInterfaceRep::get_translator() {
	return translator;
}

bool CommandInterfaceRep::set_key(int k) {
	key = k;
	return true;
}

int CommandInterfaceRep::get_key() {
	return key;
}

bool CommandInterfaceRep::set_protocol(const std::string& _protocol) {
	protocol = _protocol;
	return true;
}

const std::string& CommandInterfaceRep::get_protocol() {
	return protocol;
}

bool CommandInterfaceRep::set_uid(int u) {
	uid = u;
	return true;
}

int CommandInterfaceRep::get_uid() {
	return uid;
}

