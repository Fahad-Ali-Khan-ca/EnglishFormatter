// cli.cpp - Function declarations for the eng_format class
// 
// 09-Sep-24  F.Khan         Created.
#include "display.hpp"


int main() {
    // Define the menu items
    std::vector<std::string> menuItems = {
        "Format document",
        "Summarize document",
        "Paraphrase document",
        "Exit"
    };

    // Create an instance of the display class
    display menuDisplay(menuItems);

    // Call the navigate_menu() method to start the menu interaction
    menuDisplay.navigate_menu();

    // Program ends when navigate_menu() returns (e.g., when "Exit" is selected)
    std::cout << "\nProgram exited." << std::endl;
    return 0;
}