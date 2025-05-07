/*
 *    TransformLibraryFactory.cpp
 *
 *    Class to implement the TransformLibraryFactory architectural element.
 *
 *    Class to implement the TransformLibraryFactory architectural element.
 *    The class implements the plug-in loader for TransformLibrary instances.
 *    This file implements the body of the class.
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
static const char __date__[] = "2024/02/20";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <stdlib.h>
#include <iostream>
#include <dlfcn.h>
#include "transform_library_wrapper.h"

#include "factory/TransformLibraryFactory.hpp"
#include "builder/PathManager.hpp"
#include "debug/Verify.hpp"


void* TransformLibraryFactory::create_handle(const char* lib_basename) {
	SWDEBUGP2( 5, Verify::FACTORY, "TransformLibraryFactory::create_handle",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryFactory::create_handle",
                        " const char* " );
    using std::cout;
    using std::cerr;

    // open the library
    PathManager *pm_p = PathManager::get_PathManager();
    const std::vector<std::string>& pi_path = pm_p->get_plugin_search_path();
    std::string s;
    void* handle = NULL;
    auto b = begin(pi_path);
    for( ; b != end(pi_path); b++) {
	    s = *b;
	    s += "/lib";
	    s += lib_basename;
	    s += ".so";
	    handle = dlopen(s.c_str(), RTLD_LAZY);

	    if (!handle) {
		cerr << "Cannot open library: " << dlerror() << '\n';
		continue;
	    }
    }
    if(!handle) {
	    cerr << "TransformLibraryFactory: not found!" << std::endl;
	    return NULL;
    }
    return handle;
}

int TransformLibraryFactory::free_handle(void* handle) {
	SWDEBUGP2( 5, Verify::FACTORY, "TransformLibraryFactory::free_handle",
                        " void* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryFactory::free_handle",
                        " void* " );
	if(handle)
	{
		dlclose(handle);
	}
	return 0;
}

struct transform_library_api* TransformLibraryFactory::get_api(void* handle) {
	SWDEBUGP2( 5, Verify::FACTORY, "TransformLibraryFactory::get_api",
                        " void* " );
	SWDEBUG2( 5, Verify::TRACE, "TransformLibraryFactory::get_api",
                        " void* " );
    using std::cout;
    using std::cerr;

    // load the symbol
    typedef struct transform_library_api*  (*fn)();

    // reset errors
    dlerror();
    fn f = (fn) dlsym(handle, "get_transform_library_api");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol 'get_transform_library_api': " << dlsym_error << '\n';
        dlclose(handle);
        return NULL;
    }
    struct transform_library_api* tla = (*f)();
    return tla;
}

