/*
 *    TestInterpreter.cpp
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

static const char __authors__[] = "Bradford G. Van Treuren";
static const char __contact__[] = "bradvt59@gmail.com";
static const char __copyright__[] = "Copyright (C) 2024, Bradford G. Van Treuren";
static const char __credits__[] = "Bradford G. Van Treuren";
static const char __date__[] = "2024/09/27";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <cstdio>
#include <cctype>
#include <algorithm>
#include "dsl/TestInterpreter.hpp"
#include "dsl/PythonInterpreter.hpp"
#include <cassert>
#include "log/Logger.hpp"
#include "debug/Verify.hpp"

TestInterpreter::TestInterpreter() {
	SWDEBUGP1( 5, Verify::DSL, "TestInterpreter::TestInterpreter");
	SWDEBUG1( 5, Verify::TRACE, "TestInterpreter::TestInterpreter");
}

TestInterpreter::~TestInterpreter() {
	SWDEBUGP1( 5, Verify::DSL, "TestInterpreter::~TestInterpreter");
	SWDEBUG1( 5, Verify::TRACE, "TestInterpreter::~TestInterpreter");
}

int TestInterpreter::runTest(const std::string& test_name, std::vector<std::string> argv) {
	SWDEBUGP2( 5, Verify::DSL, "TestInterpreter::runTest",
                        " const std::string&, std::vector<std::string>" );
	SWDEBUG2( 5, Verify::TRACE, "TestInterpreter::runTest",
                        " const std::string&, std::vector<std::string>" );
	size_t dotPos = test_name.find_last_of('.');
	if(dotPos != std::string::npos) {
		std::string extension = test_name.substr(dotPos + 1);
		std::string lc_extension = __str_tolower(extension);
		if(lc_extension == "py") {
			return __runPython(test_name, argv);
		}
		else {
			std::string msg(test_name);
			msg += " does not represent a known script type.";
			Logger* logger = Logger::get_logger();
			logger->log(LOG_TYPE::ERROR, msg.c_str());
			return -1;
		}
	}
}

int TestInterpreter::__runDynamicLibrary(const std::string& test_name, std::vector<std::string> argv) {
	SWDEBUGP2( 5, Verify::DSL, "TestInterpreter::__runDynamicLibrary",
                        " const std::string&, std::vector<std::string>" );
	SWDEBUG2( 5, Verify::TRACE, "TestInterpreter::__runDynamicLibrary",
                        " const std::string&, std::vector<std::string>" );
    return 0;
}

int TestInterpreter::__runPDL2(const std::string& test_name, std::vector<std::string> argv) {
	SWDEBUGP2( 5, Verify::DSL, "TestInterpreter::__runPDL2",
                        " const std::string&, std::vector<std::string>" );
	SWDEBUG2( 5, Verify::TRACE, "TestInterpreter::__runPDL2",
                        " const std::string&, std::vector<std::string>" );
    return 0;
}

int TestInterpreter::__runPython(const std::string& test_name, std::vector<std::string> argv) {
	SWDEBUGP2( 5, Verify::DSL, "TestInterpreter::__runPython",
                        " const std::string&, std::vector<std::string>" );
	SWDEBUG2( 5, Verify::TRACE, "TestInterpreter::__runPython",
                        " const std::string&, std::vector<std::string>" );
	PythonInterpreter pyi;
	int ret = pyi.run(test_name, argv);
	return ret;
}

std::string TestInterpreter::__str_tolower(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
                // static_cast<int(*)(int)>(std::tolower)         // wrong
                // [](int c){ return std::tolower(c); }           // wrong
                // [](char c){ return std::tolower(c); }          // wrong
                   [](unsigned char c){ return std::tolower(c); } // correct
                  );
	return s;
}
