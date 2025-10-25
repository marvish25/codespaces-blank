#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <regex>
typedef std::string string;

struct Details
{
    std::string ID, pref_name, password;
    Details *Next;
};

class user_manager
{

protected:
    Details *head = new Details();
    std::string temp_id, temp_pw, temp_pn, password;
    int size = 0;

    

public:
    
    
    std::string blocked_users();
    void from_file();
    void view_users();         
    void clear_console();
    void front_insert(string temp_id, string temp_pn, string password);
    void remove_user();
};

void user_manager::front_insert(string temp_id, string temp_pn, string password)
{
    Details *new_node = new Details();
    new_node->ID = temp_id;
    new_node->pref_name = temp_pn;
    new_node->password = password;
    new_node->Next = head;
    head = new_node;
}

void user_manager::remove_user()
{
    string delete_id;
    std::cout <<"enter the email to be deleted :";
    std::getline(std::cin >> std::ws ,delete_id);

    Details *current = head;
    Details *prev = nullptr;

    if (current != nullptr && current->ID == delete_id)
    {
        head = current->Next;
        delete current;
        std::cout <<delete_id <<" removed from the system!\n";
        return;
    }

    while(current != nullptr && current->ID != delete_id )
    {
        prev = current;
        current = current->Next;
    }

    if(current == NULL)
    {
        std::cout <<delete_id <<" not found!\n";
        return;
    }

    prev->Next = current->Next;
    std::cout <<delete_id << "  succesfully removed !\n";
    delete current;
}

void user_manager::from_file()
{
    head = NULL;
    std::ifstream file("storage.txt");
    while (std::getline(file >> std::ws, temp_id), std::getline(file >> std::ws, temp_pn), std::getline(file >> std::ws, password))
    {

        front_insert(temp_id, temp_pn, password);
        size++;
    
    }
}

void user_manager::view_users()
{
    std::cout << "___________________________________________________________________\n";
    std::cout << "\033[1m***********LIST OF THE USERS AVAILABLE IN THE SYSTEM***********\n\n";

    
    Details *temp = head;

    int i = 1;
    while (temp != NULL )
    {
        std::cout << "****USER " << i << " 's INFO****\n";
        std::cout << "name    :" << temp->pref_name << "\n";
        std::cout << "Email   :" << temp->ID << "\n";
        std::cout << "passw   :" << temp->password << "\n";
        std::cout << "**************************\n\n";
        temp = temp->Next;
        i++;
    }

    std::cout << "***********************************************************************\n";
}

std::string user_manager::blocked_users()
{
    return "[account blocked]\n";
}



void user_manager::clear_console()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}