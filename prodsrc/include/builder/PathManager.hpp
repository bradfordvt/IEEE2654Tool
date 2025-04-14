/*
 *    PathManager.hpp
 *
 *    Class to implement the PathManager architectural element.
 *
 *    Class to implement the PathManager architectural element.
 *    The class implements the PathManager of the construction
 *    methods to build the model.  The class provides OS independent
 *    search paths for model types used by the application as well
 *    as search paths for the plug-in library extensions for the
 *    Translator nodes of the model architecture.
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

#ifndef INCLUDE_BUILDER_PATHMANAGER_HPP_
#define INCLUDE_BUILDER_PATHMANAGER_HPP_

#include <vector>
#include <string>

class PathManager {
#ifdef TEST
	friend class PathManager_TestCases;
#endif
public:
	static PathManager* get_PathManager();

	PathManager();
	~PathManager();

	const std::vector<std::string>& get_module_search_path();
	const std::vector<std::string>& get_plugin_search_path();
	const std::vector<std::string>& get_python_search_path();
	const std::string& get_path_separator();
	const std::string& get_pathvar_separator();

private:
	PathManager(const PathManager& mf);
	PathManager& operator=(const PathManager& mf);

	bool __file_exists(const std::string& name);
	std::string __expand_environment_variables(const std::string &s);
	bool __path_to_vector(const std::string& varname, const std::string& path_name);

	std::vector<std::string> module_search_path;
	std::vector<std::string> plugin_search_path;
	std::vector<std::string> python_search_path;
	std::string path_separator;
	std::string pathvar_separator;

	static PathManager *pm_p;
};

#endif /* INCLUDE_BUILDER_PATHMANAGER_HPP_ */
