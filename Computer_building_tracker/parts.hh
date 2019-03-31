#ifndef PARTS_HH
#define PARTS_HH

#include <string>
#include <vector>

class Parts
{   
public:
  Parts();

  void add_back(const std::vector<std::string> part_to_be_added);
  void remove_part(std::string removed_part);
  void print_parts() const;
  void change_status(std::string component) const;
  void print_the_total_price() const;
  std::vector<std::string> pack_the_data();

  ~Parts();

private:
  struct Component_list {
     std::string component;
     std::string name;
     float price;
     bool status;
     Component_list* next;
  };

  Component_list* first_part_;
  Component_list* last_part_;
};

#endif // PARTS_HH
