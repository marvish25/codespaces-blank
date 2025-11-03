#include "manager.hpp"

class user_authontication : public user_manager
{

    bool pass_strength = false;

    std::string strong_pw = "!@#$%&:;";

protected:
    bool found = false;

public:
    bool Email_validation(const std::string &email);
    void sign_in()
    {
        Details *temp = head;
        bool found = false;
        int count = 0;
        std::cout << "enter your prefered name :";
        std::getline(std::cin >> std::ws, temp_pn);

        // Using the regex library to validate the format of the email address
        do
        {
            std::cout << "enter your Email :";
            std::getline(std::cin >> std::ws, temp_id);
            clear_console();
            Email_validation(temp_id) ? std::cout << "[Email format verified]\n" : std::cout << "[invalid Email format!]\n";

        } while (!Email_validation(temp_id));

        while (temp != NULL)
        {
            if (temp_id == temp->ID)
            {
                std::cout << "[**account already exists!**]\n";
                found = true;
            }
            temp = temp->Next;
        }
        if (!found)
        {
            do
            {

                std::cout << "enter new password :";
                std::getline(std::cin >> std::ws, password);
                std::cout << "confirm password :";
                std::getline(std::cin >> std::ws, temp_pw);
                clear_console();
                if (password != temp_pw)
                {
                    std::cout << "[password don't match!]\n";
                }
                for (int i = 0; i < password.length(); i++)
                {
                    for (int j = 0; j < strong_pw.length(); j++)
                    {
                        if (password[i] == strong_pw[j])
                        {
                            count++;
                        }
                    }
                }
                count >= 2 ? pass_strength = true : pass_strength = false;
                if (pass_strength == false && password == temp_pw)
                {
                    std::cout << "[weak password include atleast two special characters (!@#$%&;:)]\n";
                    count = 0;
                }
            } while (password != temp_pw || pass_strength == false);

            std::ofstream file("storage.txt", std::ios::app);
            file << temp_id << "\n";
            file << temp_pn << "\n";
            file << password << "\n";
            std::cout << "[\033[1m ****ACCOUNT CREATED SUCCESSFULLY****]\n";
            temp_pw.clear();
            front_insert(temp_id, temp_pn, password);
        }
    }

    void login()
    {

        int attempts = 4;

        std::cout << "enter your Email address :";
        std::getline(std::cin >> std::ws, temp_id);
        std::cout << "enter your password   :";
        std::getline(std::cin >> std::ws, temp_pw);
        clear_console();
        Details* temp = head;
        
        while (temp != NULL)
        {

            if (temp_id == temp->ID && temp_pw == temp->password)
            {
                std::cout <<"\033[1m [Account verified]\033[0m\n";
                found = true;
                
                break;
            }

            else if (temp_id == temp->ID && temp_pw != temp->password)
            {
                std::cout << "wrong password!!\n";
                do
                {

                    std::cout << "\033[0m****you have " << attempts << " attempts left!!****\033[1m\n\n";
                    std::cout << "enter password  :";
                    std::getline(std::cin >> std::ws, temp_pw);
                    clear_console();
                    attempts--;
                    if(attempts == 0 && temp_pw != temp->password){
                        std::cout << blocked_users();
                    }
                    else if(temp_pw != temp->password){
                        std::cout << "wrong password!!\n";
                    }
                } while (attempts > 0 && temp_pw != temp->password);

                if (temp_pw == temp->password)
                {
                    std::cout <<"\033[1m [Account verrified]\033[0m\n";
                    found = true;
                }

                break;
            }
            else if (!found && temp->Next == NULL)
            {

                std::cout << "[account does not exist]\n";
            }
            temp = temp->Next;
        }
    }
};

bool user_authontication::Email_validation(const std::string &email)
{
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4})");
    return std::regex_match(email, pattern);
}