// cli.cpp - Function declarations for the eng_format class
// 
// 09-Sep-24  F.Khan         Created.
#include "display.hpp"


int main() {
    dotenv::init();

    // Define the menu items this should be done dynamically by someone who was administrator priviledges 
    // potential user input for more diversity
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