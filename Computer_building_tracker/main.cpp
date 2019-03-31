#include <iostream>
#include <parts.hh>
#include <string>
#include <fstream>
#include <ostream>
#include <iterator>
#include <vector>


/* Last modified: 2.3.2019
 *
 * I created this project on my sparetime to train
 * my skills in pointers (linked lists) and classes
 * I'm also in the middle of building a new pc, so
 * in a way this could prove helpful to me as well
 *
 * This program was designed to help its user to
 * track their computer-building process.
 * The program takes an input txt-file from the user,
 * reads the data it contains and adds it to a linked
 * list for further observing. The user can decide if
 * they want to add/remove components from the list,
 * and to print out all the components and their prices.
 *  After the user is done, the program will overwrite
 * the file (if it doesn't exist, it will be created)
 * with the data, so that the progress won't be lost.
 */


// Functions
void read_file(Parts &component_list , const std::string file_name);
void rewrite_the_file(Parts &component_list, const std::string file_name);
std::vector< std::string > split(const std::string& s, const char delimiter, bool ignore_empty);

int main()
{
    Parts component_list;

    std::string file_name = "";
    std::cout << "Enter a filename: ";
    getline(std::cin, file_name);
    read_file(component_list, file_name);
    std::cout << std::endl;

    std::cout << "[ Component list of the current pc-project ]" << std::endl;
    while(true){

        std::string command;

        std::cout << "What do you want to do?" << std::endl;
        std::cout << std::endl;
        std::cout << "[1] Print out all the components" << std::endl;
        std::cout << "[2] Print out to-be-purchased components" << std::endl;
        std::cout << "[3] Mark the component as bought" << std::endl;
        std::cout << "[4] Add a component to the list" << std::endl;
        std::cout << "[5] Remove a component from the list" << std::endl;
        std::cout << "[6] Save the changes and quit" << std::endl;

        std::cout << "> ";
        std::cin >> command;

        if(command == "1"){
            std::cout << std::endl;
            component_list.print_parts();
            std::cout << std::endl;
        }
        else if(command == "2"){
            std::cout << std::endl;
            component_list.print_the_total_price();
            std::cout << std::endl;
        }
        else if(command == "3"){
            std::cout << std::endl;
            std::string component;
            std::cout << "Enter a component name: ";
            std::cin >> component;
            component_list.change_status(component);
            std::cout << std::endl;
        }

        else if(command == "4"){

            // The line has to consist of 3-4 parts.
            // Erraneous lines wont be saved to the file
            // when quitting the program!

            std::string user_input = "";
            std::cout << "Enter the data in csv-format (component;name;price): ";
            std::cin.ignore();
            getline(std::cin, user_input);

            std::vector<std::string> data_parts = split(user_input, ';',true);

            component_list.add_back(data_parts);
            std::cout << std::endl;
        }

        else if(command == "5"){
            std::cout << std::endl;
            std::string component;
            std::cout << "Enter a component name: ";
            std::cin >> component;
            component_list.remove_part(component);
            std::cout << std::endl;
        }

        else if(command == "6"){
            rewrite_the_file(component_list, file_name);
            return EXIT_SUCCESS;
        }
        else{
            std::cout << std::endl;
            std::cout << "Error! No such command. " << std::endl;
            std::cout << std::endl;
        }
    }
}

std::vector< std::string > split(const std::string& s, const char delimiter, bool ignore_empty){

    // Manual split function
    // This function splits the given string into vector elements

    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and word.empty()))
        {
            result.push_back(word);
        }

    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void read_file(Parts &component_list , const std::string file_name){

    // Read a .txt-file
    // If file cannot be found, the program will create it

    std::ifstream file(file_name);

    if(not file){
        std::cout << "Error! Couldn't find the requested file.\n"
                     "Created a new .txt-file under the name: " << file_name << std::endl;
    }
    else{
        std::string file_line;

        while(getline(file, file_line)){
            std::vector<std::string> result = split(file_line, ';', true);
            component_list.add_back(result);
        }
        file.close();
    }
}

void rewrite_the_file(Parts &component_list, const std::string file_name){

    // Rewrites/saves the given file in csv format

    std::ofstream output_file(file_name);

    std::vector<std::string> packed_data = component_list.pack_the_data();
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(packed_data.begin(), packed_data.end(), output_iterator);

    output_file.close();

}
