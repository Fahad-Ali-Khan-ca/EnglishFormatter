// display.hpp -  To display the menu and pass user input
//
// 19-Sep-24  F.Khan         Created.
#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include "common.hpp"
#include "eng_format.hpp"

class display {
 public:
  display(const std::vector<std::string> &menuItems);
  void navigate_menu();
  void set_menu_options(const std::vector<std::string> &menuItems);
  std::vector<std::string> get_menu_options() const;
  std::vector<std::string> handle_file_input(const std::string &action);
  void show_menu();
  char getKeyPress();
  void clearScreen();

 private:
  // Had to make them compile time constants since they were not being
  // recognized as constant at compiler time
  static constexpr char UP_ARROW = 72;
  static constexpr char DOWN_ARROW = 80;
  static constexpr char ENTER_KEY = 13;
  std::vector<std::string> menuItems;
  int selectedIndex = 0;
  eng_format formatter;
};

#endif  // !_DISPLAY_H_
