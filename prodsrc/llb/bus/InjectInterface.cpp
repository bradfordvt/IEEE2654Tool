/*
 *    InjectInterface
 *
 *    Class to implement the InjectInterface interface element.
 *
 *    Class to implement the InjectInterface interface element.
 *    The class implements the interface used between the InjectLibrary
 *    element and the CommandInterface via the Translator node.
 *    This file implements the body of the class.
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
static const char __date__[] = "2024/06/27";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "bus/InjectInterface.hpp"
#include "repository/Repository.hpp"
#include "debug/Verify.hpp"

InjectInterface::InjectInterface() : irep() {
	SWDEBUGP1( 5, Verify::BUS, "InjectInterface::InjectInterface");
	SWDEBUG1( 5, Verify::TRACE, "InjectInterface::InjectInterface");
}

InjectInterface::InjectInterface(const InjectInterfaceRep& cr) : irep(cr) {
	SWDEBUGP2( 5, Verify::BUS, "InjectInterface::InjectInterface",
                        " const InjectInterface& " );
	SWDEBUG2( 5, Verify::TRACE, "InjectInterface::InjectInterface",
                        " const InjectInterface& " );
}

InjectInterface::~InjectInterface() {
	SWDEBUGP1( 5, Verify::BUS, "InjectInterface::~InjectInterface");
	SWDEBUG1( 5, Verify::TRACE, "InjectInterface::~InjectInterface");
}

bool operator==(const InjectInterface& lhs, const InjectInterface& rhs) {
	SWDEBUGP1( 5, Verify::BUS, "InjectInterface::operator==");
	SWDEBUG1( 5, Verify::TRACE, "InjectInterface::operator==");
	return lhs.irep == rhs.irep;
}

int InjectInterface::handle_inject_request(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::BUS, "InjectInterface::handle_inject_request",
                        " uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectInterface::handle_inject_request",
                        " uint32_t, size_t, uint8_t* " );
	Translator* translator = get_Translator();
	if(translator != NULL) {
		return translator->handle_inject_request(uid, len, message);
	}
	else {
		return -1;
	}
}

// Between InjectLibrary sender (via Translator) and CommandLibrary handler (via Translator)
int InjectInterface::send_inject_response(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::BUS, "InjectInterface::send_inject_response",
                        " uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "InjectInterface::send_inject_response",
                        " uint32_t, size_t, uint8_t* " );
	Translator* translator = get_Translator();
	if(translator != NULL) {
		return translator->handle_inject_response(uid, len, message);
	}
	else {
		return -1;
	}
}

Translator* InjectInterface::get_Translator() {
	SWDEBUGP1( 5, Verify::BUS, "InjectInterface::get_Translator");
	SWDEBUG1( 5, Verify::TRACE, "InjectInterface::get_Translator");
	Repository* rep = Repository::get_repository();
	int t = irep.get_translator();
	Translator* translator = rep->lookup_translator(t);
	return translator;
}
