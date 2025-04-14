/*
 *    DebugLibraryRep.hpp
 *
 *    Class to implement the intermediate parser representation for the
 *    DebugLibrary architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    DebugLibrary architectural element.
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

#ifndef INCLUDE_PARSER_DEBUGLIBRARYREP_HPP_
#define INCLUDE_PARSER_DEBUGLIBRARYREP_HPP_

#include <string>

class DebugLibraryRep {
#ifdef TEST
	friend class DebugLibraryRep_TestCases;
#endif
public:
	DebugLibraryRep();
	DebugLibraryRep(const std::string& lib_name);
	DebugLibraryRep(const DebugLibraryRep& l);
	~DebugLibraryRep();

	DebugLibraryRep& operator=(const DebugLibraryRep& l);
	friend bool operator==(const DebugLibraryRep& lhs, const DebugLibraryRep& rhs);

	bool set_library_name(const std::string& name);
	const std::string& get_library_name() const;

	void dump(size_t indent);

private:
	std::string library_name;
};

#endif /* INCLUDE_PARSER_DEBUGLIBRARYREP_HPP_ */
