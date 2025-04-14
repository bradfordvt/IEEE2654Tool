/*
 *    TranslatorRep.cpp
 *
 *    Class to implement the intermediate parser representation for the
 *    Translator architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    Translator architectural element.
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
static const char __date__[] = "2024/06/08";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <stdexcept>
#include <iostream>
#include "parser/TranslatorRep.hpp"
#include "debug/Verify.hpp"

TranslatorRep::TranslatorRep() : module_name(), instance_name(), path(),
				num_children(0), translator_uid(-1),
				client(-1), command_interface(-1),
				inject_interface(-1),
				cmdlib(), injlib(), dbglib(), trmlib(),
				property_keys(),
				property_values(),
				property_types(),
				children_indexes() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::TranslatorRep");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::TranslatorRep");
}

TranslatorRep::TranslatorRep(const std::string& _module_name, const std::string& _instance_name, const std::string& _path) :
				num_children(0), translator_uid(-1),
				client(-1), command_interface(-1),
				inject_interface(-1),
				cmdlib(), injlib(), dbglib(), trmlib(),
				property_keys(),
				property_values(),
				property_types(),
				children_indexes(),
				properties() {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::TranslatorRep",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::TranslatorRep",
                        " const std::string& " );
	this->module_name = _module_name;
	this->instance_name = _instance_name;
	this->path = _path;
}

TranslatorRep::TranslatorRep(const TranslatorRep& t) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::TranslatorRep",
                        " const TranslatorRep& " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::TranslatorRep",
                        " const TranslatorRep& " );
	module_name = t.module_name;
	instance_name = t.instance_name;
	path = t.path;
	num_children = t.num_children;
	translator_uid = t.translator_uid;
	client = t.client;
	command_interface = t.command_interface;
	inject_interface = t.inject_interface;
	cmdlib = t.cmdlib;
	injlib = t.injlib;
	dbglib = t.dbglib;
	trmlib = t.trmlib;
	property_keys = t.property_keys;
	property_values = t.property_values;
	property_types = t.property_types;
	children_indexes = t.children_indexes;
	properties = t.properties;
}

TranslatorRep::~TranslatorRep() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::~TranslatorRep");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::~TranslatorRep");
}

TranslatorRep& TranslatorRep::operator=(const TranslatorRep& t) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::operator=",
                        " const TranslatorRep& " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::operator=",
                        " const TranslatorRep& " );
	module_name = t.module_name;
	instance_name = t.instance_name;
	path = t.path;
	num_children = t.num_children;
	translator_uid = t.translator_uid;
	client = t.client;
	command_interface = t.command_interface;
	inject_interface = t.inject_interface;
	cmdlib = t.cmdlib;
	injlib = t.injlib;
	dbglib = t.dbglib;
	trmlib = t.trmlib;
	property_keys = t.property_keys;
	property_values = t.property_values;
	property_types = t.property_types;
	children_indexes = t.children_indexes;
	properties = t.properties;
	return *this;
}

bool TranslatorRep::set_module_name(const std::string& s) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_module_name",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_module_name",
                        " const std::string& " );
	module_name = s;
	return true;
}

bool TranslatorRep::set_instance_name(const std::string& s) {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_module_name");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_module_name");
	instance_name = s;
	return true;
}

bool TranslatorRep::set_path(const std::string& s) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_path",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_.name",
                        " const std::string& " );
	path = s;
	return true;
}

bool TranslatorRep::set_client(int n) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_client",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_client",
                        " int " );
	client = n;
	return true;
}

bool TranslatorRep::set_command_interface(int n) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_command_interface",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_command_interface",
                        " int " );
	command_interface = n;
	return true;
}

bool TranslatorRep::set_inject_interface(int n) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_inject_interface",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_inject_interface",
                        " int " );
	inject_interface = n;
	return true;
}

bool TranslatorRep::set_num_children(int n) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_num_children",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_num_children",
                        " int " );
	num_children = n;
	return true;
}

bool TranslatorRep::set_TransformLibraryRep(const TransformLibraryRep& _trmlib) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_TransformLibraryRep",
                        " const TransformLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_TransformLibraryRep",
                        " const TransformLibraryRep& " );
	this->trmlib = _trmlib;
	return true;
}

bool TranslatorRep::set_DebugLibraryRep(const DebugLibraryRep& _dbglib) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_DebugLibraryRep",
                        " const DebugLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_DebugLibraryRep",
                        " const DebugLibraryRep& " );
	this->dbglib = _dbglib;
	return true;
}

bool TranslatorRep::set_CommandLibraryRep(const CommandLibraryRep& _cmdlib) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_CommandLibraryRep",
                        " const CommandLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_CommandLibraryRep",
                        " const CommandLibraryRep& " );
	this->cmdlib = _cmdlib;
	return true;
}

bool TranslatorRep::set_InjectLibraryRep(const InjectLibraryRep& _injlib) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_InjectLibraryRep",
                        " const InjectLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_InjectLibraryRep",
                        " const InjectLibraryRep& " );
	this->injlib = _injlib;
	return true;
}

bool TranslatorRep::add_child(int _key) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::add_child",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::add_child",
                        " int " );
	children_indexes.push_back(_key);
	return true;
}

bool TranslatorRep::add_host(int _key) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::add_host",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::add_host",
                        " int " );
	host_indexes.push_back(_key);
	return true;
}

bool TranslatorRep::set_translator_uid(uint32_t uid) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_translator",
                        " uint32_t " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_translator",
                        " uint32_t " );
	translator_uid = uid;
	return true;
}

bool TranslatorRep::add_property(const std::string& _key, const std::string& _value, const std::string& _type) { 
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::add_property",
                        " const std::string&, const std::string&, const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::add_property",
                        " const std::string&, const std::string&, const std::string& " );
	property_keys.push_back(_key);
	property_values.push_back(_value);
	property_types.push_back(_type);
	return true;
}

bool TranslatorRep::set_key(int k) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_key",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_key",
                        " int " );
	key = k;
	return true;
}

int TranslatorRep::get_key() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_key");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_key");
	return key;
}

int TranslatorRep::get_client() {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_client",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_client",
                        " int " );
	return client;
}

uint32_t TranslatorRep::get_translator_uid() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_translator_uid");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_translator_uid");
	return translator_uid;
}

int TranslatorRep::get_command_interface() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_command_interface");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_command_interface");
	return command_interface;
}

int TranslatorRep::get_inject_interface() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_inject_interface");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_inject_interface");
	return inject_interface;
}

const TransformLibraryRep& TranslatorRep::get_TransformLibraryRep() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_TransformLibraryRep");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_TransformLibraryRep");
	return trmlib;
}

const DebugLibraryRep& TranslatorRep::get_DebugLibraryRep() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_DebugLibraryRep");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_DebugLibraryRep");
	return dbglib;
}

const CommandLibraryRep& TranslatorRep::get_CommandLibraryRep() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_CommandLibraryRep");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_CommandLibraryRep");
	return cmdlib;
}

const InjectLibraryRep& TranslatorRep::get_InjectLibraryRep() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_InjectLibraryRep");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_InjectLibraryRep");
	return injlib;
}

int TranslatorRep::get_num_children() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_num_children");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_num_children");
	return num_children;
}

int TranslatorRep::get_child(int index) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::set_child",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::set_child",
                        " int " );
	try {
                int chndx = children_indexes.at(index);
                return chndx;
        }
        catch(std::out_of_range o) {
                return -1;
        }
}

int TranslatorRep::get_host(int index) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::get_host",
                        " int " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::get_host",
                        " int " );
	try {
                int hndx = host_indexes.at(index);
                return hndx;
        }
        catch(std::out_of_range o) {
                return -1;
        }
}

const char* TranslatorRep::get_path() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_path");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_path");
	return path.c_str();
}

const char* TranslatorRep::get_module_name() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_module_name");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_module_name");
	return module_name.c_str();
}

const char* TranslatorRep::get_instance_name() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_instance_name");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_instance_name");
	return instance_name.c_str();
}

const std::string& TranslatorRep::get_properties() {
	SWDEBUGP1( 5, Verify::PARSER, "TranslatorRep::get_properties");
	SWDEBUG1( 5, Verify::TRACE, "TranslatorRep::get_properties");
	if(properties.length() == 0) {
		size_t sz = property_keys.size();
		properties = "{\n\t\"properties\" : {";
		for(size_t i = 0; i < sz; i++) {
			if(i > 0) properties += ",\n";
			else properties += "\n";
			properties += "\t\t";
			properties += "\"";
			properties += property_keys[i];
			properties += "\" : \"";
			properties += property_values[i];
			properties += "\"";
		}
		properties += "\n\t}\n}";
	}
	// std::cerr << "properties = " << properties << std::endl;
	return properties;
}

void TranslatorRep::dump(size_t indent) {
	SWDEBUGP2( 5, Verify::PARSER, "TranslatorRep::dump",
                        " size_t " );
	SWDEBUG2( 5, Verify::TRACE, "TranslatorRep::dump",
                        " size_t " );
        std::string ind;
        indent == 0 ? ind = std::string(indent, '\t') : ind = std::string("");
        std::string ind2(indent + 1, '\t');
        std::string ind3(indent + 2, '\t');
        std::cerr << ind << "TranslatorRep contents:" << std::endl;
        std::cerr << ind2 << "module_name = " << module_name << std::endl;
        std::cerr << ind2 << "instance_name = " << instance_name << std::endl;
        std::cerr << ind2 << "path = " << path << std::endl;
        std::cerr << ind2 << "key = " << key << std::endl;
        std::cerr << ind2 << "num_children = " << num_children << std::endl;
        std::cerr << ind2 << "translator_uid = " << translator_uid << std::endl;
        std::cerr << ind2 << "client = " << client << std::endl;
        std::cerr << ind2 << "command_interface = " << command_interface << std::endl;
        std::cerr << ind2 << "inject_interface = " << inject_interface << std::endl;
        std::cerr << ind2 << "properties = " << properties << std::endl;
        std::cerr << ind2 << "property_keys:" << std::endl;
        std::cerr << ind3 << "[";
	for(auto pk : property_keys) {
		std::cerr << pk << ", ";
	}
        std::cerr << "]" << std::endl;

        std::cerr << ind2 << "property_values:" << std::endl;
        std::cerr << ind3 << "[";
	for(auto pv : property_values) {
		std::cerr << pv << ", ";
	}
        std::cerr << "]" << std::endl;

        std::cerr << ind2 << "property_types:" << std::endl;
        std::cerr << ind3 << "[";
	for(auto pt : property_types) {
		std::cerr << pt << ", ";
	}
        std::cerr << "]" << std::endl;

        std::cerr << ind2 << "children_indexes:" << std::endl;
        std::cerr << ind3 << "[";
	for(auto ci : children_indexes) {
		std::cerr << ci << ", ";
	}
        std::cerr << "]" << std::endl;

        std::cerr << ind2 << "host indexes:" << std::endl;
        std::cerr << ind3 << "[";
	for(auto hi : host_indexes) {
		std::cerr << hi << ", ";
	}
        std::cerr << "]" << std::endl;

	cmdlib.dump(indent + 1);
	injlib.dump(indent + 1);
	dbglib.dump(indent + 1);
	trmlib.dump(indent + 1);
}

