#include "manager.hpp"

class user_authontication : public user_manager
{

    bool pass_strength = false;

    std::string strong_pw = "!@#$%&:;";


    std::string hash_func(const std::string &plain_text) 
    {
        std::hash<std::string> hasher;
        size_t hashed_value = hasher(plain_text); // Converts string to a huge number
        return std::to_string(hashed_value);      // Returns that number as a string
    }


protected:
    bool found = false;
    Details *logged_in_user = nullptr;





public:
    bool Email_validation(const std::string &email);
    void sign_in()
    {

        Details *temp = head;
        bool found = false;
        int count = 0;
        do
        {
            if (count > 0)
            {
                std::cout << "[ email not required here ]\n";
            }

            std::cout << "enter your prefered name :";
            std::getline(std::cin >> std::ws, temp_pn);
            count++;
            clear_console();
        } while (Email_validation(temp_pn));
        count = 0;

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
                std::getline(std::cin >> std::ws, temp_pw);
                std::cout << "confirm password :";
                std::getline(std::cin >> std::ws, confirm_pw);
                clear_console();
                if (confirm_pw != temp_pw)
                {
                    std::cout << "[password don't match!]\n";
                }

                else
                {
                    for (int i = 0; i < temp_pw.length(); i++)
                    {
                        for (int j = 0; j < strong_pw.length(); j++)
                        {
                            if (temp_pw[i] == strong_pw[j])
                            {
                                count++;
                            }
                        }
                    }
                    count >= 2 ? pass_strength = true : pass_strength = false;
                }
                if (pass_strength == false && confirm_pw == temp_pw)
                {
                    std::cout << "[weak password include atleast two special characters (!@#$%&;:)]\n";
                    count = 0;
                }
            } while (confirm_pw != temp_pw || pass_strength == false);
            


            
            std::cout << "[\033[1m ****ACCOUNT CREATED SUCCESSFULLY****]\n";
            temp_pw.clear();
            std::string secure_hash = hash_func(confirm_pw);
            front_insert(temp_id, temp_pn, secure_hash);
            To_file();
        }
    }

    void login()
    {


        int attempts = 4;
        std::string input_hash;
        Details *temp = head;

        std::cout << "Enter Email address : ";
        std::getline(std::cin >>std::ws , temp_id);
        std::cout << "Enter password      : ";
        std::getline(std::cin >> std::ws , temp_pw);
        input_hash = hash_func(temp_pw);
        while (temp != NULL)
        {
            
            if(temp_id == temp->ID && input_hash == temp->password)
            {
                std::cout <<" [ Account verified ]\n";
                found = true;
                logged_in_user = temp;       
                break;
            }
            else if(temp_id == temp->ID && input_hash != temp->password )
            {
                
                
                do{
                    if( attempts == 0 ){
                        blocked_users();
                        break;
                    }
                    std::cout << "[ Incorrect password ]\n";
                    std::cout << " Re-enter password :";
                    std::getline(std::cin >> std::ws ,temp_pw);
                    input_hash = hash_func(temp_pw);
                    attempts--;
                }while(input_hash != temp->password);
                if(input_hash == temp->password){
                    std::cout <<" [ Account verified ]\n";
                    found = true;
                    logged_in_user = temp;     
                    break;
                }
                
            }
            
            
            temp = temp->Next;
        }
        if (!found)
        {
            std::cout <<" [ Account not found ]\n";
        }
    }
};

bool user_authontication::Email_validation(const std::string &email)
{
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4})");
    return std::regex_match(email, pattern);
}