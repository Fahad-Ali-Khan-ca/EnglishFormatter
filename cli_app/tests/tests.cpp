// cli_app/tests/tests.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "api_client.hpp"
#include "common.hpp"
#include "display.hpp"
#include "dotenv.h"
#include <cstdlib>




TEST(ApiClientTests, ThrowsOnMissingApiKey) {
    dotenv::init();
    unsetenv("API_KEY");
    EXPECT_THROW(api_client client, std::runtime_error);
}

TEST(ApiClientTests, MakesSuccessfulApiCall) {
    api_client client;
    std::string prompt = "Test Prompt";
    EXPECT_NO_THROW(client.make_api_call(prompt));
}

TEST(EngFormatTests, ParsesValidResponse) {
    eng_format formatter;
    std::string response = R"({"choices": [{"message": {"content": "Hello, world!"}}]})";
    EXPECT_EQ(formatter.parse_response(response), "Hello, world!");
}

TEST(EngFormatTests, HandlesInvalidResponse) {
    eng_format formatter;
    std::string response = R"({"error": {"message": "Invalid input"}})";
    EXPECT_THROW(formatter.parse_response(response), std::runtime_error);
}

TEST(ApiClientTests, WriteCallbackAppendsResponse) {
    std::string responseData;
    const char* testData = "Test Data";
    size_t size = sizeof(testData) - 1;
    
    size_t written = api_client::WriteCallback((void*)testData, 1, size, &responseData);
    EXPECT_EQ(written, size);
    EXPECT_EQ(responseData, "Test Data");
}

TEST(EngFormatTests, ThrowsOnEmptyResponse) {
    eng_format formatter;
    std::string response = "";
    EXPECT_THROW(formatter.parse_response(response), std::runtime_error);
}

TEST(EngFormatTests, HandlesResponseWithoutChoices) {
    eng_format formatter;
    std::string response = R"({"no_choices": [{"message": {"content": "Test"}}]})";
    EXPECT_THROW(formatter.parse_response(response), std::runtime_error);
}

TEST(EngFormatTests, GetTokenInfoParsesCorrectly) {
    eng_format formatter;
    std::string response = R"({"usage": {"prompt_tokens": 10, "completion_tokens": 5, "total_tokens": 15}})";
    EXPECT_EQ(formatter.get_token_info(response), 
              "Token usage:\nPrompt tokens: 10\nCompletion tokens: 5\nTotal tokens: 15");
}

TEST(EngFormatTests, GetTokenInfoHandlesMissingFields) {
    eng_format formatter;
    std::string response = R"({"usage": {}})";
    EXPECT_EQ(formatter.get_token_info(response), "Token usage information not found in response.");
}

TEST(DisplayTests, HandlesMenuNavigation) {
    std::vector<std::string> menuItems = {"Option 1", "Option 2", "Exit"};
    display menu(menuItems);
    menu.navigate_menu();  // Ensure this can run without throwing errors
}
