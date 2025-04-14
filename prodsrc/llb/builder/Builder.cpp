
/*
 *    Builder.cpp
 *
 *    Class to implement the Builder architectural element.
 *
 *    Class to implement the Builder architectural element.
 *    The class implements the Builder element of the construction
 *    methods to build the model.
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

#include "builder/Builder.hpp"
#include "log/Logger.hpp"
#include "debug/Verify.hpp"

#define JSON_MODULE_PATH "module/json"
#define MDL_MODULE_PATH "module/mdl"

Builder::Builder() {
	SWDEBUGP1( 5, Verify::BUILDER, "Builder::Builder");
	SWDEBUG1( 5, Verify::TRACE, "Builder::Builder");
	root = NULL;
}

Builder::~Builder() {
	SWDEBUGP1( 5, Verify::BUILDER, "Builder::~Builder");
	SWDEBUG1( 5, Verify::TRACE, "Builder::~Builder");
}

Translator* Builder::get_root() {
	SWDEBUGP1( 5, Verify::BUILDER, "Builder::get_root");
	SWDEBUG1( 5, Verify::TRACE, "Builder::get_root");
	return root;
}

int Builder::__logger( LOG_TYPE severity, const char* message ) {
	SWDEBUGP2( 5, Verify::BUILDER, "Builder::__logger",
                        " LOG_TYPE, const char* " );
	SWDEBUG2( 5, Verify::TRACE, "Builder::__logger",
                        " LOG_TYPE, const char* " );
	Logger* l_p = Logger::get_logger();
	return l_p->log(severity, message);
}

bool Builder::__file_exists(const std::string& name) {
	SWDEBUGP2( 5, Verify::BUILDER, "Builder::__file_exists",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "Builder::__file_exists",
                        " const std::string& " );
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

void Builder::set_search_path(std::filesystem::path sd) {
	SWDEBUGP2( 5, Verify::BUILDER, "Builder::__set_search_path",
                        " const std::filesystem::path " );
	SWDEBUG2( 5, Verify::TRACE, "Builder::__set_search_path",
                        " const std::filesystem::path " );
	search_directory = sd;
}

