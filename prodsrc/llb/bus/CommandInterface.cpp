/*
 *    CommandInterface
 *
 *    Class to implement the CommandInterface interface element.
 *
 *    Class to implement the CommandInterface interface element.
 *    The class implements the interface used between the CommandBus
 *    element and the Translator node.  This file implements the
 *    body of the class.
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

#include "bus/CommandInterface.hpp"
#include "repository/Repository.hpp"
#include "debug/Verify.hpp"

CommandInterface::CommandInterface() : crep() {
	SWDEBUGP1( 5, Verify::BUS, "CommandInterface::CommandInterface");
	SWDEBUG1( 5, Verify::TRACE, "CommandInterface::CommandInterface");
}

CommandInterface::CommandInterface(const CommandInterfaceRep& cr) : crep(cr) {
	SWDEBUGP2( 5, Verify::BUS, "CommandInterface::CommandInterface",
                        " const CommandInterface& " );
	SWDEBUG2( 5, Verify::TRACE, "CommandInterface::CommandInterface",
                        " const CommandInterface& " );
	// std::cerr << "crep.get_translator() = " << crep.get_translator() << std::endl;
	// std::cerr << "crep.get_protocol() = " << crep.get_protocol() << std::endl;
	// std::cerr << "crep.get_key() = " << crep.get_key() << std::endl;
	// std::cerr << "crep.get_uid() = " << crep.get_uid() << std::endl;
	// std::cerr << "crep.get_name() = " << crep.get_name() << std::endl;
}

CommandInterface::~CommandInterface() {
	SWDEBUGP1( 5, Verify::BUS, "CommandInterface::~CommandInterface");
	SWDEBUG1( 5, Verify::TRACE, "CommandInterface::~CommandInterface");
}

bool operator==(const CommandInterface& lhs, const CommandInterface& rhs) {
	SWDEBUGP1( 5, Verify::BUS, "CommandInterface::operator==");
	SWDEBUG1( 5, Verify::TRACE, "CommandInterface::operator==");
	return lhs.crep == rhs.crep;
}

int CommandInterface::send_inject_request(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::BUS, "CommandInterface::send_inject_request",
                        " uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandInterface::send_inject_request",
                        " uint32_t, size_t, uint8_t* " );
	return handle_inject_request(uid, len, message);
}

int CommandInterface::handle_inject_request(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::BUS, "CommandInterface::handle_inject_request",
                        " uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandInterface::handle_inject_request",
                        " uint32_t, size_t, uint8_t* " );
	Translator* t_p = get_Translator();
	if(t_p != NULL) {
		return t_p->handle_inject_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int CommandInterface::handle_command_request(const char* target, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::BUS, "CommandInterface::handle_command_request",
                        " uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandInterface::handle_command_request",
                        " uint32_t, size_t, uint8_t* " );
	Translator* translator = get_Translator();
	if(translator != NULL) {
		return translator->handle_command_request(target, len, message);
	}
	else {
		return -1;
	}
}

int CommandInterface::send_command_response(const char* target, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::BUS, "CommandInterface::send_command_response",
                        " uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandInterface::send_command_response",
                        " uint32_t, size_t, uint8_t* " );
	CommandBus* cb = get_CommandBus();
	if(cb != NULL) {
		return cb->send_command_response(target, len, message);
	}
	else {
		return -1;
	}
}

CommandBus* CommandInterface::get_CommandBus() {
	SWDEBUGP1( 5, Verify::BUS, "CommandInterface::get_CommandBus");
	SWDEBUG1( 5, Verify::TRACE, "CommandInterface::get_CommandBus");
	CommandBus* cb = CommandBus::get_command_bus();
	return cb;
}

Translator* CommandInterface::get_Translator() {
	SWDEBUGP1( 5, Verify::BUS, "CommandInterface::get_Translator");
	SWDEBUG1( 5, Verify::TRACE, "CommandInterface::get_Translator");
	Repository* rep = Repository::get_repository();
	// std::cerr << "crep.get_translator() = " << crep.get_translator() << std::endl;
	// std::cerr << "crep.get_protocol() = " << crep.get_protocol() << std::endl;
	// std::cerr << "crep.get_key() = " << crep.get_key() << std::endl;
	// std::cerr << "crep.get_uid() = " << crep.get_uid() << std::endl;
	// std::cerr << "crep.get_name() = " << crep.get_name() << std::endl;
	int t = crep.get_translator();
	Translator* translator = rep->lookup_translator(t);
	return translator;
}
