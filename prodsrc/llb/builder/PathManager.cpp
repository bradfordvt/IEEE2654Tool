
/*
 *    PathManager.cpp
 *
 *    Class to implement the PathManager architectural element.
 *
 *    Class to implement the PathManager architectural element.
 *    The class implements the PathManager of the construction
 *    methods to build the model.  The class provides OS independent
 *    search paths for model types used by the application as well
 *    as search paths for the plug-in library extensions for the
 *    Translator nodes of the model architecture.
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
static const char __date__[] = "2024/09/09";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <iostream>
#include <cstdlib>
#include <cctype> // for isspace
#include <algorithm>
#include <sys/stat.h>
#include "builder/PathManager.hpp"
#include "debug/Verify.hpp"

PathManager* PathManager::pm_p = NULL;

PathManager* PathManager::get_PathManager() {
	// SWDEBUGP1( 5, Verify::BUILDER, "PathManager::get_PathManager");
	// SWDEBUG1( 5, Verify::TRACE, "PathManager::get_PathManager");
	if(pm_p == NULL) {
		pm_p = new PathManager();
	}
	return pm_p;
}

PathManager::PathManager() : path_separator(std::string("/")), pathvar_separator(":") {
	// SWDEBUGP1( 5, Verify::BUILDER, "PathManager::PathManager");
	// SWDEBUG1( 5, Verify::TRACE, "PathManager::PathManager");
	__path_to_vector(std::string("IEEE2654MODULES"), std::string("module_search_path"));
	__path_to_vector(std::string("IEEE2654PLUGINS"), std::string("plugin_search_path"));
	__path_to_vector(std::string("IEEE2654PYTHON"), std::string("python_search_path"));
}

PathManager::~PathManager() {
	// SWDEBUGP1( 5, Verify::BUILDER, "PathManager::~PathManager");
	// SWDEBUG1( 5, Verify::TRACE, "PathManager::~PathManager");
}

bool PathManager::__file_exists(const std::string& name) {
	// SWDEBUGP2( 5, Verify::BUILDER, "PathManager::__file_exists",
                        // " const std::string& " );
	// SWDEBUG2( 5, Verify::TRACE, "PathManager::__file_exists",
                        // " const std::string& " );
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

std::string PathManager::__expand_environment_variables( const std::string &s ) {
	// SWDEBUGP2( 5, Verify::BUILDER, "PathManager::__expand_environment_variables",
                        // " const std::string& " );
	// SWDEBUG2( 5, Verify::TRACE, "PathManager::__expand_environment_variables",
                        // " const std::string& " );
	if( s.find( "${" ) == std::string::npos ) return s;

	std::string pre  = s.substr( 0, s.find( "${" ) );
	std::string post = s.substr( s.find( "${" ) + 2 );

	if( post.find( '}' ) == std::string::npos ) return s;

	std::string variable = post.substr( 0, post.find( '}' ) );
	std::string value    = "";

	post = post.substr( post.find( '}' ) + 1 );

	const char *v = getenv( variable.c_str() );
	if( v != NULL ) value = std::string( v );

	return __expand_environment_variables( pre + value + post );
}

bool PathManager::__path_to_vector(const std::string& varname, const std::string& path_name) {
	// SWDEBUGP2( 5, Verify::BUILDER, "PathManager::__path_to_vector",
                        // " const std::string&, const std::string& " );
	// SWDEBUG2( 5, Verify::TRACE, "PathManager::__path_to_vector",
                        // " const std::string&, const std::string& " );
	// Extract the IEEE2654 environment variable
	std::string path_env;
	if(std::getenv(varname.c_str())) {
		path_env = std::getenv(varname.c_str());
	}
	else {
		return false;
	}
	// std::cerr << "path_env = " << path_env << std::endl;
	if(path_env.length() > 0) {
		path_env = __expand_environment_variables(path_env);
	}
	else {
		return false;
	}
	// std::cerr << "path_env = " << path_env << std::endl;

	std::vector<std::string> *paths_p;
	if(path_name == std::string("module_search_path")) {
		paths_p = &module_search_path;
	}
	else if(path_name == std::string("plugin_search_path")) {
		paths_p = &plugin_search_path;
	}
	else if(path_name == std::string("python_search_path")) {
		paths_p = &python_search_path;
	}
	else {
		// std::cerr << "Path name " << path_name << " does not exist in class." << std::endl;
		return false;
	}
	
	// Split the PATH string into individual paths
	// std::vector<std::string> paths;
	std::string current_path;
	for (char c : path_env) {
		if (c == pathvar_separator[0]) { // ':' on UNIX/Linux/OSX or ';' on Windows
			paths_p->push_back(current_path);
			current_path.clear();
		} else {
			current_path += c;
		}
	}
	if (!current_path.empty()) {
		paths_p->push_back(current_path);
	}
	// std::cerr << "current_path = " << current_path << std::endl;
	
	// Remove trailing whitespace from each path
	for (auto& p : *paths_p) {
		p.erase(std::remove_if(p.begin(), p.end(), ::isspace), p.end());
	}
	// std::cerr << "Exiting __path_to_vector()" << std::endl;
	
#if 0
	// Print the resulting vector
	for (const auto& path : *paths_p) {
		std::cout << path << std::endl;
	}
#endif
	return true;
}
const std::vector<std::string>& PathManager::get_module_search_path() {
	// SWDEBUGP1( 5, Verify::BUILDER, "PathManager::get_module_search_path");
	// SWDEBUG1( 5, Verify::TRACE, "PathManager::get_module_search_path");
	return module_search_path;
}

const std::vector<std::string>& PathManager::get_plugin_search_path() {
	// SWDEBUGP1( 5, Verify::BUILDER, "PathManager::get_plugin_search_path");
	// SWDEBUG1( 5, Verify::TRACE, "PathManager::get_plugin_search_path");
	return plugin_search_path;
}

const std::vector<std::string>& PathManager::get_python_search_path() {
	// SWDEBUGP1( 5, Verify::BUILDER, "PathManager::get_python_search_path");
	// SWDEBUG1( 5, Verify::TRACE, "PathManager::get_python_search_path");
	return python_search_path;
}

const std::string& PathManager::get_path_separator() {
	// SWDEBUGP1( 5, Verify::BUILDER, "PathManager::get_path_separator");
	// SWDEBUG1( 5, Verify::TRACE, "PathManager::get_path_separator");
	return path_separator;
}

const std::string& PathManager::get_pathvar_separator() {
	// SWDEBUGP1( 5, Verify::BUILDER, "PathManager::get_pathvar_separator");
	// SWDEBUG1( 5, Verify::TRACE, "PathManager::get_pathvar_separator");
	return pathvar_separator;
}

