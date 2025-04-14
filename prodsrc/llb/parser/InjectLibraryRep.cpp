/*
 *    InjectLibraryRep.cpp
 *
 *    Class to implement the intermediate parser representation for the
 *    InjectLibrary architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    InjectLibrary architectural element.
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

#include <iostream>
#include "parser/InjectLibraryRep.hpp"
#include "debug/Verify.hpp"

InjectLibraryRep::InjectLibraryRep() : library_name() {
	SWDEBUGP1( 5, Verify::PARSER, "InjectLibraryRep::InjectLibraryRep");
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryRep::InjectLibraryRep");
}

InjectLibraryRep::InjectLibraryRep(const std::string& lib_name) {
	SWDEBUGP2( 5, Verify::PARSER, "InjectLibraryRep::InjectLibraryRep",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryRep::InjectLibraryRep",
                        " const std::string& " );
	library_name = lib_name;
}

InjectLibraryRep::InjectLibraryRep(const InjectLibraryRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "InjectLibraryRep::InjectLibraryRep",
                        " const InjectLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryRep::InjectLibraryRep",
                        " const InjectLibraryRep& " );
	library_name = l.library_name;
}

InjectLibraryRep::~InjectLibraryRep() {
	SWDEBUGP1( 5, Verify::PARSER, "InjectLibraryRep::~InjectLibraryRep");
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryRep::~InjectLibraryRep");
}

InjectLibraryRep& InjectLibraryRep::operator=(const InjectLibraryRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "InjectLibraryRep::operator==",
                        " const InjectLibraryRep&, const InjectLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryRep::operator==",
                        " const InjectLibraryRep&, const InjectLibraryRep& " );
	library_name = l.library_name;
	return *this;
}

bool InjectLibraryRep::set_library_name(const std::string& name) {
	SWDEBUGP2( 5, Verify::PARSER, "InjectLibraryRep::set_library_name",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryRep::set_library_name",
                        " const std::string& " );
	library_name = name;
	return true;
}

const std::string& InjectLibraryRep::get_library_name() const {
	SWDEBUGP1( 5, Verify::PARSER, "InjectLibraryRep::get_library_name");
	SWDEBUG1( 5, Verify::TRACE, "InjectLibraryRep::get_library_name");
	return library_name;
}

void InjectLibraryRep::dump(size_t indent) {
	SWDEBUGP2( 5, Verify::PARSER, "InjectLibraryRep::dump",
                        " size_t " );
	SWDEBUG2( 5, Verify::TRACE, "InjectLibraryRep::dump",
                        " size_t " );
	std::string ind;
        indent == 0 ? ind = std::string(indent, '\t') : ind = std::string("");
        std::string ind2(indent + 1, '\t');
        std::cerr << ind << "InjectLibraryRep contents:" << std::endl;
        std::cerr << ind2 << "library_name = " << library_name << std::endl;
}

