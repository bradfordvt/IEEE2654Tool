/*
 *    TestInterpreterreter.hpp
 *
 *    Class to implement the Test interpreter abstraction
 *
 *    Class to implement the Test interpreter abstraction around the
 *    different DSLs supported by the tool.  These are:
 *    - Dynamic Library Module (.so on Linux, .dll on Windows
 *    - PDL2
 *    - Python
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

#ifndef INCLUDE_DSL_TESTINTERPRETER_HPP_
#define INCLUDE_DSL_TESTINTERPRETER_HPP_

#include <string>
#include <vector>

class TestInterpreter {
public:
	TestInterpreter();
	~TestInterpreter();
	int runTest(const std::string& test_name, std::vector<std::string> argv);

private:
	int __runDynamicLibrary(const std::string& test_name, std::vector<std::string> argv);
	int __runPDL2(const std::string& test_name, std::vector<std::string> argv);
	int __runPython(const std::string& test_name, std::vector<std::string> argv);
	std::string __str_tolower(std::string s);
};

#endif /* INCLUDE_DSL_TESTINTERPRETER_HPP_ */
