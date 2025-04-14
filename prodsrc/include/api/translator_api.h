/*
 *    translator_api.h
 *
 *    API for all plug-in library implementations to use for calling the Translators.
 *
 *    API for all plug-in library implementations to use for calling the Translators.
 *    API for plug-in library implementations to use for calling Translators.
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

#ifndef TRANSLATOR_API_H_
#define TRANSLATOR_API_H_
#include <stdint.h>
#ifdef _WIN64
#include <stdlib.h>
#else
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
struct inject_instance;
struct transform_instance;

enum translator_status
{
	translator_ok,
	translator_processing,
	translator_waiting,
	translator_broken,
	translator_failed
};

extern const char* translator_status_strings[];

enum translator_error_code
{
	translator_success,
	translator_unknown_metaname,
	translator_message_error,
	translator_host_error,
	translator_driver_error,
	translator_format_error,
	translator_not_json_format,
	translator_missing_attribute,
	translator_invalid_attribute,
	translator_missing_parameter,
	translator_invalid_parameter,
	translator_request_failed,
	translator_response_failed,
	translator_response_destination,
	translator_no_memory,
	translator_message_order,
	translator_unsupported_feature,
	translator_error
};

#if 0
enum log_severity {
	FATAL,
	ERROR,
	DEBUG,
	INFO
};
#endif
enum LOG_TYPE {
	FATAL,
	ERROR,
	WARNING,
	DEBUG,
	NOTICE
};

typedef struct translator_transform_api {
	int translator; /* index in table to the translator host for the interface */
	const char** (*get_translator_error_strings)();
	const char** (*get_translator_status_strings)();
	int (*send_request)( struct transform_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	int (*send_response)( struct transform_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	int (*logger)( struct transform_instance* inst, LOG_TYPE severity, const char* message );
	const char* (*get_path)( struct transform_instance* inst );
	int (*create_var)( const char* json_message );
	const char* (*read_var)( const char* json_message );
	int (*update_var)( const char* json_message );
	int (*delete_var)( const char* json_message );
} translator_transform_api;

typedef struct translator_debug_api {
	int translator; /* index in table to the translator host for the interface */
	const char** (*get_translator_error_strings)();
	const char** (*get_translator_status_strings)();
	int (*logger)( struct debug_instance* inst, LOG_TYPE severity, const char* message );
	const char* (*get_path)( struct debug_instance* inst );
	int (*create_var)( const char* json_message );
	const char* (*read_var)( const char* json_message );
	int (*update_var)( const char* json_message );
	int (*delete_var)( const char* json_message );
} translator_debug_api;

typedef struct translator_inject_api {
	int translator; /* index in table to the translator host for the interface */
	const char** (*get_translator_error_strings)();
	const char** (*get_translator_status_strings)();
	int (*send_request)( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	int (*update_request)( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	int (*send_update_response)( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	int (*send_inject_response)( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	int (*logger)( struct inject_instance* inst, LOG_TYPE severity, const char* message );
	const char* (*get_path)( struct inject_instance* inst );
	int (*create_var)( const char* json_message );
	const char* (*read_var)( const char* json_message );
	int (*update_var)( const char* json_message );
	int (*delete_var)( const char* json_message );
} translator_inject_api;

typedef struct translator_command_api {
	int translator; /* index in table to the translator host for the interface */
	const char** (*get_translator_error_strings)();
	const char** (*get_translator_status_strings)();
	int (*send_inject_request)( struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	int (*send_command_response)( struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message );
	int (*logger)( struct command_instance* inst, LOG_TYPE severity, const char* message );
	const char* (*get_path)( struct command_instance* inst );
	int (*create_var)( const char* json_message );
	const char* (*read_var)( const char* json_message );
	int (*update_var)( const char* json_message );
	int (*delete_var)( const char* json_message );
} translator_command_api;

#ifdef __cplusplus
}
#endif




#endif /* TRANSLATOR_API_H_ */
