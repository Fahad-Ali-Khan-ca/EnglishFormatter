// display.cpp - Functions declarations for display class
//
// 19-Sep-24  F.Khan         Created.
#include <termios.h>
#include <unistd.h>  
#include "display.hpp"

void display::clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

display::display(const std::vector<std::string>& items)
    : menuItems(items), selectedIndex(0) {}

char display::getKeyPress() {
#ifdef _WIN32
  return _getch();
#else
  struct termios oldt, newt;
  char ch;
  tcgetattr(STDIN_FILENO, &oldt);  // Get current terminal attributes
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);         // Disable canonical mode and echo
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Set new attributes
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore old attributes
  return ch;
#endif
}

void display::show_menu() {
  clearScreen();
  for (int i = 0; i < menuItems.size(); ++i) {
    if (i == selectedIndex) {
      std::cout << "--> " << menuItems[i] << std::endl;
    } else {
      std::cout << "  " << menuItems[i] << std::endl;
    }
  }
}

void display::navigate_menu() {
  char key;
  while (true) {
    show_menu();
    key = getKeyPress();

    switch (key) {
      case UP_ARROW:
        selectedIndex =
            (selectedIndex > 0) ? selectedIndex - 1 : menuItems.size() - 1;
        break;
      case DOWN_ARROW:
        selectedIndex =
            (selectedIndex < menuItems.size() - 1) ? selectedIndex + 1 : 0;
        break;
      case ENTER_KEY:
        if (selectedIndex == menuItems.size() - 1) {
          return;  // Exit option
        }
        std::vector<std::string> files =
            handle_file_input(menuItems[selectedIndex]);
        for (const auto& file : files) {
          formatter.convert_file(
              file, menuItems[selectedIndex]);  // Assuming convert_file is a
                                                // valid method
          std::cout << format("{} has been {}", file, menuItems[selectedIndex])
                    << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Enter any key to continue" << std::endl;
        getKeyPress();  // Wait for a keypress
        break;
    }
  }
}

std::vector<std::string> display::handle_file_input(const std::string& action) {
  clearScreen();
  std::cout << format(
      "Please enter the name of the file(s) you want to {} (separated by "
      "spaces) \n ",
      action);

  std::string input;
  std::getline(std::cin, input);  // Get the entire line of input

  std::istringstream iss(input);
  std::string path;
  std::vector<std::string> files;

  // Parse the input by splitting it based on space

  while (iss >> path) {
    if (std::filesystem::exists(path)) {
      if (std::filesystem::is_regular_file(path)) {
        files.push_back(path);  // It's a file, add it directly
      } else if (std::filesystem::is_directory(path)) {
        // It's a folder, process all files inside recursively
        for (const auto& entry :
             std::filesystem::recursive_directory_iterator(path)) {
          if (std::filesystem::is_regular_file(entry.path())) {
            files.push_back(
                entry.path().string());  // Add all files in the folder
          }
        }
      } else {
        std::cerr << "Unknown path type: " << path << std::endl;
      }
    } else {
      std::cerr << "Path does not exist: " << path << std::endl;
    }
  }

  return files;
}
