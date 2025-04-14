/*
 *    Logger.hpp
 *
 *    Class to implement the logging architectural element.
 *
 *    Class to implement the logging architectural element.
 *    The class implements the logging element of the application.
 *    This file implements the body of the Logger class.
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

#include "log/Logger.hpp"
#include <stdint.h>
#include <stddef.h>
// #include "debug/Verify.hpp"

Logger* Logger::inst = NULL;

Logger* Logger::get_logger() {
	// SWDEBUGP1( 5, Verify::LOG, "Logger::get_logger");
	// SWDEBUG1( 5, Verify::TRACE, "Logger::get_logger");
	if(Logger::inst == NULL) {
		Logger::inst = new Logger();
	}
	return Logger::inst;
}

Logger::Logger() {
	// SWDEBUGP1( 5, Verify::LOG, "Logger::Logger");
	// SWDEBUG1( 5, Verify::TRACE, "Logger::Logger");
}

Logger::~Logger() {
	// SWDEBUGP1( 5, Verify::LOG, "Logger::~Logger");
	// SWDEBUG1( 5, Verify::TRACE, "Logger::~Logger");
	std::vector<std::ostream*>::iterator it;
	for(; it != Logger::os_list.end(); ++it) {
		delete *it;
	}
}

int Logger::log(LOG_TYPE type, const char* message) {
	// SWDEBUGP2( 5, Verify::LOG, "Logger::log",
                        // " const char* " );
	// SWDEBUG2( 5, Verify::TRACE, "Logger::log",
                        // " const char* " );
	int ret = 0;
	std::vector<std::ostream*>::iterator it;
	if(type == ERROR) {
		std::cerr << "ERROR: " << message << std::endl;
	}
	else if(type == WARNING) {
		std::cerr << "WARNING: " << message << std::endl;
	}
	else if(type == DEBUG) {
		std::cerr << "DEBUG: " << message << std::endl;
	}
	else if(type == NOTICE) {
		std::cerr << "NOTICE: " << message << std::endl;
	}
	else {
		std::cerr << "UNKNOWN: " << message << std::endl;
		ret = -1;
	}
	std::cerr.flush();
	std::cout.flush();
	it = os_list.begin();
	for( ; it != Logger::os_list.end(); ++it) {
		if(type == ERROR) {
			**it << "ERROR: " << message << std::endl;
		}
		else if(type == WARNING) {
			**it << "WARNING: " << message << std::endl;
		}
		else if(type == DEBUG) {
			**it << "DEBUG: " << message << std::endl;
		}
		else if(type == NOTICE) {
			**it << "NOTICE: " << message << std::endl;
		}
		(**it).flush();
	}
	return ret;
}

void Logger::add_stream(std::ostream* os) {
	// SWDEBUGP2( 5, Verify::LOG, "Logger::add_stream",
                        // " std::ostream* " );
	// SWDEBUG2( 5, Verify::TRACE, "Logger::add_stream",
                        // " std::ostream* " );
	Logger::os_list.push_back(os);
}
