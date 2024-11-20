cmake_minimum_required(VERSION 3.20)
project(EnglishFormatter LANGUAGES CXX)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB SOURCES
    cli_app/src/*.cpp
)

# Define the main executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories for headers
target_include_directories(${PROJECT_NAME} PRIVATE cli_app/include)

# Find and link CURL and fmt libraries
find_package(CURL REQUIRED)
find_package(fmt REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl fmt::fmt)

# ------------------------
# GoogleTest and GoogleMock Configuration
# ------------------------
include(FetchContent)

# Fetch GoogleTest (which includes GoogleMock)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

# Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Optionally, set to build GMock as well
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test source files
file(GLOB TEST_SOURCES
    cli_app/tests/*.cpp
)

# Define the test executable
add_executable(EnglishFormatterTests ${TEST_SOURCES})

# Include directories for tests (if separate)
target_include_directories(EnglishFormatterTests PRIVATE cli_app/include)

# Link test executable against GTest, GMock, and the main project
target_link_libraries(EnglishFormatterTests 
    PRIVATE 
        GTest::gtest 
        GTest::gtest_main 
        GMock::gmock 
        GMock::gmock_main 
        ${PROJECT_NAME}
)

# Register the tests
add_test(NAME EnglishFormatterTests COMMAND EnglishFormatterTests)
