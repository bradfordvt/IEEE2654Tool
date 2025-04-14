/*
 *    DSLCommandBus.hpp
 *
 *    Class to implement the glue between a DSL and the CommandBus
 *    architectural element.
 *
 *    Class to implement the glue between a DSL and the CommandBus
 *    architectural element.
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

#ifndef INCLUDE_DSL_DSLCOMMANDBUS_HPP_
#define INCLUDE_DSL_DSLCOMMANDBUS_HPP_

#include <stdint.h>
#include <stddef.h>

class CommandBus;

class DSLCommandBus {
public:
	DSLCommandBus();
	~DSLCommandBus();

	void setCommandBus(CommandBus *cb);
	virtual int send_command_request(const char *target, size_t len, uint8_t *message);
	virtual int send_command_response(const char *target, size_t len, uint8_t *message);

private:
	CommandBus *cb_p;
};

#endif /* INCLUDE_DSL_DSLCOMMANDBUS_HPP_ */
