/*
 *    debug_library_api.h
 *
 *    API for all DebugLibrary implementations for Translators to call.
 *
 *    API for all DebugLibrary implementations for Translators to call
 *    to access the processing of messages coming to/from other libraries
 *    associated with the Translator.
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

#ifndef DEBUG_LIBRARY_API_H_
#define DEBUG_LIBRARY_API_H_
#include "stdbool.h"
#include <stdint.h>
#include "api/translator_api.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct debug_instance {
	uint32_t translator_uid;
	uint32_t child_uid;
	uint32_t num_children;
	uint32_t* children_uids;
	bool visible;
	enum translator_error_code error_code;
	enum translator_status status_code;
	/* char* path_name; */
	struct translator_debug_api* translator_api;
	void* private_data;
} debug_instance;

typedef struct debug_library_api {
	int entry;              /* entry number in plug-in table */
	const char* name;       /* name of the transformation library */
	const char* name_space; /* namespace name for the library */
	struct debug_instance* (*get_debug_instance)( int translator_uid );
	int (*open)( struct debug_instance* inst, struct translator_debug_api* td_api );
	int (*close)( struct debug_instance* inst );
	int (*config)( struct debug_instance* inst, char* json_message );
	int (*select)( struct debug_instance* inst, uint32_t index );
	int (*deselect)( struct debug_instance* inst, uint32_t index );
	bool (*is_selected)( struct debug_instance* inst, uint32_t uid );
	enum translator_error_code (*get_error_code)( struct debug_instance* inst, translator_error_code code );
	const char* (*get_error_string)( struct debug_instance* inst, translator_error_code code );
	enum translator_status (*get_status_code)( struct debug_instance* inst, translator_status code );
	const char* (*get_status_string)( struct debug_instance* inst, translator_status code );
	int (*handle_request)( struct debug_instance* inst, size_t len, uint8_t* message );
	int (*handle_response)( struct debug_instance* inst, size_t len, uint8_t* message );
	int (*handle_update_request)( struct debug_instance* inst, size_t len, uint8_t* message );
	int (*handle_update_response)( struct debug_instance* inst, size_t len, uint8_t* message );
	int (*handle_inject_request)( struct debug_instance* inst, size_t len, uint8_t* message );
	int (*handle_inject_response)( struct debug_instance* inst, size_t len, uint8_t* message );
	int (*handle_command_request)( struct debug_instance* inst, size_t len, uint8_t* message );
	int (*apply)( struct debug_instance* inst );
} debug_library_api;

#ifdef __cplusplus
}
#endif



#endif /* DEBUG_LIBRARY_API_H_ */
