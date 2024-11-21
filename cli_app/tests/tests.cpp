// cli_app/tests/tests.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "common.hpp"
#include "display.hpp"
#include "eng_format.hpp"
#include <cstdlib>

// Test EngFormat for parsing valid API responses
TEST(EngFormatTests, ParsesValidResponse) {
    eng_format formatter;
    std::string response = R"({"choices": [{"message": {"content": "Hello, world!"}}]})";
    EXPECT_EQ(formatter.parse_response(response), "Hello, world!");
}

// Test EngFormat for handling invalid API responses
TEST(EngFormatTests, HandlesInvalidResponse) {
    eng_format formatter;
    std::string response = R"({"error": {"message": "Invalid input"}})";
    EXPECT_THROW(formatter.parse_response(response), std::runtime_error);
}

// Test EngFormat for handling empty API responses
TEST(EngFormatTests, ThrowsOnEmptyResponse) {
    eng_format formatter;
    std::string response = "";
    EXPECT_THROW(formatter.parse_response(response), std::runtime_error);
}

// Test EngFormat for handling API responses without choices
TEST(EngFormatTests, HandlesResponseWithoutChoices) {
    eng_format formatter;
    std::string response = R"({"no_choices": [{"message": {"content": "Test"}}]})";
    EXPECT_THROW(formatter.parse_response(response), std::runtime_error);
}

// Test EngFormat for parsing token usage information
TEST(EngFormatTests, GetTokenInfoParsesCorrectly) {
    eng_format formatter;
    std::string response = R"({"usage": {"prompt_tokens": 10, "completion_tokens": 5, "total_tokens": 15}})";
    EXPECT_EQ(formatter.get_token_info(response), 
              "Token usage:\nPrompt tokens: 10\nCompletion tokens: 5\nTotal tokens: 15");
}

// Test EngFormat for handling missing token usage fields
TEST(EngFormatTests, GetTokenInfoHandlesMissingFields) {
    eng_format formatter;
    std::string response = R"({"usage": {}})";
    EXPECT_EQ(formatter.get_token_info(response), "Token usage information not found in response.");
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
