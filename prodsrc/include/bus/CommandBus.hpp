/*
 *    CommandBus.hpp
 *
 *    Class to implement the CommandBus architectural element.
 *
 *    Class to implement the CommandBus architectural element.
 *    The class implements the Factory Function design pattern to
 *    create the CommandBus.  The Factory Function enforces the
 *    Singleton design pattern to ensure only one CommandBus exists
 *    in the application.  The CommandBus class provides an API for
 *    all the DSL implementations in the application to use to alter
 *    the state of the model.
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

#ifndef INCLUDE_BUS_COMMANDBUS_HPP_
#define INCLUDE_BUS_COMMANDBUS_HPP_

#include <stdint.h>
#include <stddef.h>
#include "model/Translator.hpp"

class Translator;

typedef int (*command_response_handler_callback)(const char* target, size_t len, uint8_t* message);

class CommandBus {
public:
	static CommandBus* get_command_bus();  // Factory function to enforce Singleton architecture
	CommandBus();
	virtual ~CommandBus();
	CommandBus(const CommandBus &other);
	CommandBus& operator=(const CommandBus &other);

	int send_command_request( command_response_handler_callback cb, const char* target, size_t len, uint8_t* message);
	int handle_command_request(const char* target, size_t len, uint8_t* message);
	int send_command_response(const char* target, size_t len, uint8_t* message);
	int handle_command_response(const char* target, size_t len, uint8_t* message);

private:
	static CommandBus* inst;
	Translator* __find_target(const char* target);
	command_response_handler_callback cb_p;
};

#endif /* INCLUDE_BUS_COMMANDBUS_HPP_ */
