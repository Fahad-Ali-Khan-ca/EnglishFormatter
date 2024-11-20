cmake_minimum_required(VERSION 3.10)

# Project name and version
project(EnglishFormatter VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories for headers
include_directories(cli_app/include)

# Specify source files
set(SOURCES
    cli_app/src/cli.cpp
    cli_app/src/api_client.cpp
    cli_app/src/display.cpp
    cli_app/src/common.cpp
    cli_app/tests/test.cpp
)

# Find required packages
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

# Add Google Test framework
enable_testing()

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gmock gtest_main)

# Add test cases
add_test(NAME EnglishFormatterTests COMMAND ${PROJECT_NAME})
