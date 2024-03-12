/*
 *     DebugLibraryFactory_TestCases.hpp
 *
 *    Class to implement the  DebugLibraryFactory test cases.
 *
 *    Class to implement the DebugLibraryFactory test cases.
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

#ifndef INCLUDE_FACTORY_DEBUGLIBRARYFACTORY_TESTCASES_HPP_
#define INCLUDE_FACTORY_DEBUGLIBRARYFACTORY_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "factory/DebugLibraryFactory.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class  DebugLibraryFactory_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(  DebugLibraryFactory_TestCases );
	CPPUNIT_TEST(  DebugLibraryFactory_001 );
	CPPUNIT_TEST(  DebugLibraryFactory_002 );
	CPPUNIT_TEST(  DebugLibraryFactory_003 );
	CPPUNIT_TEST( create_handle_001);
	CPPUNIT_TEST( free_handle_001 );
	CPPUNIT_TEST( get_api_001 );
	CPPUNIT_TEST_SUITE_END();

public:
	 DebugLibraryFactory_TestCases();
	~DebugLibraryFactory_TestCases();

protected:
	DebugLibraryFactory_TestCases( const DebugLibraryFactory_TestCases& tc );
	DebugLibraryFactory_TestCases& operator=( const DebugLibraryFactory_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void DebugLibraryFactory_001();
	void DebugLibraryFactory_002();
	void DebugLibraryFactory_003();
	void create_handle_001();
	void free_handle_001();
	void get_api_001();

private:
	// Put helper functions here
};

#endif /* INCLUDE_FACTORY_DEBUGLIBRARYFACTORY_TESTCASES_HPP_ */
