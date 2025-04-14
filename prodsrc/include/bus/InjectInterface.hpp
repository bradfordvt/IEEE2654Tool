/*
 *    InjectInterface.hpp
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

#ifndef INCLUDE_BUS_INJECTINTERFACE_HPP_
#define INCLUDE_BUS_INJECTINTERFACE_HPP_

#include <stdint.h>
#include <stddef.h>
#include "model/Translator.hpp"
#include "parser/InjectInterfaceRep.hpp"

class Translator;

class InjectInterface {
public:
	InjectInterface();
	InjectInterface(const InjectInterfaceRep& cr);
	~InjectInterface();

	friend bool operator==(const InjectInterface& lhs, const InjectInterface& rhs);

	// int send_inject_request(const char* target, size_t len, uint8_t* message);
	// int handle_inject_response(const char* target, size_t len, uint8_t* message);
	int handle_inject_request(uint32_t uid, size_t len, uint8_t* message);
	int send_inject_response(uint32_t uid, size_t len, uint8_t* message);

	Translator* get_Translator();

private:
	InjectInterfaceRep irep;
};

#endif /* INCLUDE_BUS_INJECTINTERFACE_HPP_ */
