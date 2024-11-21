// cli_app/tests/tests.cpp
#include <gtest/gtest.h>
#include "api_client.hpp"
#include "eng_format.hpp"
#include "display.hpp"
#include "dotenv.h"
#include <cstdlib>

// // Test for missing API key
// TEST(ApiClientTests, ThrowsOnMissingApiKey) {
//     dotenv::init();
//     unsetenv("API_KEY"); // Use unsetenv from <cstdlib>
//     EXPECT_THROW(api_client client, std::runtime_error);
// }

// // Test for making a successful API call
// TEST(ApiClientTests, MakesSuccessfulApiCall) {
//     dotenv::init();
//     setenv("API_KEY", "test_key", 1);  // Mock environment variables
//     setenv("API_URL", "https://example.com/api", 1);
//     api_client client;
//     EXPECT_NO_THROW(client.make_api_call("Test Prompt"));
// }

// // Test parsing valid response from eng_format
// TEST(EngFormatTests, ParsesValidResponse) {
//     eng_format formatter;
//     std::string response = R"({"choices": [{"message": {"content": "Hello, world!"}}]})";
//     EXPECT_EQ(formatter.parse_response(response), "Hello, world!");
// }

// // Test handling invalid API response
// TEST(EngFormatTests, HandlesInvalidResponse) {
//     eng_format formatter;
//     std::string response = R"({"error": {"message": "Invalid input"}})";
//     EXPECT_THROW(formatter.parse_response(response), std::runtime_error);
// }

// // // Test WriteCallback in api_client
// // TEST(ApiClientTests, WriteCallbackAppendsResponse) {
// //     std::string responseData;
// //     const char* testData = "Test Data";
// //     size_t size = strlen(testData);

// //     size_t written = api_client::WriteCallback((void*)testData, 1, size, &responseData);
// //     EXPECT_EQ(written, size);
// //     EXPECT_EQ(responseData, "Test Data");
// // }

// // Test throwing on empty response in eng_format
// TEST(EngFormatTests, ThrowsOnEmptyResponse) {
//     eng_format formatter;
//     std::string response = "";
//     EXPECT_THROW(formatter.parse_response(response), std::runtime_error);
// }

// // Test handling response without "choices" field in eng_format
// TEST(EngFormatTests, HandlesResponseWithoutChoices) {
//     eng_format formatter;
//     std::string response = R"({"no_choices": [{"message": {"content": "Test"}}]})";
//     EXPECT_THROW(formatter.parse_response(response), std::runtime_error);
// }

// // Test for parsing token information correctly
// TEST(EngFormatTests, GetTokenInfoParsesCorrectly) {
//     eng_format formatter;
//     std::string response = R"({"usage": {"prompt_tokens": 10, "completion_tokens": 5, "total_tokens": 15}})";
//     EXPECT_EQ(formatter.get_token_info(response),
//               "Token usage:\nPrompt tokens: 10\nCompletion tokens: 5\nTotal tokens: 15");
// }

// Test handling missing token fields in API response
TEST(EngFormatTests, GetTokenInfoHandlesMissingFields) {
    eng_format formatter;
    std::string response = R"({"usage": {}})";
    EXPECT_EQ(formatter.get_token_info(response), "Token usage information not found in response.");
}

// Test for navigating a menu in display
TEST(DisplayTests, HandlesMenuNavigation) {
    std::vector<std::string> menuItems = {"Option 1", "Option 2", "Exit"};
    display menu(menuItems);
    EXPECT_NO_THROW(menu.navigate_menu());  // Ensure navigation runs without errors
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
