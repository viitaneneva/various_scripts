/*

    This is a schoolproject i made some time ago.
    A program that builds a simple database of
    libraries and the books they have. Includes
    a basic user interface.

    Requires a csv-file to run properly. Each line
    of the file has to consist of four parts:
    Libraryname;Author;Bookname;LoanQueueTime
*/


#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm> // used: erase

struct Book {

    std::string title;
    std::string author;
    int reservations;

};

bool operator < (const Book& book_1, const Book& book_2)
// Compares two Book-items and their members

{
    if(book_1.author < book_2.author){
        return book_1.author < book_2.author;}
    else if(book_1.author == book_2.author){
        return (book_1.title < book_2.title);}
    else{
        return book_1.author < book_2.author;}
}

std::vector<std::string> split(const std::string& line_of_text,
                               const char delimiter, bool ignore_empty = false){

// Splits a line of string into parts and stores them in a vector.

    std::vector<std::string> result;
    std::string temp = line_of_text;

    while(temp.find(delimiter) != std::string::npos)
    {
        std::string new_part = temp.substr(0, temp.find(delimiter));
        temp = temp.substr(temp.find(delimiter)+1, temp.size());
        if(not (ignore_empty and new_part.empty())){
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and temp.empty()))
    {
        result.push_back(temp);
    }
    return result;
}

void shortest_reservation_time(std::string book_name, std::map<std::string,
                               std::map<std::string, std::vector<Book>>>& data_base){

/* Finds the shortest reservation time for the wanted book.
   If the book has same reservation time in different libraries,
   function prints out all of them

   :param book_name = Name of the book we're examining here
   :param data_base = The main datastructure
   :return: = none                                                      */

    std::vector<std::string> shortest_loan_times = {}; // elements = library names
    int shortest_loan_time = 100;
    bool library_book = false; // flag to check if the book is a librarybook

    for ( auto library : data_base){
        for ( auto author : library.second){
            for ( auto book: author.second){

                if (book.title == book_name){
                        library_book = true; // Book was found in a library

                        // If this is the first found book, set the books
                        // reservations as the current shortest one
                        if (shortest_loan_times.size() == 0){
                            shortest_loan_time = book.reservations;
                            shortest_loan_times.push_back(library.first);}

                        else{
                            // If this books reservation time is smaller than the
                            // current shortest, clear the vector and reset
                            // shortest_loan_time
                            if ( book.reservations < shortest_loan_time){
                                shortest_loan_times.clear();
                                shortest_loan_times.push_back(library.first);
                                shortest_loan_time = book.reservations;}

                            // If the books reservation time is the same as the
                            // current shortest, add the library to the vector.
                            else if ( book.reservations == shortest_loan_time){
                                shortest_loan_times.push_back(library.first);}}

    }}}}

    // After looping through every library, the program checks if the shortest
    // loan time is under the reservation cap (100) and prints out the
    // information accordingly.
    if ( library_book == true){
        if (shortest_loan_time < 100){

            if (shortest_loan_time == 0){
                std::cout << "on the shelf" << std::endl;}
            else{
                std::cout << shortest_loan_time << " reservations" << std::endl;}

            for( auto library : shortest_loan_times ){
                std::cout << "--- " << library << std::endl;}
        }
        else{
             std::cout << "The book is not reservable from any library." << std::endl;}
    }

    else{
         std::cout << "Book is not a library book." << std::endl;}

}


void print_out_library_material(std::string library_name,std::map<std::string,
                                std::map<std::string, std::vector<Book>>>& data_base){

/*  Prints out all the books in a certain library. This isn't necessarily a
    useful function, but the main-function was getting a little too crowded

    :param library_name = Name of the library we're examining here
    :param data_base = The main datastructure
    :return: = none                                                      */

    for( auto author : data_base[library_name]){
        for ( auto book : author.second){
            std::cout << book.author << ": " << book.title << std::endl;
    }}
}

void print_out_loanable_books(std::map<std::string, std::map<std::string,
                              std::vector<Book>>>& data_base){

/*  Prints out all the books available for loaning

    :param data_base = The main datastructure
    :return: = none                               */

    // Temporary vector for storing the loanable books
    std::vector<Book> loanable_books;

    for ( auto library : data_base){
        for ( auto author : library.second){
            for ( auto book: author.second){
                if ( book.reservations == 0){
                    loanable_books.push_back(book);

    }}}}

    // Sort the vector alphabetically and print out its elements
    // Note that the sort uses the 'operation <'-function that
    // has been declared on line 31
    std::sort(loanable_books.begin(), loanable_books.end());
    for (auto book : loanable_books){
        std::cout << book.author << ": " << book.title << std::endl;
    }

}

void print_out_book_names(std::string library_name, std::string book_author,
                          std::map<std::string, std::map<std::string,
                          std::vector<Book>>>& data_base){

/* Print out all the books (by a certain author) and their number of reservations
   in a certain library. If there are no reservations, the book is "on the shelf."

   :param library_name = Name of the library we're examining here
   :param book_author = Name of the author whose books we're printing here
   :param data_base = The main datastructure
   :return: = none                                                              */

    for( auto book : data_base[library_name][book_author]){

        if ( book.reservations > 0){
           std::cout << book.title << " --- " <<book.reservations
                     << " reservations" << std::endl;}

        else{
           std::cout << book.title << " --- " << "on the shelf" << std::endl;}

    }
}

