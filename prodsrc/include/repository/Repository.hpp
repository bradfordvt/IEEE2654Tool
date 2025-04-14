/*
 *    Repository.hpp
 *
 *    Class to implement the Repository architectural element.
 *
 *    Class to implement the Repository architectural element.
 *    The class implements the Repository of the storage
 *    methods to contain the model elements.
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

#ifndef INCLUDE_REPOSITORY_REPOSITORY_HPP_
#define INCLUDE_REPOSITORY_REPOSITORY_HPP_

#include <vector>

#include "log/Logger.hpp"
#include "model/Translator.hpp"
#include "channel/IEEE2654Channel.hpp"
#include "channel/ClientAPI.hpp"
#include "channel/HostAPI.hpp"
#include "bus/CommandBus.hpp"
#include "bus/CommandInterface.hpp"
#include "bus/InjectInterface.hpp"

#include "parser/TopModuleRep.hpp"

class Repository
{
#ifdef TEST
	friend class Repository_TestCases;
#endif
public:
	static Repository* get_repository();

	Repository();
	~Repository();

	bool build_from_persistent_file(const std::string& repfile);
	bool save_to_persistent_file(const std::string& repfile);
	bool build_from_mdl_files(const std::string& top_module);
	bool purge_repository();

	Translator* set_TopModule(TopModuleRep& tmr);
	Translator* insert_Translator(TranslatorRep& tr);
	IEEE2654Channel* insert_Channel(ChannelRep& cr);
	HostAPI* insert_HostAPI(HostInterfaceRep& hr);
	ClientAPI* insert_ClientAPI(ClientInterfaceRep& cr);
	CommandInterface* insert_CommandInterface(CommandInterfaceRep& cr);
	InjectInterface* insert_InjectInterface(InjectInterfaceRep& ir);

	Translator* get_Translator(int index);
	IEEE2654Channel* get_Channel(int index);
	HostAPI* get_HostAPI(int index);
	ClientAPI* get_ClientAPI(int index);
	CommandInterface* get_CommandInterface(int index);
	InjectInterface* get_InjectInterface(int index);


	int get_index(const Translator& translator);
	int get_index(const IEEE2654Channel& channel);
	int get_index(const HostAPI& host_interface);
	int get_index(const ClientAPI& client_interface);
	int get_index(const CommandInterface& command);
	int get_index(const InjectInterface& inject_interface);

	void set_num_translators(int n);
	void set_num_channels(int n);
	void set_num_host_interfaces(int n);
	void set_num_client_interfaces(int n);
	void set_num_command_interfaces(int n);
	void set_num_inject_interfaces(int n);

	size_t get_num_translators();
	size_t get_num_channels();
	size_t get_num_host_interfaces();
	size_t get_num_client_interfaces();
	size_t get_num_command_interfaces();
	size_t get_num_inject_interfaces();
	Translator* get_TopModule();

	Translator* lookup_translator(uint32_t translator_uid);
	Translator* lookup_translator(const char* path);
        HostAPI* lookup_host(uint32_t uid);
	static Translator* find_translator_by_uid(uint32_t uid);
	static Translator* find_translator_by_path(const char* path);
	void dump(size_t indent);

private:
	Repository(const Repository& t);
	Repository& operator=(const Repository& t);

	static Repository* repository;  // Singleton for repository

	int num_translators;
	int num_channels;
	int num_host_interfaces;
	int num_client_interfaces;
	int num_command_interfaces;
	int num_inject_interfaces;

	TopModuleRep tmrep;
	std::vector<Translator*> translators;
	std::vector<uint32_t> uid_list;
	std::vector<const char*> path_list;
	std::vector<IEEE2654Channel*> channels;
	std::vector<HostAPI*> host_interfaces;
	std::vector<ClientAPI*> client_interfaces;
	std::vector<CommandInterface*> command_interfaces;
	std::vector<InjectInterface*> inject_interfaces;
};

#endif /* INCLUDE_REPOSITORY_REPOSITORY_HPP_ */
