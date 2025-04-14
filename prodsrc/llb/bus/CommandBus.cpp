/*
 *    CommandBus.cpp
 *
 *    Class to implement the CommandBus architectural element.
 *
 *    Class to implement the CommandBus architectural element.
 *    The class implements the Factory Function design pattern to
 *    create the CommandBus.  The Factory Function enforces the
 *    Singleton design pattern to ensure only one CommandBus exists
 *    in the application.  The CommandBus class provides an API for
 *    all the DSL implementations in the application to use to alter
 *    the state of the model.  This file implements the body of the
 *    CommandBus.
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
static const char __date__[] = "2024/02/20";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "bus/CommandBus.hpp"
#include "model/Translator.hpp"
#include "repository/Repository.hpp"
#include "dsl/DSLCommandBus.hpp"
#include "debug/Verify.hpp"

CommandBus* CommandBus::inst = NULL;

/* Set up factory method to enforce a Singleton architecture for the CommandBus */
CommandBus* CommandBus::get_command_bus() {
	SWDEBUGP1( 5, Verify::BUS, "CommandBus::get_command_bus");
	SWDEBUG1( 5, Verify::TRACE, "CommandBus::get_command_bus");
	if(CommandBus::inst == NULL) {
		CommandBus::inst = new CommandBus();
	}
	return CommandBus::inst;
}

CommandBus::CommandBus() {
	// TODO Auto-generated constructor stub
	SWDEBUGP1( 5, Verify::BUS, "CommandBus::CommandBus");
	SWDEBUG1( 5, Verify::TRACE, "CommandBus::CommandBus");

}

CommandBus::~CommandBus() {
	// TODO Auto-generated destructor stub
	SWDEBUGP1( 5, Verify::BUS, "CommandBus::~CommandBus");
	SWDEBUG1( 5, Verify::TRACE, "CommandBus::~CommandBus");
}

CommandBus::CommandBus(const CommandBus &other) {
	// TODO Auto-generated constructor stub
	SWDEBUGP2( 5, Verify::BUS, "CommandBus::CommandBus",
                        " const CommandBus&" );
	SWDEBUG2( 5, Verify::TRACE, "CommandBus::CommandBus",
                        " const CommandBus&" );

}

CommandBus& CommandBus::operator=(const CommandBus &other) {
	// TODO Auto-generated method stub
	SWDEBUGP1( 5, Verify::BUS, "CommandBus::operator=");
	SWDEBUG1( 5, Verify::TRACE, "CommandBus::operator=");
	return *this;
}

// DONE
int CommandBus::send_command_request(command_response_handler_callback cb, const char* target, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::BUS, "CommandBus::send_command_request",
                        " command_response_handler_callback, const char*, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandBus::send_command_request",
                        " command_response_handler_callback, const char*, size_t, uint8_t* " );
	cb_p = cb;
	return handle_command_request(target, len, message);
}

// DONE
int CommandBus::handle_command_request(const char* target, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::BUS, "CommandBus::handle_command_request",
                        " const char*, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandBus::handle_command_request",
                        " const char*, size_t, uint8_t* " );
	// std::cerr << "Calling CommandBus::__find_target()" << std::endl;
	Translator* t_p = __find_target(target);
	if(t_p != NULL) {
		// std::cerr << "Calling Translator::handle_command_request()" << std::endl;
		return t_p->handle_command_request(target, len, message);
	}
	// std::cerr << "Returning error from CommandBus::cwhandle_command_request__find_target()" << std::endl;
	return -1;
}

// DONE
int CommandBus::send_command_response(const char* target, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::BUS, "CommandBus::send_command_response",
                        " const char*, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandBus::send_command_response",
                        " const char*, size_t, uint8_t* " );
	return handle_command_response(target, len, message);
}

// DONE
int CommandBus::handle_command_response(const char* target, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::BUS, "CommandBus::handle_command_response",
                        " const char*, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandBus::handle_command_response",
                        " const char*, size_t, uint8_t* " );
	return cb_p(target, len, message);
}

Translator* CommandBus::__find_target(const char* target) {
	SWDEBUGP2( 5, Verify::BUS, "CommandBus::__find_target",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "CommandBus::__find_target",
                        " const char* " );
	// std::cerr << "Calling Repository::find_translator_by_path(" << target << ")" << std::endl;
	Translator* t_p = Repository::find_translator_by_path(target);
	return t_p;
}