bool read_a_line(std::string line, std::map<std::string,
                 std::map<std::string, std::vector<Book>>>& data_base ){

/* This function reads the contents of a csv-file line, and stores the information
   from it to the main datastructure. The line has to contain four items separated
   by ';'-character, and none of these items can be a blank. Otherwise the program
   will give an error message and the program execution is terminated.

    :param line = a csv-file line that contains 4 parts separated by ';'
    :param data_base = The main datastructure
    :return: = returns 'true' if the line-reading was successful                */

    std::vector<std::string> line_parts = split(line, ';', true);

    if (line_parts.size() == 4){

        for (auto parts : line_parts){
            if(isspace(parts[0]))
                return false;
        }

        if (line_parts[3] == "on-the-shelf")
            line_parts[3] = "0";

        std::string library = line_parts[0];
        std::string book_author = line_parts[1];
        std::string book_name = line_parts[2];
        int reservations = stoi(line_parts[3]);

        // Define a structure variable from the information
        Book book = {book_name, book_author, reservations};
        std::vector<Book> books = {book};

        // If the library name can be found from the database..
        if (data_base.find(library) != data_base.end()){

            // If the author's name can be found from the library's archives
            if (data_base[library].find(book_author) != data_base[library].end())

                // Let's check that there's no book with the same title as the one
                // we are currently working with.
                for (unsigned int i = 0; i < data_base[library][book_author].size(); i++){

                    // If there is a book with the same title, replace it with the
                    // one we are currently working with, otherwise just add the
                    // Book-item to the vector.
                    if (data_base[library][book_author][i].title == book.title){
                        data_base[library][book_author][i] = book;
                    }
                    else{
                        data_base[library][book_author].push_back(book);
                        break;}
                }

            else{
                data_base[library].insert({book_author, books});}
        }

        // If the library name isn't in the database, the program adds it there. Also
        // the author we're currently working with is added to the new library.
        else{
            std::map<std::string, std::vector<Book>> author = {{book_author, books}};
            data_base.insert({library, author});
        }

        // After the information of a line has been successfullysaved in the database
        // database the program sorts out the vectors inside the map and returns
        // a value of true.

        std::sort(data_base[library][book_author].begin(),
                  data_base[library][book_author].end());

        return true;
    }

    else{
        return false;}
}



bool read_file(std::string file_name,
               std::map<std::string, std::map<std::string,
               std::vector<Book>>>& data_base ){

/* This attemps to open a file with the given name. If it succeeds, the lines
   of the file will be given to the 'read_a_line' function, which stores the
   information from them to the main datastructure. If the file cannot be opened,
   the program will print out an error message and the execution terminates.

    :param file_name = A filename inputted by user
    :param data_base = The main datastructure
    :return: = returns true if the file reading was successful                */

    std::ifstream file(file_name);
    if (file){

        std::string line;
        while( std::getline(file, line)){

            // If the function returns bool value false, the program will
            // print out an error message and the execution terminates.
            if (!read_a_line(line, data_base)){
                std::cout << "Error: empty field" << std::endl;
                return false;}
        }

        file.close();
        return true;
   }

    else{
        std::cout << "Error: the input file cannot be opened" << std::endl;
        return false;}
}

int main()

{
    // Main database
    // <library_name : <author: <Book1, Book2, Book3.. BookN>>>
    std::map<std::string, std::map<std::string, std::vector<Book>>> data_base;

    std::string file_name = "";
    std::cout << "Input file: ";
    std::getline(std::cin, file_name);

    if(read_file(file_name, data_base)){
        while(true){

            std::string user_input;
            std::cout << "> ";
            std::getline(std::cin, user_input);

            std::vector<std::string> parts = split(user_input, ' ', true);
            std::string command = parts.at(0);

            // Print out all the libraries stored in the database
            if(command == "libraries"){

                if(parts.size() == 1){
                    for ( auto library : data_base)
                        std::cout << library.first << std::endl;}
                else{
                    std::cout << "Error: error in command " << command << std::endl;}
            }

            // Print out all the books of the given library
            else if(command == "material"){

                if(parts.size() == 2){

                    std::string library_name = parts.at(1);

                    if(data_base.find(library_name) != data_base.end()){
                        print_out_library_material(library_name, data_base);}
                    else{
                        std::cout << "Error: unknown library name" << std::endl;}
                }

                else{
                     std::cout << "Error: error in command " << command << std::endl;}
            }

            // Print out all the books that can be found on the shelf
            else if(command == "loanable"){

                if(parts.size() == 1){
                    print_out_loanable_books(data_base);}
                else{
                    std::cout << "Error: error in command " << command << std::endl;}
            }

            // Print out all the books by given author in given library
            else if(command == "books"){

                if(parts.size() == 3){
                    std::string library_name = parts.at(1);
                    std::string book_author = parts.at(2);

                    if(data_base.find(library_name) != data_base.end()){
                        if(data_base[library_name].find(book_author)
                                != data_base[library_name].end()){
                            print_out_book_names(library_name, book_author, data_base);}

                        else{
                            std::cout << "Error: unknown author" << std::endl;}

                    }
                    else{
                        std::cout << "Error: unknown library name" << std::endl;}
                }

                else{
                    std::cout << "Error: error in command " << command << std::endl;}
            }

            // Print out the shortest reservation queue for given book
            else if(command == "reservable"){

                // Temporary string to parse togehter the bookname
                std::string book_name;
                for( unsigned int i = 1; i <= parts.size() -1; i++ ){
                    if (i == parts.size()-1){
                         book_name += parts[i];}
                    else{
                        book_name += parts[i];
                        book_name += " ";}
                }

                // If the user entered the name with quotation marks, they're erased
                book_name.erase(std::remove(book_name.begin(), book_name.end(), '"'),
                                book_name.end());

                shortest_reservation_time(book_name, data_base);
            }

            // Quits the program
            else if(command == "quit"){
                break;
            }

            else {
                std::cout << "Error: Unknown command: " << command << std::endl;}
        }
    }
    else{
        return EXIT_FAILURE;}

    return EXIT_SUCCESS;
}
