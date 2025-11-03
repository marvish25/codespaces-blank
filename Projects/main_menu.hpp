#include "user_authentication.hpp"


class menu : public user_authontication
{

public:
    void user_menu();
    void main_menu();
    void execute();
};

void menu::main_menu()
{

    std::string choice_str;
    char choice;

    do
    {
        /* code */

        std::cout << "________________________\n";
        std::cout << "\033[1m    MAIN MENU \033[0m\n";
        std::cout << "************************\n";
        std::cout << "1. Register\n";
        std::cout << "2. Log in\n";
        std::cout << "3. View users\n";
        std::cout << "4. Exit\n\n";
        std::cout << "enter choice here :";
        std::getline(std::cin >> std::ws, choice_str);
        clear_console();
        if (choice_str.length() == 1)
        {
            choice = choice_str[0];
            switch (choice)
            {
            case '1':
                sign_in();

                break;
            case '2':
                login();
                if (found)
                {
                    user_menu();
                }

                break;
            case '3':
                if(head== NULL)
                {
                    std::cout << "[ No available users in the system! ]\n";
                }
                else
                {
                    view_users();
                } 
                break;
            case '4':
                std::cout << "\033[1mTHANK YOU FOR USING MY CODE RATE IT OUT OF 10 \033[0m\n";
                break;
            default:
                std::cout << "[invalid key]\n";

                break;
            }
        }
        else
        {
            std::cout << "[please enter only (1,2,3 or 4)]\n";
        }
    } while (choice != '4');
}

void menu::user_menu()
{
    char choice;
    std::string choice_str;

    do
    {
        std::cout << "1. Remove user\n";
        std::cout << "2. Modify details\n";
        std::cout << "3. back\n";
        std::cout << "enter choice here :";
        std::getline(std::cin >> std::ws, choice_str);
        clear_console();
        if (choice_str.length() == 1)
        {
            choice = choice_str[0];
            switch (choice)
            {
            case '1':
                remove_user();
                break;
            case '2':
                std::cout << modify() <<"\n";
                break;
            case '3': 
                found = false;
                break;
            default:
                std::cout << "[invalid option!]\n";
                break;
            }
        }
        else
        {
            std::cout << "[please enter only (1,2,3 or 4)]\n";
        }
    } while (choice != '2');
}
void menu::execute()
{
    from_file();
    main_menu();
}