/*
 *    DebugLibraryFactory.hpp
 *
 *    Class to implement the DebugLibraryFactory architectural element.
 *
 *    Class to implement the DebugLibraryFactory architectural element.
 *    The class implements the plug-in loader for DebugLibrary instances.
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

#ifndef DEBUGLIBRARYFACTORY_HPP_
#define DEBUGLIBRARYFACTORY_HPP_

#include "api/debug_library_api.h"

struct debug_library_api;

class DebugLibraryFactory {
	public:
		void* create_handle(const char* lib_basename);
		int free_handle(void* handle);
		struct debug_library_api* get_api(void* handle);
};

#endif /* DEBUGLIBRARYFACTORY_HPP_ */
