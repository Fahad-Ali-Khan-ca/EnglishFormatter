// cli_app/tests/tests.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "api_client.hpp"
#include "common.hpp"
#include "display.hpp"
#include "dotenv.h"
#include <cstdlib>

TEST(EngFormatTests, ParsesValidResponse) {
    // Set dummy environment variables for testing
    setenv("API_KEY", "dummy_key", 1);
    setenv("API_URL", "https://dummy.url", 1);

    eng_format formatter;
    std::string response = R"({"choices": [{"message": {"content": "Hello, world!"}}]})";
    EXPECT_EQ(formatter.parse_response(response), "Hello, world!");
}

TEST(EngFormatTests, HandlesInvalidResponse) {
    // Set dummy environment variables for testing
    setenv("API_KEY", "dummy_key", 1);
    setenv("API_URL", "https://dummy.url", 1);

    eng_format formatter;
    std::string response = R"({"error": {"message": "Invalid input"}})";
    EXPECT_THROW(formatter.parse_response(response), std::runtime_error);
}

TEST(EngFormatTests, ThrowsOnEmptyResponse) {
    // Set dummy environment variables for testing
    setenv("API_KEY", "dummy_key", 1);
    setenv("API_URL", "https://dummy.url", 1);

    eng_format formatter;
    std::string response = "";
    EXPECT_THROW(formatter.parse_response(response), std::runtime_error);
}

TEST(EngFormatTests, HandlesResponseWithoutChoices) {
    // Set dummy environment variables for testing
    setenv("API_KEY", "dummy_key", 1);
    setenv("API_URL", "https://dummy.url", 1);

    eng_format formatter;
    std::string response = R"({"no_choices": [{"message": {"content": "Test"}}]})";
    EXPECT_THROW(formatter.parse_response(response), std::runtime_error);
}

// TEST(EngFormatTests, GetTokenInfoParsesCorrectly) {
//     // Set dummy environment variables for testing
//     setenv("API_KEY", "dummy_key", 1);
//     setenv("API_URL", "https://dummy.url", 1);

//     eng_format formatter;
//     std::string response = R"({"usage": {"prompt_tokens": 10, "completion_tokens": 5, "total_tokens": 15}})";
//     EXPECT_EQ(formatter.get_token_info(response), 
//               "Token usage:\nPrompt tokens: 10\nCompletion tokens: 5\nTotal tokens: 15");
// }

// TEST(EngFormatTests, GetTokenInfoHandlesMissingFields) {
//     // Set dummy environment variables for testing
//     setenv("API_KEY", "dummy_key", 1);
//     setenv("API_URL", "https://dummy.url", 1);

//     eng_format formatter;
//     std::string response = R"({"usage": {}})";
//     EXPECT_EQ(formatter.get_token_info(response), "Token usage information not found in response.");
// }

// TEST(DisplayTests, HandlesMenuNavigation) {
//     // Set dummy environment variables for testing
//     setenv("API_KEY", "dummy_key", 1);
//     setenv("API_URL", "https://dummy.url", 1);

//     std::vector<std::string> menuItems = {"Option 1", "Option 2", "Exit"};
//     display menu(menuItems);
//     EXPECT_NO_THROW(menu.navigate_menu()); // Ensure this can run without throwing errors
// }

// TEST(ApiClientTests, WriteCallbackAppendsResponse) {
//     // Set dummy environment variables for testing
//     setenv("API_KEY", "dummy_key", 1);
//     setenv("API_URL", "https://dummy.url", 1);

//     std::string responseData;
//     const char* testData = "Test Data";
//     size_t size = sizeof(testData) - 1;

//     size_t written = api_client::WriteCallback((void*)testData, 1, size, &responseData);
//     EXPECT_EQ(written, size);
//     EXPECT_EQ(responseData, "Test Data");
// }

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
