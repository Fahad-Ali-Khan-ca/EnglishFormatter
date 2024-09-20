// cli.cpp - Function declarations for the eng_format class
// 
// 09-Sep-24  F.Khan         Created.
#include "display.hpp"
#include "dotenv.h"

const std::string TOOL_NAME = "EnglishFormatter";
const std::string TOOL_VERSION = "0.1";
std::string model = "llama3-8b-8192";
std::string output_name = "_modified";

int main( int argc, char *argv[]) {

    bool showVersion = false;
    bool showHelp = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--version" || arg == "-v") {
            showVersion = true;
            break; // Exit the loop; no need to process further arguments
        }
        else if (arg == "--help" || arg == "-h") {
            showHelp = true;
            break; // Exit the loop; no need to process further arguments
        }
        else if (arg == "--model" || arg == "-m") {
            if (i + 1 < argc) {
                std::string old_model = model;
                model = argv[++i]; // Increment i to skip over the value
                std::cout << "Model changed from " << old_model << " to " << model << "." << std::endl;
            }
            else {
                std::cerr << "Error: The option '" << arg << "' requires a model name as an argument." << std::endl;
                return 1; // Exit with error code
            }
        }
        else if (arg == "--output" || arg == "-o") {
            if (i + 1 < argc) {
                output_name = argv[++i]; // Increment i to skip over the value
                std::cout << "Output files will now be saved under [name]" << output_name << std::endl;
            }
            else {
                std::cerr << "Error: The option '" << arg << "' requires an output name as an argument." << std::endl;
                return 1; // Exit with error code
            }
        }
        else {
            std::cerr << "Error: Unrecognized option '" << arg << "'" << std::endl;
            return 1; // Exit with error code
        }
    }

    if (showVersion) {
        std::cout << "Tool Name: " << TOOL_NAME << "\nVersion: " << TOOL_VERSION << std::endl;
        return 0;
    }

    if (showHelp) {
        std::cout << "Usage: my_tool [options]\n"
            << "Options:\n"
            << "  -h, --help           Show this help message and exit\n"
            << "  -v, --version        Show the tool's version and exit\n"
            << "  -m, --model MODEL    Specify the model to use\n"
            << "  -o, --output NAME    Specify the output file suffix\n"
            << std::endl;

    }

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