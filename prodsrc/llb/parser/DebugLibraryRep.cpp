/*
 *    DebugLibraryRep.cpp
 *
 *    Class to implement the intermediate parser representation for the
 *    DebugLibrary architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    DebugLibrary architectural element.
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
#include "parser/DebugLibraryRep.hpp"
#include "debug/Verify.hpp"

DebugLibraryRep::DebugLibraryRep() : library_name() {
	SWDEBUGP1( 5, Verify::PARSER, "DebugLibraryRep::DebugLibraryRep");
	SWDEBUG1( 5, Verify::TRACE, "DebugLibraryRep::DebugLibraryRep");
}

DebugLibraryRep::DebugLibraryRep(const std::string& lib_name) {
	SWDEBUGP2( 5, Verify::PARSER, "DebugLibraryRep::DebugLibraryRep",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryRep::DebugLibraryRep",
                        " const std::string& " );
	library_name = lib_name;
}

DebugLibraryRep::DebugLibraryRep(const DebugLibraryRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "DebugLibraryRep::DebugLibraryRep",
                        " const DebugLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryRep::DebugLibraryRep",
                        " const DebugLibraryRep& " );
	library_name = l.library_name;
}

DebugLibraryRep::~DebugLibraryRep() {
	SWDEBUGP1( 5, Verify::PARSER, "DebugLibraryRep::~DebugLibraryRep");
	SWDEBUG1( 5, Verify::TRACE, "DebugLibraryRep::~DebugLibraryRep");
}

DebugLibraryRep& DebugLibraryRep::operator=(const DebugLibraryRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "DebugLibraryRep::operator=",
                        " const DebugLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryRep::operator=",
                        " const DebugLibraryRep& " );
	library_name = l.library_name;
	return *this;
}

bool operator==(const DebugLibraryRep& lhs, const DebugLibraryRep& rhs) {
	SWDEBUGP2( 5, Verify::PARSER, "DebugLibraryRep::operator==",
                        " const DebugLibraryRep&, const DebugLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryRep::operator==",
                        " const DebugLibraryRep&, const DebugLibraryRep& " );
	return lhs.library_name == rhs.library_name;
}

bool DebugLibraryRep::set_library_name(const std::string& name) {
	SWDEBUGP2( 5, Verify::PARSER, "DebugLibraryRep::set_library_name",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryRep::set_library_name",
                        " const std::string& " );
	library_name = name;
	return true;
}

const std::string& DebugLibraryRep::get_library_name() const {
	SWDEBUGP1( 5, Verify::PARSER, "DebugLibraryRep::get_library_name");
	SWDEBUG1( 5, Verify::TRACE, "DebugLibraryRep::get_library_name");
	return library_name;
}

void DebugLibraryRep::dump(size_t indent) {
	SWDEBUGP2( 5, Verify::PARSER, "DebugLibraryRep::dump",
                        " size_t " );
	SWDEBUG2( 5, Verify::TRACE, "DebugLibraryRep::dump",
                        " size_t " );
	std::string ind;
        indent == 0 ? ind = std::string(indent, '\t') : ind = std::string("");
        std::string ind2(indent + 1, '\t');
        std::cerr << ind << "DebugLibraryRep contents:" << std::endl;
        std::cerr << ind2 << "library_name = " << library_name << std::endl;
}

