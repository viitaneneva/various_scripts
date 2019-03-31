#include "parts.hh"
#include <iostream>
#include <sstream>


Parts::Parts(): first_part_(nullptr), last_part_(nullptr) {
}

Parts::~Parts(){
    while ( first_part_ != nullptr ) {
       Component_list* item_to_be_released = first_part_;
       first_part_ = first_part_->next;

       delete item_to_be_released;
    }
 }

void Parts::add_back(const std::vector<std::string> part_to_be_added)
{

    // Adds data from the given vector to the linked list
    // The vector needs to have 3 or 4 elements or
    // the data wont be added to the list

    std::vector<std::string>::size_type data_length = part_to_be_added.size();

    if(data_length < 3 || data_length > 4){
        std::cout << "Error! There was something wrong with the line. \n"
                     "The data it contained won't be added to the list."
                  << std::endl;
        return;
    }

    bool status;
    std::string component = part_to_be_added[0];
    std::string product_name = part_to_be_added[1];
    float price = stof(part_to_be_added[2]);

    if(data_length == 4){
        status = true;
    }
    else{
        status = false;
    }

    Component_list* new_part = new Component_list{component,
                                                  product_name,
                                                  price, status,
                                                  nullptr};

    if(first_part_ == nullptr){
        first_part_ = new_part;
        last_part_ = new_part;
    }
    else{
        last_part_->next = new_part;
        last_part_ = new_part;
    }
}

void Parts::remove_part(std::string part_to_be_removed)
{

    // This function will delete an item from the list

    Component_list* current = first_part_;
    Component_list* before = nullptr;

    while (current) {
        if (current->component == part_to_be_removed) {
            if (before) {
                before->next = current->next;
            }
            if (first_part_ == current) {
                first_part_ = first_part_->next;
            }

            delete current;
            std::cout << "Successfully deleted the following"
                         " item from the list: " <<
                         part_to_be_removed << std::endl;
            return;
        }
        before = current;
        current = current->next;
    }

    std::cout << "Error! No such component on the list." << std::endl;

}

void Parts::change_status(std::string component) const {

    // Changes a component status from false to true
    // False = the component hasn't been bought
    // True = the component has been bought

    Component_list* item_to_be_changed = first_part_;
    while (item_to_be_changed != nullptr){
        if(item_to_be_changed->component == component){
            if (item_to_be_changed->status){
                std::cout << "This component has already "
                             "been marked as bought." << std::endl;
            }
            else{
                item_to_be_changed->status = true;
                std::cout << "Successfully changed the "
                             "component status." << std::endl;
            }

            return;
        }
        item_to_be_changed = item_to_be_changed->next;
    }

    std::cout << "Error! No such component on the list." << std::endl;
}


void Parts::print_parts() const
{

    // Prints out all the components
    // The function will also tell the user if the component
    // has been marked as bought

    Component_list* item_to_be_printed = first_part_;
    while (item_to_be_printed != nullptr){
        if (item_to_be_printed->status){
            std::cout << item_to_be_printed->component << ": "
                      << item_to_be_printed->name  << ", [BOUGHT]"
                      << std::endl;
        }
        else{
            std::cout << item_to_be_printed->component << ": "
                      << item_to_be_printed->name << std::endl;
        }

        item_to_be_printed = item_to_be_printed->next;
    }

}

void Parts::print_the_total_price() const
{

    // Prints out the components that are yet to be bought
    // as well as their prices and the total sum

    float sum = 0;
    Component_list* item_to_be_printed = first_part_;

    while(item_to_be_printed != nullptr){
        if(item_to_be_printed->status == false){
            std::cout << item_to_be_printed->component << ": " <<
                         item_to_be_printed->name << ".........."
                      << item_to_be_printed->price << "e" << std::endl;

            sum += item_to_be_printed->price;
        }

        item_to_be_printed = item_to_be_printed->next;
    }

    std::cout << "--------------" << std::endl;
    std::cout << "TOTAL: " << sum << "e" << std::endl;

}

std::vector<std::string> Parts::pack_the_data(){

    // Pack the data, if there's any, into a vector
    // for further purpose

    Component_list* item = first_part_;

    std::vector<std::string> lines;
    while(item != nullptr){
        std::stringstream ss;

        ss << item->component << ";" << item->name << ";" << item->price;
        if (item->status){
            ss << ";" << "bought";
        }

        std::string line = ss.str();
        lines.push_back(line);

        item = item->next;
    }

    return lines;
}

