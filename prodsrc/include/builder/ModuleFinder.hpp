/*
 *    ModuleFinder.hpp
 *
 *    Class to implement the ModuleFinder architectural element.
 *
 *    Class to implement the ModuleFinder architectural element.
 *    The class implements the ModuleFinder of the construction
 *    methods to build the model.  The class searches all the MDL
 *    files in the module description path and maps the module
 *    name found in each file with the file name.  As module names
 *    are encountered in an instance statement, the module type
 *    name will be found from this class's cache to help traverse 
 *    the building of the tree by depth first search.
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

#ifndef INCLUDE_BUILDER_MODULEFINDER_HPP_
#define INCLUDE_BUILDER_MODULEFINDER_HPP_

#include <filesystem>
#include <vector>
#include <string>
#include <map>
#include "log/Logger.hpp"

class ModuleFinder {
#ifdef TEST
	friend class ModuleFinder_TestCases;
#endif
public:
	static ModuleFinder* get_ModuleFinder();

	ModuleFinder();
	~ModuleFinder();

	int find_modules(const std::filesystem::path& directory);
	const std::string& find_module(const char* module);
	const std::string& get_module(const std::string& filename);
	const std::string& get_filename(const std::string& module);

protected:
	int __logger(LOG_TYPE severity, const char* message);
	bool __file_exists(const std::string& name);

private:
	const std::string& __locate_module_name_in_file(const std::string& filename);
	const std::string& __locate_module_name_in_line(const std::string& line);
	std::vector<std::string> __split(const std::string& str, const std::string& delimiters);
	ModuleFinder(const ModuleFinder& mf);
	ModuleFinder& operator=(const ModuleFinder& mf);

	std::map<std::string, std::string> file_to_name;
	std::map<std::string, std::string> name_to_file;

	static std::string empty_string;
	static ModuleFinder *mf_p;
};

#endif /* INCLUDE_BUILDER_MODULEFINDER_HPP_ */
