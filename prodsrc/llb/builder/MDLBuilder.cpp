/*
 *    MDLBuilder.cpp
 *
 *    Class to implement the MDLBuilder architectural element.
 *
 *    Class to implement the MDLBuilder architectural element.
 *    The class implements the MDLBuilder element of the construction
 *    methods to build the model.  The MDLParser is used to construct
 *    the module node in the branch with the result being a persistent
 *    representation as a JSON file for the entire root.
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
#include <string.h>

#include <sys/stat.h>

#include "builder/MDLBuilder.hpp"

#define JSON_MODULE_PATH "module/json"
#define MDL_MODULE_PATH "module/mdl"

MDLBuilder::MDLBuilder() {
	SWDEBUGP1( 5, Verify::BUILDER, "MDLBuilder::MDLBuilder");
	SWDEBUG1( 5, Verify::TRACE, "MDLBuilder::MDLBuilder");
}

MDLBuilder::~MDLBuilder() {
	SWDEBUGP1( 5, Verify::BUILDER, "MDLBuilder::~MDLBuilder");
	SWDEBUG1( 5, Verify::TRACE, "MDLBuilder::~MDLBuilder");
}

int MDLBuilder::build_root(const char* module_name) {
	SWDEBUGP2( 5, Verify::BUILDER, "MDLBuilder::build_root",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "MDLBuilder::build_root",
                        " const char* " );
	std::string file_path(JSON_MODULE_PATH);
	file_path += "/";
	file_path += module_name;
	file_path += ".json";
	std::string mdl_path(MDL_MODULE_PATH);
	mdl_path += "/";
	mdl_path += module_name;
	mdl_path += ".mdl";

	if(__file_exists(file_path)) {
		JSONMDLBuilder json_builder;
		int ret = json_builder.build_root(file_path);
		if(ret == 0) {
			root = json_builder.get_root();
		}
		return ret;
	}
	else if(__file_exists(mdl_path)) {
		MDLMDLBuilder mdl_builder;
		int ret = mdl_builder.build_root(file_path);
		if(ret == 0) {
			root = mdl_builder.get_root();
		}
		return ret;
	}
	else {
		return -1;
	}
}

Translator& MDLBuilder::get_root() {
	SWDEBUGP1( 5, Verify::BUILDER, "MDLBuilder::get_root");
	SWDEBUG1( 5, Verify::TRACE, "MDLBuilder::get_root");
	return root;
}

bool MDLBuilder::__file_exists(const std::string& name) {
	SWDEBUGP2( 5, Verify::BUILDER, "MDLBuilder::__file_exists",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "MDLBuilder::__file_exists",
                        " const std::string& " );
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
