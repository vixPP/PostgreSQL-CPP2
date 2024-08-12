#include "personal.h"

using namespace std;

int main()
{
    string connection_string =
        "host=localhost "
        "port=5432 "
        "dbname=personalDB "
        "user=postgres "
        "password=postgres";
    clientManager CM(connection_string);

        int num = 0;
        do 
        {

            cout << "\n Выберите действие: \n" << endl <<
                "1.Добавить нового клиента \n"
                "2.Добавить телефон для существующего клиента \n"
                "3.Изменить данные о клиенте \n"
                "4.Удалить телефон у существующего клиента \n"
                "5.Удалить существующего клиента \n"
                "6.Найти клиента по его данным — имени, фамилии, email или номер. \n"
                "7.Выход \n \n"
                "> ";
            cin >> num;


            try
            {

                CM.createDatabaseTables();

                if (num == 1)
                {
                    std::cout << "Введите имя пользователя: \n"
                        "> ";
                    string name;
                    cin >> name;

                    cout << "Введите фамилию пользователя: \n"
                        "> ";
                    string surname;
                    cin >> surname;

                    cout << "Введите email пользователя: \n"
                        "> ";
                    string email;
                    cin >> email;

                    CM.addClient(name, surname, email);
                    CM.show();
                }

                if (num == 2)
                {
                    cout << "Введите id клиента, которому требуется добавления номера \n"
                        "> ";
                    int clientID = 0;
                    cin >> clientID;

                    cout << "Введите номер, который хотите добавить \n"
                        "> ";

                    string number;
                    cin >> number;

                    CM.addPhone(clientID, number);
                    CM.show();

                }

                if (num == 3)
                {
                    cout << "Введите id клиента, которому требуется изменения: \n"
                        "> ";
                    int clientId = 0;
                    cin >> clientId;





                    cout << "Выберите, что Вы хотите изменить:\n"
                        << "1. Имя\n"
                        << "2. Фамилия\n"
                        << "3. Почта\n"
                        << "4. Номер\n> ";
                    int columnChoice = 0;
                    cin >> columnChoice;

                    int number_Id = 0;
                    string column;
                    switch (columnChoice)
                    {
                    case 1:
                        column = "name";
                        break;
                    case 2:
                        column = "surname";
                        break;
                    case 3:
                        column = "email";
                        break;
                    case 4:
                        column = "phone";
                        cout << "Введите id номера который хотите сменить: \n> ";
                        cin >> number_Id;
                        break;
                    }

                    cout << "Введите новое значение:\n> ";
                    string newValue;
                    cin >> newValue;

                    CM.updateClient(clientId, columnChoice, column, newValue, number_Id);
                    CM.show();
                }

                if (num == 4)
                {
                    int clientId = 0;
                    int number_Id = 0;

                    cout << "Введите ID клиента, у которого нужно удалить номер: \n" <<
                        "> ";
                    cin >> clientId;

                    cout << "Введите ID номера, который нужно удалить: \n> ";
                    cin >> number_Id;

                    CM.removePhone(clientId, number_Id);
                }

                if (num == 5)
                {
                    cout << "Введите ID клиента, которого хотите удалить: \n" <<
                        "> ";
                    int clientId = 0;
                    cin >> clientId;

                    CM.removeClient(clientId);
                }

                if (num == 6)
                {
                    cout << "Выберите действие: \n"
                        "1. Искать по имени, фамилии и email \n"
                        "2. Искать по номеру телефона \n"
                        "> ";

                    int N = 0;
                    cin >> N;

                    if (N == 1)
                    {

                        cout << "Введите имя: \n";
                        string SName;
                        cin >> SName;

                        cout << "Введите фамилию: \n";
                        string SSurname;
                        cin >> SSurname;

                        cout << "Введите почту: \n";
                        string Smail;
                        cin >> Smail;


                        std::vector<Client> clients = CM.findClients(SName, SSurname, Smail, "", N);

                        for (const auto& client : clients) 
                        {
                            cout << "Имя: " << client.name_ << endl;
                            cout << "Фамилия: " << client.surname_ << endl;
                            cout << "Email: " << client.email_ << endl;
                            for (const auto& phone : client.phone_numbers_) 
                            {
                                cout << "Телефон: " << phone << endl;
                            }
                            cout << endl;
                        }
                    }

                    else if (N == 2)
                    {
                        cout << "Введите номер: \n";
                        string SNumber;
                        cin >> SNumber;

                        std::vector<Client> clients = CM.findClients("", "", "", SNumber, N);

                        for (const auto& client : clients) 
                        {
                            cout << "Имя: " << client.name_ << endl;
                            cout << "Фамилия: " << client.surname_ << endl;
                            cout << "Email: " << client.email_ << endl;
                            for (const auto& phone : client.phone_numbers_)
                            {
                                cout << "Телефон: " << phone << endl;
                            }
                            cout << endl;
                        }
   
                    }

                }
            }


            catch (const std::exception& ex)
            {
                std::cout << "Exception happened: " << ex.what() << std::endl;
            }

        }
        while (num != 7);
    
};