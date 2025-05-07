/*
 *    Wrapper code to map  into IEEE Std 2654 C API structure.
 *
 *    Wrapper code to map  into IEEE Std 2654 C API structure.
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
static const char __date__[] = "2024/07/31";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <stdlib.h>
#include "api/command_library_api.h"
#include "CLTestDisplay.hpp"

#include "debug/SwDebugLib.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#define MY_THIS(inst, ret) if(inst == NULL)\
	{\
		return ret;\
	}\
	CLTestDisplay* my_this = (CLTestDisplay*)(inst->private_data);\
	if(my_this == NULL)\
	{\
		inst->error_code = translator_error;\
		inst->status_code = translator_broken;\
		return ret;\
	}

#define TEST_MY_THIS() CLTestDisplay* my_this = (CLTestDisplay*)(inst->private_data);\
	if(my_this == NULL) {\
		my_this = new CLTestDisplay();\
		if(my_this == NULL) {\
			inst->error_code = translator_error;\
			inst->status_code = translator_broken;\
			return -1;\
		}\
		inst->private_data = (void*)my_this;\
	}

command_instance* get_command_instance( int translator_uid )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplayWrapper::get_command_instance",
			" int translator_uid ");
	command_instance* inst = (command_instance*)malloc(sizeof(command_instance));
	inst->translator_uid = translator_uid;
	inst->error_code = translator_success;
	inst->status_code = translator_ok;
	inst->private_data = (void*)0;
	return inst;
}

int my_open( struct command_instance* inst, struct translator_command_api* tc_api )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplayWrapper::my_open",
			" struct command_instance*, struct translator_command_api* ");
	TEST_MY_THIS()
	return my_this->open(inst, tc_api);
}

int my_close( struct command_instance* inst )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplayWrapper::my_close",
			" struct command_instance* ");
	MY_THIS(inst, -1)
	return my_this->close();
}

int config( struct command_instance* inst, char* json_message )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplayWrapper::config",
			" struct command_instance*, char* ");
	MY_THIS(inst, -1)
	return my_this->config(json_message);
}

enum translator_error_code get_error_code( struct command_instance* inst )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplayWrapper::get_error_code",
			" struct command_instance* ");
	MY_THIS(inst, translator_error)
	return my_this->get_error_code();
}

const char* get_error_string( struct command_instance* inst )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplayWrapper::get_error_string",
			" struct command_instance* ");
	MY_THIS(inst, "")
	return my_this->get_error_string();
}

enum translator_status get_status_code( struct command_instance* inst )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplayWrapper::get_status_code",
			" struct command_instance* ");
	MY_THIS(inst, translator_failed)
	return my_this->get_status_code();
}

const char* get_status_string( struct command_instance* inst )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplayWrapper::get_status_string",
			" struct command_instance* ");
	MY_THIS(inst, "")
	return my_this->get_status_string();
}

int handle_command_request( struct command_instance* inst, size_t len, uint8_t* message )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplayWrapper::handle_command_request",
			" struct command_instance*, size_t, uint8_t* ");
	MY_THIS(inst, -1)
	return my_this->handle_command_request(len, message);
}

int handle_inject_response( struct command_instance* inst, size_t len, uint8_t* message )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplayWrapper::handle_inject_response",
			" struct command_instance*, size_t, uint8_t* ");
	MY_THIS(inst, -1)
	return my_this->handle_inject_response(len, message);
}

int apply( struct command_instance* inst )
{
	SWDEBUG2( struct command_instance, NULL, "CLTestDisplayWrapper::apply",
			" struct command_instance* ");
	MY_THIS(inst, -1)
	return my_this->apply();
}

static command_library_api cla = {
	.entry = -1,
	.name = "CLTestDisplay",
	.name_space = "Test",
	.get_command_instance = get_command_instance,
	.open = my_open,
	.close = my_close,
	.config = config,
	.get_error_code = get_error_code,
	.get_error_string = get_error_string,
	.get_status_code = get_status_code,
	.get_status_string = get_status_string,
	.handle_command_request = handle_command_request,
	.handle_inject_response = handle_inject_response,
	.apply = apply
};

struct command_library_api* get_command_library_api()
{
	SWDEBUG1( struct command_instance, NULL, "CLTestLeafWrapper::get_command_librry_api");
	return &cla;
}

#ifdef __cplusplus
}
#endif
