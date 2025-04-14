/*
 *    CommandInterface.hpp
 *
 *    Class to implement the CommandInterface interface element.
 *
 *    Class to implement the CommandInterface interface element.
 *    The class implements the interface used between the CommandBus
 *    element and the Translator node.
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

#ifndef INCLUDE_BUS_COMMANDINTERFACE_HPP_
#define INCLUDE_BUS_COMMANDINTERFACE_HPP_

#include <stdint.h>
#include <stddef.h>
#include "bus/CommandBus.hpp"
#include "model/Translator.hpp"
#include "parser/CommandInterfaceRep.hpp"

class CommandBus;
class Translator;

class CommandInterface {
public:
	CommandInterface();
	CommandInterface(const CommandInterfaceRep& cr);
	~CommandInterface();

	friend bool operator==(const CommandInterface& lhs, const CommandInterface& rhs);

	int send_inject_request(uint32_t uid, size_t len, uint8_t* message);
	int handle_inject_request(uint32_t uid, size_t len, uint8_t* message);
	int handle_inject_response(const char* target, size_t len, uint8_t* message);
	int handle_command_request(const char* target, size_t len, uint8_t* message);
	int send_command_response(const char* target, size_t len, uint8_t* message);

	CommandBus* get_CommandBus();
	Translator* get_Translator();

private:
	CommandInterfaceRep crep;
};


#endif /* INCLUDE_BUS_COMMANDINTERFACE_HPP_ */
