// tests.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "api_client.hpp"
#include "common.hpp"
#include "cli.cpp"
#include "display.hpp"

class MockApiClient : public api_client {
public:
    MOCK_METHOD(std::string, make_api_call, (const std::string& prompt), (override));
};

TEST(MockApiClientTests, MockedApiResponse) {
    MockApiClient mockClient;
    EXPECT_CALL(mockClient, make_api_call)
        .WillOnce(::testing::Return(R"({"choices": [{"message": {"content": "Mock Response"}}]})"));
    
    std::string response = mockClient.make_api_call("Test Prompt");
    EXPECT_EQ(response, R"({"choices": [{"message": {"content": "Mock Response"}}]})");
}

// Mock the CURL and environment variable setup
TEST(ApiClientTests, ThrowsOnMissingApiKey) {
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


TEST(CliTests, ReturnsErrorOnUnrecognizedOption) {
    const char* argv[] = {"tool_name", "--invalid"};
    EXPECT_EQ(main(2, (char**)argv), 1); // Assuming 1 is error code
}

TEST(CliTests, HandlesHelpFlag) {
    const char* argv[] = {"tool_name", "--help"};
    EXPECT_EQ(main(2, (char**)argv), 0);
}

TEST(CliTests, HandlesVersionFlag) {
    const char* argv[] = {"tool_name", "--version"};
    EXPECT_EQ(main(2, (char**)argv), 0);
}


TEST(DisplayTests, HandlesMenuNavigation) {
    std::vector<std::string> menuItems = {"Option 1", "Option 2", "Exit"};
    display menu(menuItems);
    menu.navigate_menu();  // Ensure this can run without throwing errors
}