
/*
 *    ModuleFinder.cpp
 *
 *    Class to implement the ModuleFinder architectural element.
 *
 *    Class to implement the ModuleFinder architectural element.
 *    The class implements the ModuleFinder element of the construction
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

static const char __authors__[] = "Bradford G. Van Treuren";
static const char __contact__[] = "bradvt59@gmail.com";
static const char __copyright__[] = "Copyright (C) 2024, Bradford G. Van Treuren";
static const char __credits__[] = "Bradford G. Van Treuren";
static const char __date__[] = "2024/08/19";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <regex>
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>

#include "builder/ModuleFinder.hpp"
#include "debug/Verify.hpp"

#define JSON_MODULE_PATH "module/json"
#define MDL_MODULE_PATH "module/mdl"

ModuleFinder* ModuleFinder::mf_p = NULL;
std::string ModuleFinder::empty_string;

ModuleFinder* ModuleFinder::get_ModuleFinder() {
	SWDEBUGP1( 5, Verify::BUILDER, "ModuleFinder::get_ModuleFinder");
	SWDEBUG1( 5, Verify::TRACE, "ModuleFinder::get_ModuleFinder");
	if(mf_p == NULL) {
		mf_p = new ModuleFinder();
	}
	return mf_p;
}

ModuleFinder::ModuleFinder() {
	SWDEBUGP1( 5, Verify::BUILDER, "ModuleFinder::ModuleFinder");
	SWDEBUG1( 5, Verify::TRACE, "ModuleFinder::ModuleFinder");
       	file_to_name = {};
       	name_to_file = {};
}

ModuleFinder::~ModuleFinder() {
	SWDEBUGP1( 5, Verify::BUILDER, "ModuleFinder::~ModuleFinder");
	SWDEBUG1( 5, Verify::TRACE, "ModuleFinder::~ModuleFinder");
}

int ModuleFinder::find_modules(const std::filesystem::path& directory) {
	SWDEBUGP2( 5, Verify::BUILDER, "ModuleFinder::find_modules",
                        " const std::filesystem::path& " );
	SWDEBUG2( 5, Verify::TRACE, "ModuleFinder::find_modules",
                        " const std::filesystem::path& " );
    std::string mn;
    std::string fpath;
    DIR *di;
    // char *ptr1,*ptr2;
    char *ptr2;
    int retn;
    struct dirent *dir;
//     std::cerr << "directory = " << directory << std::endl;
    di = opendir(directory.c_str()); //specify the directory name
    if (di)
    {
        while ((dir = readdir(di)) != NULL)
        {
	    fpath = std::string(directory.c_str()) + "/" + dir->d_name;
            // ptr1=strtok(dir->d_name,".");
            strtok(dir->d_name,".");
            ptr2=strtok(NULL,".");
            if(ptr2!=NULL)
            {
                retn=strcmp(ptr2,"mdl");
                if(retn==0)
                {
// 		    std::cerr << "dir->d_name = " << dir->d_name << std::endl;
// 		    std::cerr << "fpath = " << fpath << std::endl;
		    mn = find_module(fpath.c_str());
// 		    std::cerr << "mn: " << mn << std::endl;
		    if(mn.length()) {
			    file_to_name[fpath] = mn;
			    name_to_file[mn] = fpath;
		    }
		    else {
			    std::string msg("Module file ");
			    msg += fpath;
			    msg += " is not a Module Description Language file.";
			    __logger(WARNING, msg.c_str());
		    }
                }
            }
        }
        closedir(di);
    }
//     std::cerr << "file_to_name contents:" << std::endl;
    // for(const auto pair : file_to_name) {
// 	    std::cerr << "key = " << pair.first << ", value = " << pair.second << std::endl;
    // }

//     std::cerr << "name_to_file contents:" << std::endl;
    // for(const auto pair : name_to_file) {
// 	    std::cerr << "key = " << pair.first << ", value = " << pair.second << std::endl;
    // }
    return 0;
}

const std::string& ModuleFinder::find_module(const char* module) {
	SWDEBUGP2( 5, Verify::BUILDER, "ModuleFinder::find_module",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "ModuleFinder::find_module",
                        " const char* " );
	std::string filename(module);
	static std::string mname;
	mname = __locate_module_name_in_file(filename);
// 	std::cerr << "mname: " << mname << std::endl;
	if(mname.length()) {
		return mname;
	}
	else {
		return empty_string;
	}
}

const std::string& ModuleFinder::get_module(const std::string& filename) {
	SWDEBUGP2( 5, Verify::BUILDER, "ModuleFinder::get_module",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ModuleFinder::get_module",
                        " const std::string& " );
	return file_to_name[filename];
}

const std::string& ModuleFinder::get_filename(const std::string& module) {
	SWDEBUGP2( 5, Verify::BUILDER, "ModuleFinder::get_filename",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ModuleFinder::get_filename",
                        " const std::string& " );
	return name_to_file[module];
}

int ModuleFinder::__logger( LOG_TYPE severity, const char* message ) {
	SWDEBUGP2( 5, Verify::BUILDER, "ModuleFinder::__logger",
                        " LOG_TYPE, const char* " );
	SWDEBUG2( 5, Verify::TRACE, "ModuleFinder::__logger",
                        " LOG_TYPE, const char* " );
	Logger* l_p = Logger::get_logger();
	return l_p->log(severity, message);
}

bool ModuleFinder::__file_exists(const std::string& name) {
	SWDEBUGP2( 5, Verify::BUILDER, "ModuleFinder::__file_exists",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ModuleFinder::__file_exists",
                        " const std::string& " );
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

const std::string& ModuleFinder::__locate_module_name_in_file(const std::string& filename) {
	SWDEBUGP2( 5, Verify::BUILDER, "ModuleFinder::__locate_module_name_in_file",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ModuleFinder::__locate_module_name_in_file",
                        " const std::string& " );
	static std::string module_name;
	std::ifstream ifs(filename);
	if(ifs.is_open()) {
		std::string line;
		while(std::getline(ifs, line)) {
			module_name = __locate_module_name_in_line(line);
			if(module_name.length()) {
				ifs.close();
// 				std::cerr << "module_name: " << module_name << std::endl;
				return module_name;
			}
		}
		ifs.close();
		return empty_string;
	}
	else {
		ifs.close();
		return empty_string;
	}
}

const std::string& ModuleFinder::__locate_module_name_in_line(const std::string& line) {
	SWDEBUGP2( 5, Verify::BUILDER, "ModuleFinder::__locate_module_name_in_line",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ModuleFinder::__locate_module_name_in_line",
                        " const std::string& " );
	static std::string token;
	std::string WS("[ |\t|\r|\n]+");
	auto tokens = __split(line, WS);
// 	std::cerr << "line = " << line << std::endl;
// 	std::cerr << "tokens.size() = " << tokens.size() << std::endl;
// 	std::cerr << "tokens.[0] = " << tokens[0] << std::endl;
// 	std::cerr << "tokens.[1] = " << tokens[1] << std::endl;
	if(tokens[0] == std::string("module")) {
		token = tokens[1];
		return token;
	}
	else {
		return empty_string;
	}
}

std::vector<std::string> ModuleFinder::__split(const std::string& str, const std::string& delimiters) {
	SWDEBUGP2( 5, Verify::BUILDER, "ModuleFinder::__split",
                        " const std::string&, const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "ModuleFinder::__split",
                        " const std::string&, const std::string& " );
	std::regex regexz(delimiters);
	return {std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
		std::sregex_token_iterator()};
}

