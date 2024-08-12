#include "personal.h"

using namespace std;

clientManager::clientManager(const std::string& connection) : connection_{ connection } { std::cout << "Подключение к базt данных установленно!" << std::endl; };

void clientManager::createDatabaseTables() // создание таблицы 
{
    
        pqxx::work t(connection_);
        t.exec("CREATE TABLE IF NOT EXISTS "  
                  "clients(id SERIAL PRIMARY KEY, "
                  "name TEXT, "
                  "surname TEXT, "
                  "email TEXT UNIQUE); "  

            "CREATE TABLE IF NOT EXISTS " 
            "phones(id SERIAL PRIMARY KEY, "
            "client_id INT REFERENCES clients(id), "
            "phone TEXT UNIQUE); " );
        t.commit();
        std::cout << "A database structure (tables) created" << std::endl;
    
}

void clientManager::addClient(const std::string& name, const std::string& surname, const std::string& email)
{
        pqxx::work t(connection_);
        pqxx::result res = t.exec_params("INSERT INTO clients (name, surname, email) " 
                                         "VALUES ($1, $2, $3) "
                                         "RETURNING id", name, surname, email);
            
        
            int client_id = res[0][0].as<int>();
            
            t.commit();

            cout << "Client added with ID: " << client_id << std::endl;
        

} 

void clientManager::addPhone(int clientId, const std::string& phone)
{

        pqxx::work t(connection_);

        t.exec_params("INSERT INTO phones "
            "(client_id, phone) "
            "VALUES ($1, $2); ", clientId, phone);
        t.commit();

        std::cout << "Phone added for client ID: " << clientId << std::endl;
  
}

void clientManager::updateClient(int clientId, int columnChoice, std::string column, std::string newValue, int number_id)
{

        pqxx::work t(connection_);

        if (column == "phone")
        {
            t.exec("UPDATE phones SET " + column + " = '" + newValue + "' WHERE id = '" + to_string(number_id) + "' AND client_id = " + to_string(clientId));
        }
        else
        {
            t.exec("UPDATE clients SET " + column + " = '" + newValue + "' WHERE id = '" + to_string(clientId) + "'");
        }
        t.commit();

        cout << "\n Информация успешно изменена! \n";

}

void clientManager::removePhone(int number_id, int clientId)
{

        pqxx::work t(connection_);

        string deleteQuery = "DELETE FROM phones "
            "WHERE id = " + to_string(number_id) + " AND client_id = " + to_string(clientId);

        t.exec(deleteQuery);

        t.commit();

        cout << "\n Номер успешно удален!" << endl;
    }



void clientManager::removeClient(int clientId)
{


        pqxx::work t(connection_);

        string deleteQuery = "DELETE FROM clients WHERE id = " + t.quote(clientId);

        t.exec(deleteQuery);

        t.commit();

        cout << "Клиент удален!" << endl;
    
}

std::vector<Client> clientManager::findClients(const std::string& name, const std::string& surname, const std::string& email, const std::string& phone, int N) 
{
    std::vector<Client> clients;

        pqxx::work t(connection_);

        if (N == 1) 
        {
            pqxx::result res = t.exec_params("SELECT c.id, c.name, c.surname, c.email, p.phone "
                "FROM clients c "
                "LEFT JOIN phones p ON c.id = p.client_id "
                "WHERE c.name = $1 AND c.surname = $2 AND c.email = $3",
                name, surname, email);

            for (const auto& row : res) 
            {
                Client client;
                client.name_ = row[1].as<std::string>();
                client.surname_ = row[2].as<std::string>();
                client.email_ = row[3].as<std::string>();
                if (!row[4].is_null())
                    client.phone_numbers_.push_back(row[4].as<std::string>());
                clients.push_back(client);
            }
        }
        else if (N == 2) 
        {

            pqxx::result res = t.exec_params("SELECT c.id, c.name, c.surname, c.email, p.phone "
                "FROM clients c "
                "JOIN phones p ON c.id = p.client_id "
                "WHERE p.phone = $1",
                phone);

            for (const auto& row : res) 
            {
                Client client;
                client.name_ = row[1].as<std::string>();
                client.surname_ = row[2].as<std::string>();
                client.email_ = row[3].as<std::string>();
                client.phone_numbers_.push_back(row[4].as<std::string>());
                clients.push_back(client);
            }


        }
        else 
        {
            std::cout << "Неверный выбор. Попробуйте еще раз.\n";
        }

        t.commit();
    

    return clients;
}

void clientManager::show()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    pqxx::work t(connection_);

    pqxx::result tables = t.exec("SELECT table_name FROM information_schema.tables WHERE table_schema='public'");

    for (auto row : tables)
    {
        std::string table_name = row[0].as<std::string>();

        std::string query = "SELECT * FROM " + table_name;
        pqxx::result data = t.exec(query);

        std::cout << "Table: " << table_name << std::endl;
        for (auto& row : data) {
            for (auto& field : row) {
                std::cout << field.c_str() << "  ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    t.commit();
    std::cout << "Done" << std::endl;
};
