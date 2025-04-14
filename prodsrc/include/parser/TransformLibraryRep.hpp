/*
 *    TransformLibraryRep.hpp
 *
 *    Class to implement the intermediate parser representation for the
 *    TransformLibrary architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    TransformLibrary architectural element.
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

#ifndef INCLUDE_PARSER_TRANSFORMLIBRARYREP_HPP_
#define INCLUDE_PARSER_TRANSFORMLIBRARYREP_HPP_

#include <string>

class TransformLibraryRep {
#ifdef TEST
	friend class TransformLibraryRep_TestCases;
#endif
public:
	TransformLibraryRep();
	TransformLibraryRep(const std::string& lib_name);
	TransformLibraryRep(const TransformLibraryRep& l);
	~TransformLibraryRep();

	TransformLibraryRep& operator=(const TransformLibraryRep& l);
	friend bool operator==(const TransformLibraryRep& lhs, const TransformLibraryRep& rhs);

	bool set_library_name(const std::string& name);
	const std::string& get_library_name() const;

	void dump(size_t indent);

private:
	std::string library_name;
};

#endif /* INCLUDE_PARSER_TRANSFORMLIBRARYREP_HPP_ */
