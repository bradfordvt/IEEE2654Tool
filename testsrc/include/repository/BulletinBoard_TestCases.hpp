/*
 *    BulletinBoard_TestCases.hpp
 *
 *    Class to implement the BulletinBoard test cases.
 *
 *    Class to implement the BulletinBoard test cases.
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

#ifndef INCLUDE_REPOSITORY_REPOSITORY_TESTCASES_HPP_
#define INCLUDE_REPOSITORY_REPOSITORY_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "repository/BulletinBoard.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class BulletinBoard_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( BulletinBoard_TestCases );
	CPPUNIT_TEST( BulletinBoard_001 );
	CPPUNIT_TEST( BulletinBoard_002 );
	CPPUNIT_TEST( BulletinBoard_003 );
	CPPUNIT_TEST( create_var_001 );
	CPPUNIT_TEST( create_var_002 );
	CPPUNIT_TEST( read_var_001 );
	CPPUNIT_TEST( read_var_002 );
	CPPUNIT_TEST( update_var_001 );
	CPPUNIT_TEST( update_var_002 );
	CPPUNIT_TEST( delete_var_001 );
	CPPUNIT_TEST( delete_var_002 );
	CPPUNIT_TEST( dump_001 );
	CPPUNIT_TEST_SUITE_END();

public:
	BulletinBoard_TestCases();
	~BulletinBoard_TestCases();

protected:
	BulletinBoard_TestCases( const BulletinBoard_TestCases& tc );
	BulletinBoard_TestCases& operator=( const BulletinBoard_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void BulletinBoard_001();
	void BulletinBoard_002();
	void BulletinBoard_003();
	void create_var_001();
	void create_var_002();
	void read_var_001();
	void read_var_002();
	void update_var_001();
	void update_var_002();
	void delete_var_001();
	void delete_var_002();
	void dump_001();

private:
	// Put helper functions here
};

#endif /* INCLUDE_REPOSITORY_REPOSITORY_TESTCASES_HPP_ */
