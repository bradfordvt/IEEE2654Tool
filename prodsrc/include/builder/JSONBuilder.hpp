
/*
 *    JSONBuilder.hpp
 *
 *    Class to implement the JSONBuilder architectural element.
 *
 *    Class to implement the JSONBuilder architectural element.
 *    The class implements the JSONBuilder element of the construction
 *    methods to build the model.
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

#ifndef INCLUDE_BUILDER_JSONBUILDER_HPP_
#define INCLUDE_BUILDER_JSONBUILDER_HPP_

#include <string>
#include <vector>
#include "log/Logger.hpp"
#include "model/Translator.hpp"
#include "builder/Builder.hpp"
#include "builder/PathManager.hpp"

class JSONBuilder: public Builder {
#ifdef TEST
	friend class JSONBuilder_TestCases;
#endif
public:
	JSONBuilder();
	~JSONBuilder();

	virtual int build_root(const std::string& module_name);

private:
	JSONBuilder(const Translator& t);
	JSONBuilder& operator=(const JSONBuilder& t);
	std::string __find_module(const std::string& module_name);
	bool __file_exists(const std::string& name);
	std::string __expand_environment_variables(const std::string &s);
	// void __path_to_vector();
        // std::vector<std::string> paths;
	PathManager* pm;
};

#endif /* INCLUDE_BUILDER_JSONBUILDER_HPP_ */
