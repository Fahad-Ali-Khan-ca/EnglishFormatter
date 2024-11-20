cmake_minimum_required(VERSION 3.20)

# Set the project name
project(EnglishFormatter LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories for headers
include_directories(cli_app/include)

# Add source files
file(GLOB SOURCES
    cli_app/src/*.cpp
)

# Add test files
file(GLOB TEST_SOURCES
    cli_app/tests/*.cpp
)

# Define the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${TEST_SOURCES})

# Find and link CURL
find_package(CURL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)

# Include Google Test if tests exist
find_package(GTest REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main)

# Enable testing
enable_testing()
add_test(NAME EnglishFormatterTests COMMAND ${PROJECT_NAME})
