cmake_minimum_required(VERSION 3.20)
project(EnglishFormatter LANGUAGES CXX)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------
# Core Library Configuration
# ------------------------

# Collect all source files for the core library, excluding cli.cpp
file(GLOB CORE_SOURCES
    cli_app/src/*.cpp
)

# Exclude cli.cpp from CORE_SOURCES to prevent multiple main definitions
list(FILTER CORE_SOURCES EXCLUDE REGEX "cli\\.cpp$")

# Define the core library
add_library(core_lib STATIC ${CORE_SOURCES})

# Include directories for the core library
target_include_directories(core_lib PUBLIC cli_app/include)

# Find and link CURL and fmt libraries
find_package(CURL REQUIRED)
find_package(fmt REQUIRED)
target_link_libraries(core_lib PUBLIC CURL::libcurl fmt::fmt)

# ------------------------
# GoogleTest and GoogleMock Configuration
# ------------------------
include(FetchContent)

# Fetch GoogleTest (which includes GoogleMock)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP ON
)

# Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Enable building GMock and GTest
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# ------------------------
# Main Executable Configuration
# ------------------------

# Define the main executable and link it against the core library
add_executable(EnglishFormatter cli_app/src/cli.cpp)
target_link_libraries(EnglishFormatter PRIVATE core_lib)

# ------------------------
# Test Executable Configuration
# ------------------------

# Collect all test source files
file(GLOB TEST_SOURCES
    cli_app/tests/*.cpp
)

# Define the test executable
add_executable(EnglishFormatterTests ${TEST_SOURCES})

# Include directories for tests
target_include_directories(EnglishFormatterTests PRIVATE cli_app/include)

# Link test executable against GMock, GTest, and the core library
target_link_libraries(EnglishFormatterTests 
    PRIVATE 
        gmock 
        gtest 
        core_lib
)

# Register the tests
add_test(NAME EnglishFormatterTests COMMAND EnglishFormatterTests)
