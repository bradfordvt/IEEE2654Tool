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
static const char __date__[] = "2024/03/23";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <stdlib.h>
#include "api/transform_library_api.h"
#include "TLTestLeaf.hpp"
#include <iostream>

#include "debug/SwDebugLib.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#if 1
#define MY_THIS(inst, ret) if(inst == NULL)\
	{\
		return ret;\
	}\
	TLTestLeaf* my_this = (TLTestLeaf*)(inst->private_data);\
	if(my_this == NULL)\
	{\
		inst->error_code = translator_error;\
		inst->status_code = translator_broken;\
		return ret;\
	}
#else
#define MY_THIS(inst) TLTestLeaf* my_this = (TLTestLeaf*)(inst->private_data);
#endif

#define TEST_MY_THIS() TLTestLeaf* my_this = (TLTestLeaf*)(inst->private_data);\
	if(my_this == NULL)\
	{\
		my_this = new TLTestLeaf();\
		if(my_this == NULL)\
		{\
			inst->error_code = translator_error;\
			inst->status_code = translator_broken;\
			return -1;\
		}\
		inst->private_data = (void*)my_this;\
	}

transform_instance* get_transform_instance( int translator_uid )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestLeafWrapper::get_command_instance",
			" int translator_uid ");
	transform_instance* inst = (transform_instance*)malloc(sizeof(transform_instance));
	inst->translator_uid = translator_uid;
	inst->error_code = translator_success;
	inst->status_code = translator_ok;
	inst->private_data = (void*)0;
	return inst;
}

int my_open( struct transform_instance* inst, struct translator_transform_api* tt_api )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestLeafWrapper::my_open",
			" struct transform_instance*, struct translator_transform_api* ");
	TEST_MY_THIS()
	return my_this->open(inst, tt_api);
}

int my_close( struct transform_instance* inst )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestLeafWrapper::my_close",
			" struct transform_instance* ");
	MY_THIS(inst, -1);
	return my_this->close();
}

int config( struct transform_instance* inst, char* json_message )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestLeafWrapper::config",
			" struct transform_instance*, char* ");
	MY_THIS(inst, -1);
	return my_this->config(json_message);
}

// Use my_select name as select() overloads select for stdlib declaration.
int my_select( struct transform_instance* inst, uint32_t index )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestLeafWrapper::my_select",
			" struct transform_instance*, uint32_t ");
	MY_THIS(inst, -1);
	return my_this->select(index);
}

int deselect( struct transform_instance* inst, uint32_t index )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestLeafWrapper::deselect",
			" struct transform_instance*, uint32_t ");
	MY_THIS(inst, -1);
	return my_this->deselect(index);
}

bool is_selected( struct transform_instance* inst, uint32_t uid )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestLeafWrapper::is_selected",
			" struct transform_instance*, uint32_t ");
	MY_THIS(inst, false);
	return my_this->is_selected(uid);
}

enum translator_error_code get_error_code( struct transform_instance* inst )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestLeafWrapper::get_error_code",
			" struct transform_instance* ");
	MY_THIS(inst, translator_error);
	return my_this->get_error_code();
}

const char* get_error_string( struct transform_instance* inst )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestLeafWrapper::get_error_string",
			" struct transform_instance* ");
	MY_THIS(inst, "");
	return my_this->get_error_string();
}

enum translator_status get_status_code( struct transform_instance* inst )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestLeafWrapper::get_status_code",
			" struct transform_instance* ");
	MY_THIS(inst, translator_failed);
	return my_this->get_status_code();
}

const char* get_status_string( struct transform_instance* inst )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestLeafWrapper::get_status_string",
			" struct transform_instance* ");
	MY_THIS(inst, "");
	return my_this->get_status_string();
}

int handle_request( struct transform_instance* inst, size_t len, uint8_t* message )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestLeafWrapper::handle_request",
			" struct transform_instance*, size_t, uint8_t* ");
	MY_THIS(inst, -1);
	return my_this->handle_request(len, message);
}

int handle_response( struct transform_instance* inst, size_t len, uint8_t* message )
{
	SWDEBUG2( struct transform_instance, NULL, "TLTestLeafWrapper::handle_response",
			" struct transform_instance*, size_t, uint8_t* ");
	MY_THIS(inst, -1);
	return my_this->handle_response(len, message);
}

int apply( struct transform_instance* inst )
{
	SWDEBUG2( struct transform_instance, NULL, "CLTestLeafWrapper::apply",
			" struct transform_instance* ");
	MY_THIS(inst, -1);
	return my_this->apply();
}

static transform_library_api tla = {
	.entry = -1,
	.name = "TLTestLeaf",
	.name_space = "Test",
	.get_transform_instance = get_transform_instance,
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
	.apply = apply
};

struct transform_library_api* get_transform_library_api()
{
	SWDEBUG1( struct transform_instance, NULL, "CLTestLeafWrapper::get_transform_library_api");
	return &tla;
}

#ifdef __cplusplus
}
#endif
