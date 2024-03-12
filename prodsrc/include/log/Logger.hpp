/*
 *    Logger.hpp
 *
 *    Class to implement the logging architectural element.
 *
 *    Class to implement the logging architectural element.
 *    The class implements the logging element of the application.
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

#ifndef INCLUDE_LOG_LOGGER_HPP_
#define INCLUDE_LOG_LOGGER_HPP_

#include <vector>
#include <fstream>
#include <iostream>


enum LOG_TYPE {
	ERROR,
	WARNING,
	DEBUG,
	NOTICE
};
class Logger {
private:
	static Logger* inst;

public:
	static Logger* get_logger();
	Logger();
	virtual ~Logger();

	void log(LOG_TYPE type, const char* message);
	void add_stream(std::ostream* os);

private:
	std::vector<std::ostream*> os_list;
};

#endif /* INCLUDE_LOG_LOGGER_HPP_ */
