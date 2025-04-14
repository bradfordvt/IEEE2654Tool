/*
 *    Builder.hpp
 *
 *    Class to implement the Builder interface architectural element.
 *
 *    Class to implement the Builder interface architectural element.
 *    The class implements the Builder interface of the construction
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

#ifndef INCLUDE_BUILDER_BUILDER_HPP_
#define INCLUDE_BUILDER_BUILDER_HPP_

#include <filesystem>
#include <string>
#include "log/Logger.hpp"
#include "model/Translator.hpp"

class Builder {
#ifdef TEST
	friend class Builder_TestCases;
#endif
public:
	Builder();
	~Builder();

	virtual int build_root(const std::string& model_name) = 0;
	Translator* get_root();
	void set_search_path(std::filesystem::path sd);

protected:
	int __logger(LOG_TYPE severity, const char* message);
	bool __file_exists(const std::string& name);
	void set_translator();

	Translator* root;
	std::filesystem::path search_directory;

private:
	Builder(const Translator& t);
	Builder& operator=(const Builder& t);
};

#endif /* INCLUDE_BUILDER_BUILDER_HPP_ */
