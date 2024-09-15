// cli.cpp - Function declarations for the eng_format class
// 
// 09-Sep-24  F.Khan         Created.
#define CURL_STATICLIB

#include "eng_format.hpp"
#include <map>
#include <functional>
#include <iostream>
#include "curl/curl.h"


#ifdef _DEBUG
#pragma comment (lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment (lib, "curl/libcurl_a.lib")
#endif
#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")


//Numerical code for keys assinged to const char 

//Test libcurl=============================

// ===============================================================================================================

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void test_libcurl() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else {
            std::cout << "Response from http://example.com:\n" << readBuffer << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}


const char UP_ARROW = 72;
const char DOWN_ARROW = 80;
const char ENTER_KEY = 13;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}



void displayMenu(const std::vector<std::string>& menuItems, int selectedIndex) {
    system("cls"); 
    for (int i = 0; i < menuItems.size(); ++i) {
        if (i == selectedIndex) {
            std::cout << "--> " << menuItems[i] << std::endl; 
        }
        else {
            std::cout << "  " << menuItems[i] << std::endl;
        }
    }
}
void format_file() {
    std::string Name;
    std::cout << "Please enter the name of the file you want to format" << std::endl;
    std::cin >> Name;
    std::cout << format("{} has been formatted", Name);

}

void summarize_file() {
    std::string Name;
    std::cout << "Please enter the name of the file you want to Summarize" << std::endl;
    std::cin >> Name;
    std::cout << format("{} has been Summarized", Name);

}
void paraphrase_file() {
    std::string Name;
    std::cout << "Please enter the name of the file you want to Paraphrase" << std::endl;
    std::cin >> Name;
    std::cout << format("{} has been Paraphrase", Name);

}

std::map<std::string, std::function<void()>> funcMap =
{
    { "Format document", format_file},
    { "Summarize document", summarize_file},
    { "Paraphrase document", paraphrase_file}

};


int main() {
    test_libcurl();
    std::vector<std::string> menuItems = { "Format document", "Summarize document", "Paraphrase document", "Exit" };
    int selectedIndex = 0;
    char key;
    while (true) {
        displayMenu(menuItems, selectedIndex);

        key = _getch(); // Read key press

        switch (key) {
        case UP_ARROW: // Up arrow key
            selectedIndex = (selectedIndex > 0) ? selectedIndex - 1 : menuItems.size() - 1;
            break;
        case DOWN_ARROW: // Down arrow key
            selectedIndex = (selectedIndex < menuItems.size() - 1) ? selectedIndex + 1 : 0;
            break;
        case ENTER_KEY: // Enter key
            if (selectedIndex == menuItems.size() - 1) { // "Exit" option
                return 0;
            }
            std::cout << "You selected: " << menuItems[selectedIndex] << std::endl;
            if (funcMap.find(menuItems[selectedIndex]) != funcMap.end()) { // Check if the key exists
                funcMap[menuItems[selectedIndex]](); // Call the associated function
            }
            else {
                std::cerr << "Error: Invalid menu selection." << std::endl;
            }
            _getch(); // Wait for user to press a key
            break;
        }
    }

    return 0;
}


