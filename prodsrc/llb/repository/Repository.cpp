/*
 *    Repository.cpp
 *
 *    Class to implement the Repository architectural element.
 *
 *    Class to implement the Repository architectural element.
 *    The class implements the Repository element of the modeling
 *    data representation.  It implements the representation of the
 *    IEEE2654Tree model elements.
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
static const char __date__[] = "2024/06/08";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <stdexcept>
#include <iostream>
#include <string.h>
#include <sys/stat.h>

#include "repository/Repository.hpp"
#include "parser/JSONParser.hpp"
#include "debug/Verify.hpp"

Repository* Repository::repository = NULL;

Repository* Repository::get_repository() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "Repository::get_repository");
	SWDEBUG1( 5, Verify::TRACE, "Repository::get_repository");
	if(Repository::repository == NULL) {
		Repository::repository = new Repository();
		if(Repository::repository == NULL) {
			// TODO handle error condition
		}
	}
	return Repository::repository;
}

bool Repository::purge_repository() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "Repository::purge_repository");
	SWDEBUG1( 5, Verify::TRACE, "Repository::purge_repository");
	while(!translators.empty()) {
		Translator* p = translators.back();
		translators.pop_back();
		delete p;
	}
	while(!channels.empty()) {
		IEEE2654Channel* p = channels.back();
		channels.pop_back();
		delete p;
	}
	while(!host_interfaces.empty()) {
		HostAPI* p = host_interfaces.back();
		host_interfaces.pop_back();
		delete p;
	}
	while(!client_interfaces.empty()) {
		ClientAPI* p = client_interfaces.back();
		client_interfaces.pop_back();
		delete p;
	}
	while(!command_interfaces.empty()) {
		CommandInterface* p = command_interfaces.back();
		command_interfaces.pop_back();
		delete p;
	}
	while(!inject_interfaces.empty()) {
		InjectInterface* p = inject_interfaces.back();
		inject_interfaces.pop_back();
		delete p;
	}
	return true;
}

Repository::Repository() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "Repository::Repository");
	SWDEBUG1( 5, Verify::TRACE, "Repository::Repository");
}

Repository::~Repository() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "Repository::~Repository");
	SWDEBUG1( 5, Verify::TRACE, "Repository::~Repository");
	purge_repository();
	delete Repository::repository;
}

bool Repository::build_from_persistent_file(const std::string& repfile) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::build_from_persistent_file",
			" const std::string& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::build_from_persistent_file",
			" const std::string& ");
	// Verify repfile exists
	struct stat buffer;
	if(stat(repfile.c_str(), &buffer) != 0) {
		// TODO - log error
		return false;
	}
	JSONParser jp;
	return jp.parse(repfile);
}

bool Repository::save_to_persistent_file(const std::string& repfile) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::save_to_persistent_file",
			" const std::string& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::save_to_persistent_file",
			" const std::string& ");
	return false;
}

bool Repository::build_from_mdl_files(const std::string& top_module) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::build_from_mdl_file",
			" const std::string& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::build_from_mdl_file",
			" const std::string& ");
	return false;
}

Translator* Repository::insert_Translator(TranslatorRep& tr) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::insert_Translator",
			" TranslatorRep& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::insert_Translator",
			" TranslatorRep& ");
	Translator* t = new Translator(tr);
	std::vector<Translator*>::iterator iter = translators.begin() + tr.get_key();
    	translators.insert(iter, t);
	std::vector<const char*>::iterator piter = path_list.begin() + tr.get_key();
    	path_list.insert(piter, t->get_path());
	std::vector<uint32_t>::iterator uiter = uid_list.begin() + tr.get_key();
    	uid_list.insert(uiter, t->get_uid());
	return t;
}

IEEE2654Channel* Repository::insert_Channel(ChannelRep& cr) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::insert_Channel",
			" ChannelRep& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::insert_Channel",
			" ChannelRep& ");
	IEEE2654Channel* c = new IEEE2654Channel(cr);
	std::vector<IEEE2654Channel*>::iterator iter = channels.begin() + cr.get_key();
    	channels.insert(iter, c);
	return c;
}

HostAPI* Repository::insert_HostAPI(HostInterfaceRep& hr) {
	SWDEBUGP2( 5, Verify::TRACE, "Repository::insert_HostAPI",
			" HostInterfaceRep& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::insert_HostAPI",
			" HostInterfaceRep& ");
	HostAPI* h = new HostAPI(hr);
	std::vector<HostAPI*>::iterator iter = host_interfaces.begin() + hr.get_key();
    	host_interfaces.insert(iter, h);
	return h;
}

ClientAPI* Repository::insert_ClientAPI(ClientInterfaceRep& cr) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::insert_ClientAPI",
			" ClientInterfaceRep& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::insert_ClientAPI",
			" ClientInterfaceRep& ");
	ClientAPI* c = new ClientAPI(cr);
	std::vector<ClientAPI*>::iterator iter = client_interfaces.begin() + cr.get_key();
    	client_interfaces.insert(iter, c);
	return c;
}

CommandInterface* Repository::insert_CommandInterface(CommandInterfaceRep& cr) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::insert_CommandInterface",
			" CommandInterfaceRep& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::insert_CommandInterface",
			" CommandInterfaceRep& ");
	CommandInterface* c = new CommandInterface(cr);
	std::vector<CommandInterface*>::iterator iter = command_interfaces.begin() + cr.get_key();
    	command_interfaces.insert(iter, c);
	return c;
}

InjectInterface* Repository::insert_InjectInterface(InjectInterfaceRep& ir) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::insert_InjectInterface",
			" InjectInterfaceRep& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::insert_InjectInterface",
			" InjectInterfaceRep& ");
	InjectInterface* i = new InjectInterface(ir);
	std::vector<InjectInterface*>::iterator iter = inject_interfaces.begin() + ir.get_key();
    	inject_interfaces.insert(iter, i);
	return i;
}

Translator* Repository::get_Translator(int index) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::get_Translator",
			" int ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::get_Translator",
			" int ");
	// TODO - add exception check
	// std::cerr << "index = " << index << std::endl;
	return translators.at(index);
}

IEEE2654Channel* Repository::get_Channel(int index) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::get_Channel",
			" int ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::get_Channel",
			" int ");
	// TODO - add exception check
	return channels.at(index);
}

HostAPI* Repository::get_HostAPI(int index) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::get_HostAPI",
			" int ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::get_HostAPI",
			" int ");
	// TODO - add exception check
	return host_interfaces.at(index);
}

ClientAPI* Repository::get_ClientAPI(int index) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::get_ClientAPI",
			" int ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::get_ClientAPI",
			" int ");
	// TODO - add exception check
	return client_interfaces.at(index);
}

CommandInterface* Repository::get_CommandInterface(int index) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::get_CommandInterface",
			" int ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::get_CommandInterface",
			" int ");
	// TODO - add exception check
	return command_interfaces.at(index);
}

InjectInterface* Repository::get_InjectInterface(int index) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::get_InjectInterface",
			" int ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::get_InjectInterface",
			" int ");
	// TODO - add exception check
	return inject_interfaces.at(index);
}

int Repository::get_index(const Translator& translator) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::get_index",
			" const Translator& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::get_index",
			" const Translator& ");
	std::vector<Translator*>::iterator it;
	int i = 0;
	for(it = translators.begin(); it != translators.end(); it++, i++)
	{
		if(*(*it) == translator)
		{
			return i;
		}
	}
	return -1;
}

int Repository::get_index(const IEEE2654Channel& channel) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::get_index",
			" const IEEE2654Channel& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::get_index",
			" const IEEE2654Channel& ");
	std::vector<IEEE2654Channel*>::iterator it;
	int i = 0;
	for(it = channels.begin(); it != channels.end(); it++, i++)
	{
		if(*(*it) == channel)
		{
			return i;
		}
	}
	return -1;
}

int Repository::get_index(const HostAPI& host_interface) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::get_index",
			" const HostAPI& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::get_index",
			" const HostAPI& ");
	std::vector<HostAPI*>::iterator it;
	int i = 0;
	for(it = host_interfaces.begin(); it != host_interfaces.end(); it++, i++)
	{
		if(*(*it) == host_interface)
		{
			return i;
		}
	}
	return -1;
}

int Repository::get_index(const ClientAPI& client_interface) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::get_index",
			" const ClientAPI& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::get_index",
			" const ClientAPI& ");
	std::vector<ClientAPI*>::iterator it;
	int i = 0;
	for(it = client_interfaces.begin(); it != client_interfaces.end(); it++, i++)
	{
		if(*(*it) == client_interface)
		{
			return i;
		}
	}
	return -1;
}

int Repository::get_index(const CommandInterface& command_interface) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::get_index",
			" const CommandInterface& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::get_index",
			" const CommandInterface& ");
	std::vector<CommandInterface*>::iterator it;
	int i = 0;
	for(it = command_interfaces.begin(); it != command_interfaces.end(); it++, i++)
	{
		if(*(*it) == command_interface)
		{
			return i;
		}
	}
	return -1;
}

int Repository::get_index(const InjectInterface& inject_interface) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::get_index",
			" const InjectInterface& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::get_index",
			" const InjectInterface& ");
	std::vector<InjectInterface*>::iterator it;
	int i = 0;
	for(it = inject_interfaces.begin(); it != inject_interfaces.end(); it++, i++)
	{
		if(*(*it) == inject_interface)
		{
			return i;
		}
	}
	return -1;
}

void Repository::set_num_translators(int n) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::num_translators",
			" int ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::num_translators",
			" int ");
	translators.reserve(n);
	path_list.reserve(n);
	uid_list.reserve(n);
	num_translators = n;
}

void Repository::set_num_channels(int n) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::set_num_channels",
			" int ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::set_num_channels",
			" int ");
	channels.reserve(n);
	num_channels = n;
}

void Repository::set_num_host_interfaces(int n) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::set_num_host_interfaces",
			" int ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::set_num_host_interfaces",
			" int ");
	host_interfaces.reserve(n);
	num_host_interfaces = n;
}

void Repository::set_num_client_interfaces(int n) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::set_num_client_interfaces",
			" int ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::set_num_client_interfaces",
			" int ");
	client_interfaces.reserve(n);
	num_client_interfaces = n;
}

void Repository::set_num_command_interfaces(int n) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::set_num_command_interfaces",
			" int ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::set_num_command_interfaces",
			" int ");
	command_interfaces.reserve(n);
	num_command_interfaces = n;
}

void Repository::set_num_inject_interfaces(int n) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::set_num_inject_interfaces",
			" int ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::set_num_inject_interfaces",
			" int ");
	inject_interfaces.reserve(n);
	num_inject_interfaces = n;
}

size_t Repository::get_num_translators() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "Repository::get_num_translators");
	SWDEBUG1( 5, Verify::TRACE, "Repository::get_num_translators");
	return translators.size();
}

size_t Repository::get_num_channels() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "Repository::get_num_channels");
	SWDEBUG1( 5, Verify::TRACE, "Repository::get_num_channels");
	return channels.size();
}

size_t Repository::get_num_host_interfaces() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "Repository::get_num_host_interfaces");
	SWDEBUG1( 5, Verify::TRACE, "Repository::get_num_host_interfaces");
	return host_interfaces.size();
}

size_t Repository::get_num_client_interfaces() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "Repository::get_num_client_interfaces");
	SWDEBUG1( 5, Verify::TRACE, "Repository::get_num_client_interfaces");
	return client_interfaces.size();
}

size_t Repository::get_num_command_interfaces() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "Repository::get_num_command_interfaces");
	SWDEBUG1( 5, Verify::TRACE, "Repository::get_num_command_interfaces");
	return command_interfaces.size();
}

size_t Repository::get_num_inject_interfaces() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "Repository::get_num_inject_interfaces");
	SWDEBUG1( 5, Verify::TRACE, "Repository::get_num_inject_interfaces");
	return inject_interfaces.size();
}

Translator* Repository::lookup_translator(uint32_t translator_uid) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::lookup_translator",
			" uint32_t ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::lookup_translator",
			" uint32_t ");
	// std::cerr << "translator_uid = " << translator_uid << std::endl;
        std::vector<uint32_t>::iterator i = begin(uid_list);
        std::vector<Translator*>::iterator t = begin(translators);
        for(; i != end(uid_list); ++t, ++i) {
                if(*i == translator_uid) {
                        return *t;
                }
        }
	// std::cerr << "lookup_translator is returning NULL" << std::endl;
        return NULL;
}

Translator* Repository::lookup_translator(const char* path) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::lookup_translator",
			" const char* ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::lookup_translator",
			" const char* ");
        std::vector<const char*>::iterator p = begin(path_list);
        std::vector<Translator*>::iterator t = begin(translators);
        for( ; p != end(path_list); ++p, ++t ) {
		// std::cerr << "lookup_translator: *p = " << *p << ", path = " << path << ")" << std::endl;
                if(!strcmp(*p, path)) {
                        return *t;
                }
        }
        return NULL;
}

HostAPI* Repository::lookup_host(uint32_t uid) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::lookup_host",
			" uint32_t ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::lookup_host",
			" uint32_t ");
	Translator* t_p = lookup_translator(uid);
	if(t_p) {
		ClientAPI* cl_p = t_p->get_ClientAPI();
		IEEE2654Channel* ch_p = cl_p->get_Channel();
		return ch_p->get_HostAPI();
	}
	else {
		return NULL;
	}
#if 0
        try {
                HostAPI* h_p = host_repository.at(uid);
                return h_p;
        }
        catch (const std::out_of_range& oor) {
                return NULL;
        }
#endif
}

Translator* Repository::find_translator_by_uid(uint32_t uid) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::find_translator_by_uid",
			" uint32_t ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::find_translator_by_uid",
			" uint32_t ");
	Repository* rep = Repository::get_repository();
	Translator* trans = rep->lookup_translator(uid);
	return trans;
}

Translator* Repository::find_translator_by_path(const char* path) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::find_translator_by_path",
			" const char* ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::find_translator_by_path",
			" const char* ");
	Repository* rep = Repository::get_repository();
	Translator* trans = rep->lookup_translator(path);
	return trans;
}

Translator* Repository::set_TopModule(TopModuleRep& tmr) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::set_TopModule",
			" TopModuleRep& ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::set_TopModule",
			" TopModuleRep& ");
	tmrep = tmr;
	return find_translator_by_uid(tmrep.get_translator());
}

Translator* Repository::get_TopModule() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "Repository::get_TopModule");
	SWDEBUG1( 5, Verify::TRACE, "Repository::get_TopModule");
	uint32_t translator_uid = tmrep.get_translator();
	// key in implementation is (translator_uid - 1)
	return translators[translator_uid - 1];
}

void Repository::dump(size_t indent) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "Repository::dump",
			" size_t ");
	SWDEBUG2( 5, Verify::TRACE, "Repository::dump",
			" size_t ");
	std::string ind;
        indent == 0 ? ind = std::string(indent, '\t') : ind = std::string("");
	std::string ind2(indent + 1, '\t');
	std::cerr << ind << "Repository contents:" << std::endl;
	std::cerr << ind2 << "num_translators = " << num_translators << std::endl;
	std::cerr << ind2 << "num_channels = " << num_channels << std::endl;
	std::cerr << ind2 << "num_host_interfaces = " << num_host_interfaces << std::endl;
	std::cerr << ind2 << "num_client_interfaces = " << num_client_interfaces << std::endl;
	std::cerr << ind2 << "num_command_interfaces = " << num_command_interfaces << std::endl;
	std::cerr << ind2 << "num_inject_interfaces = " << num_inject_interfaces << std::endl;
	tmrep.dump(indent + 1);
	for(auto ti : translators) {
		ti->dump(indent + 1);
	}
	std::cerr << ind2 << "uid_list = [";
	for(auto ui : uid_list) {
		std::cerr << ui << ", ";
	}
	std::cerr << "]" << std::endl;
	std::cerr << ind2 << "path_list = [";
	for(auto pi : path_list) {
		std::cerr << pi << ", ";
	}
	std::cerr << "]" << std::endl;
	std::cerr << ind2 << "channel_list = [";
	for(auto chi : channels) {
		std::cerr << chi << ", ";
	}
	std::cerr << "]" << std::endl;
	std::cerr << ind2 << "host_interfaces = [";
	for(auto hi : host_interfaces) {
		std::cerr << hi << ", ";
	}
	std::cerr << "]" << std::endl;
	std::cerr << ind2 << "client_interfaces = [";
	for(auto ci : client_interfaces) {
		std::cerr << ci << ", ";
	}
	std::cerr << "]" << std::endl;
	std::cerr << ind2 << "command_interfaces = [";
	for(auto coi : command_interfaces) {
		std::cerr << coi << ", ";
	}
	std::cerr << "]" << std::endl;
	std::cerr << ind2 << "inject_interfaces = [";
	for(auto ii : inject_interfaces) {
		std::cerr << ii << ", ";
	}
	std::cerr << "]" << std::endl;
}

#if 0
int Repository::transform_send_request( struct transform_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		t_p->mode = 0;
		ClientAPI* c_p = t_p->client_p;
		return c_p->send_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int Repository::inject_send_request( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		t_p->mode = 1;
		ClientAPI* c_p = t_p->client_p;
		return c_p->send_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int Repository::send_inject_request( struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->handle_inject_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int Repository::send_inject_response( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->handle_inject_response(uid, len, message);
	}
	else {
		return -1;
	}
}

int Repository::send_command_response( struct command_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		auto p = begin(Repository::path_list);
		auto u = begin(Repository::uid_list);
		for( ; u != end(Repository::uid_list); ++p, ++u ) {
			if(*u == inst->translator_uid) {
				return t_p->handle_command_response(*p, len, message);
			}
		}
		return -1;
	}
	else {
		return -1;
	}
}

int Repository::update_request( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		HostAPI* h_p = t_p->__lookup_host(uid);
		if(h_p !=  NULL) {
			return h_p->update_request(uid, len, message);
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

int Repository::send_response( struct transform_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		HostAPI* h_p = t_p->__lookup_host(uid);
		if(h_p !=  NULL) {
			return h_p->send_response(uid, len, message);
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

int Repository::send_update_response( struct inject_instance* inst, uint32_t uid, size_t len, uint8_t* message ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		t_p->mode = 1;
		ClientAPI* c_p = t_p->client_p;
		return c_p->send_update_response(uid, len, message);
	}
	else {
		return -1;
	}
}

int Repository::logger_transform( struct transform_instance* inst, log_severity severity, const char* message ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__logger(severity, message);
	}
	else {
		return -1;
	}
}

int Repository::logger_inject( struct inject_instance* inst, log_severity severity, const char* message ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__logger(severity, message);
	}
	else {
		return -1;
	}
}

int Repository::logger_debug( struct debug_instance* inst, log_severity severity, const char* message ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__logger(severity, message);
	}
	else {
		return -1;
	}
}

int Repository::logger_command( struct command_instance* inst, log_severity severity, const char* message ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__logger(severity, message);
	}
	else {
		return -1;
	}
}

const char* Repository::__get_path() {
	auto u = begin(Repository::uid_list);
	auto p = begin(Repository::path_list);
	for( ; u != end(Repository::uid_list); ++p, ++u ) {
		if(*u == t_uid) {
			return *p;
		}
	}
	return NULL;
}

const char* Repository::get_transform_path( struct transform_instance* inst ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__get_path();
	}
	else {
		return NULL;
	}
}

const char* Repository::get_debug_path( struct debug_instance* inst ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__get_path();
	}
	else {
		return NULL;
	}
}

const char* Repository::get_inject_path( struct inject_instance* inst ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__get_path();
	}
	else {
		return NULL;
	}
}

const char* Repository::get_command_path( struct command_instance* inst ) {
	Repository* t_p = __lookup_translator(inst->translator_uid);
	if(t_p != NULL) {
		return t_p->__get_path();
	}
	else {
		return NULL;
	}
}

int Repository::create_var( const char* json_message ) {
	return 0;
}

const char* Repository::read_var( const char* json_message ) {
	return "";
}

int Repository::update_var( const char* json_message ) {
	return 0;
}

int Repository::delete_var( const char* json_message ) {
	return 0;
}

int Repository::handle_request( uint32_t uid, size_t len, uint8_t* message ) {
	return tla->handle_request(t_inst, len, message);
}

int Repository::handle_inject_request( uint32_t uid, size_t len, uint8_t* message ) {
	return ila->handle_inject_request(i_inst, len, message);
}

int Repository::handle_update_request( uint32_t uid, size_t len, uint8_t* message ) {
	return ila->handle_update_request(i_inst, len, message);
}

int Repository::handle_response( uint32_t uid, size_t len, uint8_t* message ) {
	if(mode == 0) {
		return tla->handle_response(t_inst, len, message);
	}
	else if(mode == 1) {
		return ila->handle_response(i_inst, len, message);
	}
	else {
		return -1;
	}
}

int Repository::handle_update_response( uint32_t uid, size_t len, uint8_t* message ) {
	return ila->handle_update_response(i_inst, len, message);
}

int Repository::handle_inject_response( uint32_t uid, size_t len, uint8_t* message ) {
	return cla->handle_inject_response(c_inst, len, message);
}

int Repository::handle_command_response( const char* target, size_t len, uint8_t* message ) {
	cmd_bus = CommandBus::get_command_bus();
	return cmd_bus->handle_command_response(target, len, message);
}

Repository* Repository::__lookup_translator(uint32_t translator_uid) {
	auto i = begin(uid_list);
	auto t = begin(translator_list);
	for(; i != end(uid_list); ++t, ++i) {
		if(*i == translator_uid) {
			return *t;
		}
	}
	return NULL;
}

HostAPI* Repository::__lookup_host(uint32_t uid) {
	try {
		HostAPI* h_p = host_repository.at(uid);
		return h_p;
	}
	catch (const std::out_of_range& oor) {
		return NULL;
	}
}

int Repository::__logger( log_severity severity, const char* message ) {
	if(severity == FATAL) {
		std::cerr << "FATAL: " << message;
		return 0;
	}
	else if(severity == ERROR) {
		std::cerr << "ERROR: " << message;
		return 0;
	}
	else if(severity == DEBUG) {
		std::cout << "DEBUG: " << message;
		return 0;
	}
	else if(severity == INFO) {
		std::cout << "INFO: " << message;
		return 0;
	}
	else {
		std::cerr << "UNKNOWN: " << message;
		return -1;
	}
}
#endif
