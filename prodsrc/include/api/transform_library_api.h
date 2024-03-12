/*
 *    transform_library_api.h
 *
 *    API for all TransformLibrary implementations for Translators to call.
 *
 *    API for all TransformLibrary implementations for Translators to call
 *    to access the processing of requests coming from Client branches
 *    connected to the Translator in the model.
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

#ifndef TRANSFORM_LIBRARY_API_H_
#define TRANSFORM_LIBRARY_API_H_
#include "stdbool.h"
#include <stdint.h>
#include <stddef.h>
#include "api/translator_api.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct transform_instance {
	uint32_t translator_uid;
	uint32_t child_uid;
	uint32_t num_children;
	uint32_t* children_uids;
	bool visible;
	enum translator_error_code error_code;
	enum translator_status status_code;
	/* char* path_name; */
	struct translator_transform_api* translator_api;
	void* private_data;
} transform_instance;

typedef struct transform_library_api {
	int entry;              /* entry number in plug-in table */
	const char* name;       /* name of the transformation library */
	const char* name_space; /* namespace name for the library */
	struct transform_instance* (*get_transform_instance)( int translator_uid );
	int (*open)( struct transform_instance* inst, struct translator_transform_api* tt_api );
	int (*close)( struct transform_instance* inst );
	int (*config)( struct transform_instance* inst, char* json_message );
	int (*select)( struct transform_instance* inst, uint32_t index );
	int (*deselect)( struct transform_instance* inst, uint32_t index );
	bool (*is_selected)( struct transform_instance* inst, uint32_t uid );
	enum translator_error_code (*get_error_code)( struct transform_instance* inst );
	const char* (*get_error_string)( struct transform_instance* inst );
	enum translator_status (*get_status_code)( struct transform_instance* inst );
	const char* (*get_status_string)( struct transform_instance* inst );
	int (*handle_request)( struct transform_instance* inst, size_t len, uint8_t* message );
	int (*handle_response)( struct transform_instance* inst, size_t len, uint8_t* message );
	int (*apply)( struct transform_instance* inst );
} transform_library_api;

#ifdef __cplusplus
}
#endif



#endif /* TRANSFORM_LIBRARY_API_H_ */
