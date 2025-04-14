/*
 *    ModuleFinder_TestCases.hpp
 *
 *    Class to implement the ModuleFinder test cases.
 *
 *    Class to implement the ModuleFinder test cases.
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

#ifndef INCLUDE_BUILDER_MODULEFINDER_TESTCASES_HPP_
#define INCLUDE_BUILDER_MODULEFINDER_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "builder/ModuleFinder.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class ModuleFinder_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( ModuleFinder_TestCases );
	CPPUNIT_TEST( ModuleFinder_001 );
	CPPUNIT_TEST( ModuleFinder_002 );
	CPPUNIT_TEST( ModuleFinder_003 );
	CPPUNIT_TEST( find_modules_001 );
	CPPUNIT_TEST( find_module_001 );
	CPPUNIT_TEST( find_module_002 );
	CPPUNIT_TEST( find_module_003 );
	CPPUNIT_TEST( find_module_004 );
	CPPUNIT_TEST( find_module_005 );
	CPPUNIT_TEST_SUITE_END();

public:
	ModuleFinder_TestCases();
	~ModuleFinder_TestCases();

protected:
	ModuleFinder_TestCases( const ModuleFinder_TestCases& tc );
	ModuleFinder_TestCases& operator=( const ModuleFinder_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void ModuleFinder_001();
	void ModuleFinder_002();
	void ModuleFinder_003();
	void find_modules_001();
	void find_module_001();
	void find_module_002();
	void find_module_003();
	void find_module_004();
	void find_module_005();

private:
	// Put helper functions here
};

#endif /* INCLUDE_BUILDER_MODULEFINDER_TESTCASES_HPP_ */
