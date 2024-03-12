/*
 *    CommandLibraryFactory_TestCases.hpp
 *
 *    Class to implement the CommandLibraryFactory test cases.
 *
 *    Class to implement the CommandLibraryFactory test cases.
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

#ifndef INCLUDE_FACTORY_COMMANDLIBRARYFACTORY_TESTCASES_HPP_
#define INCLUDE_FACTORY_COMMANDLIBRARYFACTORY_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "factory/CommandLibraryFactory.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class CommandLibraryFactory_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( CommandLibraryFactory_TestCases );
	CPPUNIT_TEST( CommandLibraryFactory_001 );
	CPPUNIT_TEST( CommandLibraryFactory_002 );
	CPPUNIT_TEST( CommandLibraryFactory_003 );
	CPPUNIT_TEST( create_handle_001);
	CPPUNIT_TEST( free_handle_001 );
	CPPUNIT_TEST( get_api_001 );
	CPPUNIT_TEST_SUITE_END();

public:
	CommandLibraryFactory_TestCases();
	~CommandLibraryFactory_TestCases();

protected:
	CommandLibraryFactory_TestCases( const CommandLibraryFactory_TestCases& tc );
	CommandLibraryFactory_TestCases& operator=( const CommandLibraryFactory_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void CommandLibraryFactory_001();
	void CommandLibraryFactory_002();
	void CommandLibraryFactory_003();
	void create_handle_001();
	void free_handle_001();
	void get_api_001();

private:
	// Put helper functions here
};

#endif /* INCLUDE_FACTORY_COMMANDLIBRARYFACTORY_TESTCASES_HPP_ */
