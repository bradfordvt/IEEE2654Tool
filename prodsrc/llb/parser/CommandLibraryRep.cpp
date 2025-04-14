/*
 *    CommandLibraryRep.cpp
 *
 *    Class to implement the intermediate parser representation for the
 *    CommandLibrary architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    CommandLibrary architectural element.
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
#include "parser/CommandLibraryRep.hpp"
#include "debug/Verify.hpp"

CommandLibraryRep::CommandLibraryRep() : library_name() {
	SWDEBUGP1( 5, Verify::PARSER, "CommandLibraryRep::CommandLibraryRep");
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryRep::CommandLibraryRep");
}

CommandLibraryRep::CommandLibraryRep(const std::string& lib_name) {
	SWDEBUGP2( 5, Verify::PARSER, "CommandLibraryRep::CommandLibraryRep",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryRep::CommandLibraryRep",
                        " const std::string& " );
	library_name = lib_name;
}

CommandLibraryRep::CommandLibraryRep(const CommandLibraryRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "CommandLibraryRep::CommandLibraryRep",
                        " const CommandLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryRep::CommandLibraryRep",
                        " const CommandLibraryRep& " );
	library_name = l.library_name;
}

CommandLibraryRep::~CommandLibraryRep() {
	SWDEBUGP1( 5, Verify::PARSER, "CommandLibraryRep::~CommandLibraryRep");
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryRep::~CommandLibraryRep");
}

CommandLibraryRep& CommandLibraryRep::operator=(const CommandLibraryRep& l) {
	SWDEBUGP2( 5, Verify::PARSER, "CommandLibraryRep::operator=",
                        " const CommandLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryRep::operator=",
                        " const CommandLibraryRep& " );
	library_name = l.library_name;
	return *this;
}

bool operator==(const CommandLibraryRep& lhs, const CommandLibraryRep& rhs) {
	SWDEBUGP2( 5, Verify::PARSER, "CommandLibraryRep::operator==",
                        " const CommandLibraryRep&, const CommandLibraryRep& " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryRep::operator==",
                        " const CommandLibraryRep&, const CommandLibraryRep& " );
	return lhs.library_name == rhs.library_name;
}

bool CommandLibraryRep::set_library_name(const std::string& name) {
	SWDEBUGP2( 5, Verify::PARSER, "CommandLibraryRep::set_library_name",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryRep::set_library_name",
                        " const std::string& " );
	library_name = name;
	return true;
}

const std::string& CommandLibraryRep::get_library_name() const {
	SWDEBUGP1( 5, Verify::PARSER, "CommandLibraryRep::get_library_name");
	SWDEBUG1( 5, Verify::TRACE, "CommandLibraryRep::get_library_name");
	return library_name;
}

void CommandLibraryRep::dump(size_t indent) {
	SWDEBUGP2( 5, Verify::PARSER, "CommandLibraryRep::dump",
                        " size_t " );
	SWDEBUG2( 5, Verify::TRACE, "CommandLibraryRep::dump",
                        " size_t " );
	std::string ind;
        indent == 0 ? ind = std::string(indent, '\t') : ind = std::string("");
        std::string ind2(indent + 1, '\t');
        std::cerr << ind << "CommandLibraryRep contents:" << std::endl;
        std::cerr << ind2 << "library_name = " << library_name << std::endl;
}

