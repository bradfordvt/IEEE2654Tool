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
#include "api/inject_library_api.h"
#include "ILTestDisplay.hpp"

#include "debug/SwDebugLib.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#define MY_THIS(inst, ret) if(inst == NULL)\
	{\
		return ret;\
	}\
	ILTestDisplay* my_this = (ILTestDisplay*)(inst->private_data);\
	if(my_this == NULL)\
	{\
		inst->error_code = translator_error;\
		inst->status_code = translator_broken;\
		return ret;\
	}

#define TEST_MY_THIS() ILTestDisplay* my_this = (ILTestDisplay*)(inst->private_data);\
	if(my_this == NULL) {\
		my_this = new ILTestDisplay();\
		if(my_this == NULL) {\
			inst->error_code = translator_error;\
			inst->status_code = translator_broken;\
			return -1;\
		}\
		inst->private_data = (void*)my_this;\
	}

inject_instance* get_inject_instance( int translator_uid )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::get_inject_instance",
			" int translator_uid ");
	inject_instance* inst = (inject_instance*)malloc(sizeof(inject_instance));
	inst->translator_uid = translator_uid;
	inst->error_code = translator_success;
	inst->status_code = translator_ok;
	inst->private_data = (void*)0;
	return inst;
}

int my_open( struct inject_instance* inst, struct translator_inject_api* ti_api )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::my_open",
			" struct inject_instance*, struct translator_inject_api* ");
	TEST_MY_THIS()
	return my_this->open(inst, ti_api);
}

int my_close( struct inject_instance* inst )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::my_close",
			" struct inject_instance* ");
	MY_THIS(inst, -1)
	return my_this->close();
}

int config( struct inject_instance* inst, char* json_message )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::config",
			" struct inject_instance*, char* ");
	MY_THIS(inst, -1)
	return my_this->config(json_message);
}

int my_select( struct inject_instance* inst, uint32_t index )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::my_select",
			" struct inject_instance*, uint32_t ");
	MY_THIS(inst, -1)
	return my_this->select(index);
}

int deselect( struct inject_instance* inst, uint32_t index )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::deselect",
			" struct inject_instance*, uint32_t ");
	MY_THIS(inst, -1)
	return my_this->deselect(index);
}

bool is_selected( struct inject_instance* inst, uint32_t uid )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::is_selected",
			" struct inject_instance*, uint32_t ");
	MY_THIS(inst, false)
	return my_this->is_selected(uid);
}

enum translator_error_code get_error_code( struct inject_instance* inst )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::get_error_code",
			" struct inject_instance* ");
	MY_THIS(inst, translator_error)
	return my_this->get_error_code();
}

const char* get_error_string( struct inject_instance* inst )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::get_error_string",
			" struct inject_instance* ");
	MY_THIS(inst, "")
	return my_this->get_error_string();
}

enum translator_status get_status_code( struct inject_instance* inst )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::get_status_code",
			" struct inject_instance* ");
	MY_THIS(inst, translator_failed)
	return my_this->get_status_code();
}

const char* get_status_string( struct inject_instance* inst )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::get_status_string",
			" struct inject_instance* ");
	MY_THIS(inst, "")
	return my_this->get_status_string();
}

int handle_request( struct inject_instance* inst, size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::handle_request",
			" struct inject_instance*, size_t, uint8_t* ");
	MY_THIS(inst, -1)
	return my_this->handle_request(len, message);
}

int handle_response( struct inject_instance* inst, size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::handle_response",
			" struct inject_instance*, size_t, uint8_t* ");
	MY_THIS(inst, -1)
	return my_this->handle_response(len, message);
}

int handle_update_request( struct inject_instance* inst, size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::handle_update_request",
			" struct inject_instance*, size_t, uint8_t* ");
	MY_THIS(inst, -1)
	return my_this->handle_update_request(len, message);
}

int handle_update_response( struct inject_instance* inst, size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::handle_update_response",
			" struct inject_instance*, size_t, uint8_t* ");
	MY_THIS(inst, -1)
	return my_this->handle_update_response(len, message);
}

int handle_inject_request( struct inject_instance* inst, size_t len, uint8_t* message )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::handle_inject_request",
			" struct inject_instance*, size_t, uint8_t* ");
	MY_THIS(inst, -1)
	return my_this->handle_inject_request(len, message);
}

int apply( struct inject_instance* inst )
{
	SWDEBUG2( struct inject_instance, NULL, "ILTestDisplayWrapper::apply",
			" struct inject_instance* ");
	MY_THIS(inst, -1)
	return my_this->apply();
}

static inject_library_api ila = {
	.entry = -1,
	.name = "ILTestDisplay",
	.name_space = "Test",
	.get_inject_instance = get_inject_instance,
	.open = my_open,
	.close = my_close,
	.config = config,
	.select = my_select,
	.deselect = deselect,
	.is_selected = is_selected,
	.get_error_code = get_error_code,
	.get_error_string = get_error_string,
	.get_status_code = get_status_code,
	.get_status_string = get_status_string,
	.handle_request = handle_request,
	.handle_response = handle_response,
	.handle_update_request = handle_update_request,
	.handle_update_response = handle_update_response,
	.handle_inject_request = handle_inject_request,
	.apply = apply
};

struct inject_library_api* get_inject_library_api()
{
	SWDEBUG1( struct inject_instance, NULL, "ILTestDisplayWrapper::get_inject_library_api");
	return &ila;
}

#ifdef __cplusplus
}
#endif
