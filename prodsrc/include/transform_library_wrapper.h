/*
 *    transform_library_wrapper.h
 *
 *    File to wrap TransformLibrary implementation with standard access point. 
 *
 *    File to wrap TransformLibrary implementation with standard access point.
 *    Defines the standardized get_transform_library_api( ) function as the
 *    access point into the TransformLibrary API of a plug-in library.  Each
 *    shared library plug-in exposes the API implementation by exporting
 *    the symbol get_transform_library_api referencing the API structure
 *    implemented.  In Linux (gcc), the dlsym() function is used to obtain this
 *    wrapper function from the shared library.  In Windows, the GetProcAddress()
 *    function is used to obtain this wrapper function from the shared library.
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

#ifndef TRANSFORM_LIBRARY_WRAPPER_H_
#define TRANSFORM_LIBRARY_WRAPPER_H_

#include "api/transform_library_api.h"

#ifdef __cplusplus
extern "C" {
#endif

struct transform_library_api* get_transform_library_api();

#ifdef __cplusplus
}
#endif

#endif /* TRANSFORM_LIBRARY_WRAPPER_H_ */
