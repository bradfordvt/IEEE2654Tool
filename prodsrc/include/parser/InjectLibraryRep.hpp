/*
 *    InjectLibraryRep.hpp
 *
 *    Class to implement the intermediate parser representation for the
 *    InjectLibrary architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    InjectLibrary architectural element.
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

#ifndef INCLUDE_PARSER_INJECTLIBRARYREP_HPP_
#define INCLUDE_PARSER_INJECTLIBRARYREP_HPP_

#include <string>

class InjectLibraryRep {
#ifdef TEST
	friend class InjectLibraryRep_TestCases;
#endif
public:
	InjectLibraryRep();
	InjectLibraryRep(const std::string& lib_name);
	InjectLibraryRep(const InjectLibraryRep& l);
	~InjectLibraryRep();

	InjectLibraryRep& operator=(const InjectLibraryRep& l);
	friend bool operator==(const InjectLibraryRep& lhs, const InjectLibraryRep& rhs);

	bool set_library_name(const std::string& name);
	const std::string& get_library_name() const;

	void dump(size_t indent);

private:
	std::string library_name;
};

#endif /* INCLUDE_PARSER_INJECTLIBRARYREP_HPP_ */
