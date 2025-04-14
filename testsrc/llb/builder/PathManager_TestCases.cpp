/*
 *    PathManager_TestCases.cpp
 *
 *    Class for the PathManager test cases.
 *
 *    Class for the PathManager test cases.
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
static const char __date__[] = "2024/09/10";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <dirent.h>
#include <cstdio>
#include <cstring>
#include "stdlib.h" // for putenv()
#include "builder/PathManager.hpp"
#include "builder/PathManager_TestCases.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( PathManager_TestCases );

PathManager_TestCases::PathManager_TestCases( ) : CPPUNIT_NS::TestFixture( ) {
}

PathManager_TestCases::~PathManager_TestCases( ) {
}

PathManager_TestCases::PathManager_TestCases( const PathManager_TestCases& tc ) : CPPUNIT_NS::TestFixture( ) {
}

PathManager_TestCases& PathManager_TestCases::operator=( const PathManager_TestCases& tc ) {
	return *this;
}

void PathManager_TestCases::setUp( ) {
}

void PathManager_TestCases::tearDown( ) {
}

void PathManager_TestCases::PathManager_001() {
	char mpath[] = "IEEE2654MODULES=${HOME}/VisualStudioCode/IEEE2654Tool/examples/model/tree";
	char ppath[] = "IEEE2654PLUGINS=${HOME}/VisualStudioCode/IEEE2654Tool/bin/plugins";

	putenv(mpath);
	putenv(ppath);
	PathManager p;
#ifdef TEST
	CPPUNIT_ASSERT(p.filename.length() == 0);
#endif
}

void PathManager_TestCases::PathManager_002() {
}

void PathManager_TestCases::PathManager_003() {
}

void PathManager_TestCases::get_paths_001() {
	char mpath[] = "IEEE2654MODULES=${HOME}/VisualStudioCode/IEEE2654Tool/examples/model/tree";
	char ppath[] = "IEEE2654PLUGINS=${HOME}/VisualStudioCode/IEEE2654Tool/bin/plugins";

	putenv(mpath);
	putenv(ppath);
	PathManager pm;

	std::vector<std::string> mpath_vector;
	mpath_vector = pm.get_module_search_path();
	CPPUNIT_ASSERT(mpath_vector.size() == 1);
	std::string smpath(__expand_environment_variables(std::string(mpath)));
	smpath = smpath.substr(smpath.find('=') + 1); 
	// std::cerr << "mpath_vector[0] = " << mpath_vector[0] << std::endl;
	// std::cerr << "smpath = " << smpath << std::endl;
	CPPUNIT_ASSERT(smpath.compare(mpath_vector[0]) == 0);

	std::vector<std::string> ppath_vector;
	ppath_vector = pm.get_plugin_search_path();
	CPPUNIT_ASSERT(ppath_vector.size() == 1);
	std::string sppath(__expand_environment_variables(std::string(ppath)));
	sppath = sppath.substr(sppath.find('=') + 1); 
	// std::cerr << "ppath_vector[0] = " << ppath_vector[0] << std::endl;
	// std::cerr << "sppath = " << sppath << std::endl;
	CPPUNIT_ASSERT(sppath.compare(ppath_vector[0]) == 0);

	CPPUNIT_ASSERT(pm.get_path_separator().compare("/") == 0);
}

std::string PathManager_TestCases::__expand_environment_variables( const std::string &s ) {
        if( s.find( "${" ) == std::string::npos ) return s;

        std::string pre  = s.substr( 0, s.find( "${" ) );
        std::string post = s.substr( s.find( "${" ) + 2 );

        if( post.find( '}' ) == std::string::npos ) return s;

        std::string variable = post.substr( 0, post.find( '}' ) );
        std::string value    = "";

        post = post.substr( post.find( '}' ) + 1 );

        const char *v = getenv( variable.c_str() );
        if( v != NULL ) value = std::string( v );

        return __expand_environment_variables( pre + value + post );
}

