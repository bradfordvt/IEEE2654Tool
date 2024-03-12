/*
 *    command_library_api.h
 *
 *    API for all CommandLibrary implementations for Translators to call.
 *
 *    API for all CommandLibrary implementations for Translators to call
 *    to access the processing of commands coming from DSL interfaces to
 *    elements inside the model.
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

#ifndef COMMAND_LIBRARY_API_H_
#define COMMAND_LIBRARY_API_H_
#include "stdbool.h"
#include <stdint.h>
#include <stddef.h>
#include "api/translator_api.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct command_instance {
	uint32_t translator_uid;
	uint32_t child_uid;
	uint32_t num_children;
	uint32_t* children_uids;
	bool visible;
	enum translator_error_code error_code;
	enum translator_status status_code;
	/* char* path_name; */
	struct translator_command_api* translator_api;
	void* private_data;
} command_instance;

typedef struct command_library_api {
	int entry;              /* entry number in plug-in table */
	const char* name;       /* name of the command library */
	const char* name_space; /* namespace name for the library */
	struct command_instance* (*get_command_instance)( int translator_uid );
	int (*open)( struct command_instance* inst, struct translator_command_api* tc_api );
	int (*close)( struct command_instance* inst );
	int (*config)( struct command_instance* inst, char* json_message );
	enum translator_error_code (*get_error_code)( struct command_instance* inst );
	const char* (*get_error_string)( struct command_instance* inst );
	enum translator_status (*get_status_code)( struct command_instance* inst );
	const char* (*get_status_string)( struct command_instance* inst );
	int (*handle_command_request)( struct command_instance* inst, size_t len, uint8_t* message );
	int (*handle_inject_response)( struct command_instance* inst, size_t len, uint8_t* message );
	int (*apply)( struct command_instance* inst );
} command_library_api;

#ifdef __cplusplus
}
#endif



#endif /* COMMAND_LIBRARY_API_H_ */
