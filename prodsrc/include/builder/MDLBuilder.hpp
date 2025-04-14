/*
 *    MDLBuilder.hpp
 *
 *    Class to implement the MDLBuilder architectural element.
 *
 *    Class to implement the MDLBuilder architectural element.
 *    The class implements the MDLBuilder element of the construction
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

#ifndef INCLUDE_BUILDER_MDLBUILDER_HPP_
#define INCLUDE_BUILDER_MDLBUILDER_HPP_

#include "log/logger.hpp"
#include "model/Translator.hpp"
#include "builder/Builder.hpp"

class MDLBuilder(Builder) {
#ifdef TEST
	friend class MDLBuilder_TestCases;
#endif
public:
	MDLBuilder();
	~MDLBuilder();

	int build_root(const char* module_name);
	Translator& get_root();

private:
	MDLBuilder(const Translator& t);
	MDLBuilder& operator=(const MDLBuilder& t);
};

#endif /* INCLUDE_BUILDER_MDLBUILDER_HPP_ */
