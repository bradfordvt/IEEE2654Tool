/*
 *    BulletinBoard.hpp
 *
 *    Class to implement the BulletinBoard architectural element.
 *
 *    Class to implement the BulletinBoard architectural element.
 *    The class implements the BulletinBoard of the storage
 *    methods to contain the CRUD elements.
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

#ifndef INCLUDE_REPOSITORY_BULLETINBOARD_HPP_
#define INCLUDE_REPOSITORY_BULLETINBOARD_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <map>

class BulletinBoard
{
#ifdef TEST
	friend class BulletinBoard_TestCases;
#endif
public:
	static BulletinBoard* get_bulletin_board();

	BulletinBoard();
	~BulletinBoard();

	bool purge_bulletin_board();
	int create_var(const char* json_message);
	const char* read_var(const char* json_message);
	int update_var(const char* json_message);
	int delete_var(const char* json_message);
	void dump(std::ostream& os);

private:
	BulletinBoard(const BulletinBoard& t);
	BulletinBoard& operator=(const BulletinBoard& t);
	int __create(const std::string& key, const std::string& value);
	const char* __read(const std::string& key);
	int __update(const std::string& key, const std::string& value);
	int __delete(const std::string& key);
	int __parse_message(const char* json_message);

	static BulletinBoard* bb;  // Singleton for bulletin_board
	std::map<std::string, std::string> bulletin_board;
	std::string my_key;
	std::string my_value;
};

#endif /* INCLUDE_REPOSITORY_BULLETINBOARD_HPP_ */
