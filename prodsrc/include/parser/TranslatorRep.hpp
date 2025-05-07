/*
 *    TranslatorRep.hpp
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

#ifndef INCLUDE_PARSER_TRANSLATORREP_HPP_
#define INCLUDE_PARSER_TRANSLATORREP_HPP_

#include <string>
#include <vector>
#include <cstdint>

#include "parser/TransformLibraryRep.hpp"
#include "parser/DebugLibraryRep.hpp"
#include "parser/CommandLibraryRep.hpp"
#include "parser/InjectLibraryRep.hpp"

class TranslatorRep {
#ifdef TEST
	friend class TranslatorRep_TestCases;
#endif
public:
	TranslatorRep();
	TranslatorRep(const std::string& _module_name, const std::string& _instance_name, const std::string& _path);
	TranslatorRep(const TranslatorRep& t);
	~TranslatorRep();

	TranslatorRep& operator=(const TranslatorRep& t);

	bool set_module_name(const std::string& s );
	bool set_instance_name(const std::string& s );
	bool set_path(const std::string& s );
	bool set_client(int n);
	bool set_command_interface(int n);
	bool set_inject_interface(int n);
	bool set_num_children(int n);
	bool set_TransformLibraryRep(const TransformLibraryRep& _trmlib);
	bool set_DebugLibraryRep(const DebugLibraryRep& _dbglib);
	bool set_CommandLibraryRep(const CommandLibraryRep& _cmdlib);
	bool set_InjectLibraryRep(const InjectLibraryRep& _injlib);
	bool add_child(int _key);
	bool add_host(int _key);
	bool set_translator_uid(uint32_t uid);
	bool add_property(const std::string& _key, const std::string& _value, const std::string& _type);
	bool set_key(int k);
	int get_key();
	int get_client();
	uint32_t get_translator_uid();
	int get_command_interface();
	int get_inject_interface();
	const TransformLibraryRep& get_TransformLibraryRep();
	const DebugLibraryRep& get_DebugLibraryRep();
	const CommandLibraryRep& get_CommandLibraryRep();
	const InjectLibraryRep& get_InjectLibraryRep();
	int get_num_children();
	int get_child(int index);
	int get_host(int index);
	const char* get_path();
	const char* get_module_name();
	const char* get_instance_name();
	const std::string& get_properties(); // return JSON string of properties for config

	void dump(size_t indent);

private:
	std::string module_name;
	std::string instance_name;
	std::string path;
	int key; // Index into table of Translator instances in repository
	int num_children;
	uint32_t translator_uid;
	int client;
	int command_interface;
	int inject_interface;
	CommandLibraryRep cmdlib;
	InjectLibraryRep injlib;
	DebugLibraryRep dbglib;
	TransformLibraryRep trmlib;
	std::vector<std::string> property_keys;
	std::vector<std::string> property_values;
	// Types of values in properties: string, int, bool
	std::vector<std::string> property_types;
	std::vector<int> children_indexes;
	std::vector<int> host_indexes;
	std::string properties;
};

#endif /* INCLUDE_PARSER_TRANSLATORREP_HPP_ */
