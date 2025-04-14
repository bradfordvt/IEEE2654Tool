/*
 *    TopModuleRep.hpp
 *
 *    Class to implement the intermediate parser representation for the
 *    TopModule architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    TopModule (root) architectural element.
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

#ifndef INCLUDE_PARSER_TOPMODULEREP_HPP_
#define INCLUDE_PARSER_TOPMODULEREP_HPP_

#include <string>

class TopModuleRep {
#ifdef TEST
	friend class TopModuleRep_TestCases;
#endif
public:
	TopModuleRep();
	TopModuleRep(const std::string& _module_name);
	TopModuleRep(const TopModuleRep& l);
	~TopModuleRep();

	TopModuleRep& operator=(const TopModuleRep& l);

	bool set_module_name(const std::string& _module_name);
	const std::string& get_module_name();
	bool set_num_translators(int count);
	int get_num_translators();
	bool set_num_channels(int count);
	int get_num_channels();
	bool set_num_host_interfaces(int count);
	int get_num_host_interfaces();
	bool set_num_client_interfaces(int count);
	int get_num_client_interfaces();
	bool set_num_command_interfaces(int count);
	int get_num_command_interfaces();
	bool set_num_inject_interfaces(int count);
	int get_num_inject_interfaces();
	bool set_translator(int count);
	int get_translator();

	void dump(size_t indent);

private:
	std::string module_name;
	int num_translators;
	int num_channels;
	int num_host_interfaces;
	int num_client_interfaces;
	int num_command_interfaces;
	int num_inject_interfaces;
	int translator;
};

#endif /* INCLUDE_PARSER_TOPMODULEREP_HPP_ */
