#pragma once

#include <iostream>
#include <pqxx/pqxx>
#include <Windows.h>
#include <string>

struct Client
{
	std::string name_;
	std::string surname_;
	std::string email_;
	std::vector<std::string> phone_numbers_;
};

class clientManager
{
private:
	pqxx::connection connection_;

public:
	clientManager(const std::string& connection);

	void createDatabaseTables();
	void addClient(const std::string& name, const std::string& surname, const std::string& email);
	void addPhone(int clientId, const std::string& phone);
	void updateClient(int clientId, int columnChoice, std::string column, std::string newValue, int number_id);
	void removePhone(int number_id, int clientId);
	void removeClient(int clientId);
	std::vector<Client> findClients(const std::string& name, const std::string& surname, const std::string& email, const std::string& phone, int N);
	
	void show(); 
	
};