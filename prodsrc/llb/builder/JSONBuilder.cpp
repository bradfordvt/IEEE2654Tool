/*
 *    JSONBuilder.cpp
 *
 *    Class to implement the JSONBuilder architectural element.
 *    Class to implement the JSONBuilder architectural element.
 *    The class implements the JSONBuilder element of the construction
 *    methods to build the model.  Module Desription Language (MDL) files
 *    describe the module at a node in the IEEE2654ModelTree, but parsing
 *    MDL files repetatively for every node instance in the tree is costly.
 *    Thus, the MDL, once parsed, is stored persistently as a JSON description
 *    file.  The JSONBuilder is used to read in the already vetted module
 *    description stored as a single JSON file for the entire branch.
 *    The Builder class is used to ensure the children of the current root
 *    are up to date and the JSON version is updated if the MDL version is
 *    newer.
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
static const char __date__[] = "2024/06/05";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <cctype> // for isspace
#include <algorithm>

#include <string.h>
#include <sys/stat.h>

#include "builder/PathManager.hpp"
#include "builder/JSONBuilder.hpp"
#include "parser/JSONParser.hpp"
#include "repository/Repository.hpp"
#include "debug/Verify.hpp"

#define JSON_MODULE_PATH "module/json"

JSONBuilder::JSONBuilder() : Builder() {
	SWDEBUGP1( 5, Verify::BUILDER, "JSONBuilder::JSONBuilder");
	SWDEBUG1( 5, Verify::TRACE, "JSONBuilder::JSONBuilder");
	// __path_to_vector();
	pm = PathManager::get_PathManager();
}

JSONBuilder::~JSONBuilder() {
	SWDEBUGP1( 5, Verify::BUILDER, "JSONBuilder::~JSONBuilder");
	SWDEBUG1( 5, Verify::TRACE, "JSONBuilder::~JSONBuilder");
}

int JSONBuilder::build_root(const std::string& module_name) {
	SWDEBUGP2( 5, Verify::BUILDER, "JSONBuilder::build_root",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONBuilder::build_root",
                        " const std::string& " );
	std::string module_path = __find_module(module_name);
	if(module_path.length()) {
		JSONParser p;
		bool pret = p.parse(module_path);
		if(pret) {
			// Repository is now populated and IEEE2654Tree model is built
			// Now set the root to the rooted Translator in the Repository
			Repository* rep = Repository::get_repository();
			root = rep->get_TopModule();
			return 0;
		}
		else {
			// IEEE2654Tree model failed to build
			return -1;
		}
	}
	else {
		// Failed to locate the module file
		return -2;
	}
}

std::string JSONBuilder::__find_module(const std::string& module_name) {
	SWDEBUGP2( 5, Verify::BUILDER, "JSONBuilder::__find_module",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONBuilder::__find_module",
                        " const std::string& " );
	std::string path;
	const std::vector<std::string>& paths = pm->get_module_search_path(); 
	for(auto iter = paths.begin(); iter != paths.end(); iter++) {
		path = *iter + "/" + module_name + ".json";
		// std::cerr << "path = " << path << std::endl;
		if(__file_exists(path)) {
			// std::cerr << "found module = " << path << std::endl;
			return path;
		}
	}
	// std::cerr << "did not find module = " << module_name << std::endl;
	path = "";
	// std::cerr << "returning path = " << path << std::endl;
	return path;
}

bool JSONBuilder::__file_exists(const std::string& name) {
	SWDEBUGP2( 5, Verify::BUILDER, "JSONBuilder::__file_exists",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONBuilder::__file_exists",
                        " const std::string& " );
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

