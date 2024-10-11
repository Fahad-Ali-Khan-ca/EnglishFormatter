# Contributing to EnglishFormatter

Thank you for your interest in contributing to **EnglishFormatter**! This document provides guidelines for setting up your development environment, building the project, and contributing code.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Setting Up the Development Environment](#setting-up-the-development-environment)
- [Building the Project](#building-the-project)
- [Running Tests](#running-tests)
  - [Setting Up the Testing Framework](#setting-up-the-testing-framework)
  - [Running Test Cases](#running-test-cases)
  - [Adding New Tests](#adding-new-tests)
  - [Test Guidelines](#test-guidelines)
- [Source Code Formatting](#source-code-formatting)
  - [Setting Up clang-format](#setting-up-clang-format)
  - [Running clang-format](#running-clang-format)
- [Linting the Code](#linting-the-code)
  - [Setting Up clang-tidy](#setting-up-clang-tidy)
  - [Running clang-tidy](#running-clang-tidy)
- [Editor/IDE Integration](#editoride-integration)
  - [Visual Studio Code Integration](#visual-studio-code-integration)
- [Development Guidelines](#development-guidelines)
- [Project Structure](#project-structure)
- [Extending the Tool](#extending-the-tool)
- [Submitting Changes](#submitting-changes)
- [Support](#support)
- [Acknowledgments](#acknowledgments)

---

## Prerequisites

Before you begin, ensure you have met the following requirements:

- **C++17 or higher**: A compiler that supports C++17.
- **libcurl**: For making HTTP requests to the API.
- **nlohmann/json**: For JSON parsing and serialization.
- **dotenv-cpp**: To manage environment variables from a `.env` file.
- **An API Key**: You'll need an API key from the language model provider (e.g., OpenAI).

## Setting Up the Development Environment

### Installing Dependencies

#### libcurl

- **Windows**: Download the pre-built binaries from the [official website](https://curl.se/windows/).
- **Unix/Linux**:

  ```bash
  sudo apt-get install libcurl4-openssl-dev
  ```

#### nlohmann/json

- Download the single-header `json.hpp` file from the [GitHub repository](https://github.com/nlohmann/json/releases).

#### dotenv-cpp

- Clone the repository:

  ```bash
  git clone https://github.com/motdotla/dotenv-cpp.git
  ```

- Include the `dotenv.h` and `dotenv.cpp` in your project.

### Setting Up the `.env` File

Create a `.env` file in the project's root directory:

```
API_KEY=your_api_key_here
```

Replace `your_api_key_here` with your actual API key.

## Building the Project

### Using `g++`

```bash
g++ -std=c++17 -o EnglishFormatter main.cpp eng_format.cpp display.cpp dotenv.cpp -lcurl -pthread
```

### Using Visual Studio

- Open the solution file or create a new project.
- Add all source files to the project.
- Link against `libcurl` and ensure all dependencies are included.
- Build the project.

## Running Tests

### Setting Up the Testing Framework

We use **Google Test (GTest)** and **Google Mock (GMock)** for writing and running unit tests. 

#### Installing Google Test

1. **Linux**:
   ```bash
   sudo apt-get install libgtest-dev
   cd /usr/src/gtest
   sudo cmake .
   sudo make
   sudo cp *.a /usr/lib
   ```

2. **Windows**:
   Download the [Google Test source](https://github.com/google/googletest) and build it according to the instructions.

3. **MacOS**:
   Install via Homebrew:
   ```bash
   brew install googletest
   ```

### Running Test Cases

1. Build the tests:
   ```bash
   g++ -std=c++17 -I<gtest-include-path> -I<project-include-path> tests.cpp -o tests -lgtest -lgmock -lpthread
   ```

2. Run the tests:
   ```bash
   ./tests
   ```

3. View the results in the terminal. Successful tests will pass, and failed tests will display detailed error messages.

---

### Adding New Tests

#### Test Organization
- Test cases are located in the `tests.cpp` file.
- Each test case corresponds to a specific function or class in the project.

#### Example of a New Test Case

To add a test for `eng_format`:

```cpp
#include <gtest/gtest.h>
#include "eng_format.hpp"

TEST(EngFormatTests, NewFunctionTest) {
    eng_format formatter;
    // Add logic for the new test case
    EXPECT_EQ(formatter.some_function(), expected_result);
}
```

1. Add the test case in `tests.cpp`.
2. Rebuild and run the tests to verify.

### Test Guidelines

1. **Test Coverage**:
   - Ensure new features and bug fixes are covered by tests.
   - Write tests for edge cases (e.g., invalid inputs, empty strings, etc.).

2. **Mocking**:
   - Use `Google Mock` to mock external dependencies, such as API calls.

3. **Readability**:
   - Write clear and descriptive test names.
   - Include comments if the test logic is complex.

---


## Source Code Formatting

We use `clang-format` to maintain consistent code style throughout the project.

### Setting Up clang-format

1. **Install clang-format**:

   - **Windows**: Download from the [LLVM website](https://releases.llvm.org/download.html).
   - **Unix/Linux**:

     ```bash
     sudo apt-get install clang-format
     ```

2. **Configuration**:

   - A `.clang-format` file is provided at the root of the project.
   - It uses the default style. You can customize it by editing the `.clang-format` file.

### Running clang-format

**Command-Line Usage**:

A script is provided to format the entire codebase:

```bash
./format.sh
```

**Contents of `format.sh`**:

```bash
#!/bin/bash
clang-format -i *.cpp *.hpp
```

Make the script executable:

```bash
chmod +x format.sh
```

**Note**: Run this script before committing your code to ensure consistent formatting.

## Linting the Code

We use `clang-tidy` to catch common mistakes and improve code quality.

### Setting Up clang-tidy

1. **Install clang-tidy**:

   - **Windows**: Download from the [LLVM website](https://releases.llvm.org/download.html).
   - **Unix/Linux**:

     ```bash
     sudo apt-get install clang-tidy
     ```

2. **Configuration**:

   - Create a `.clang-tidy` file in the root directory.
   - Example `.clang-tidy` configuration:

     ```yaml
     Checks: '-*,clang-analyzer-*'
     WarningsAsErrors: ''
     ```

### Running clang-tidy

**Command-Line Usage**:

A script is provided to lint the codebase:

```bash
./lint.sh
```

**Contents of `lint.sh`**:

```bash
#!/bin/bash
clang-tidy *.cpp -- -std=c++17
```

Make the script executable:

```bash
chmod +x lint.sh
```

**Note**: Run this script to identify and fix code issues.

**Fixing Issues**:

- Review the warnings and errors reported by `clang-tidy`.
- Fix the issues in your code.
- If necessary, you can suppress specific warnings using `// NOLINT` comments or adjust the `.clang-tidy` configuration.

## Editor/IDE Integration

### Visual Studio Code Integration

We recommend using Visual Studio Code for development. Here's how to integrate `clang-format` and `clang-tidy`:

1. **Install Extensions**:

   - Install the [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack).

2. **Configure Settings**:

   Create a `.vscode/settings.json` file with the following content:

   ```json
   {
     "editor.formatOnSave": true,
     "C_Cpp.clang_format_style": "file",
     "C_Cpp.clang_format_fallbackStyle": "LLVM",
     "C_Cpp.clang_format_path": "clang-format",
     "C_Cpp.codeAnalysis.clangTidy.enabled": true,
     "C_Cpp.codeAnalysis.clangTidy.path": "clang-tidy",
     "C_Cpp.codeAnalysis.clangTidy.useBuildPath": false,
     "C_Cpp.codeAnalysis.clangTidy.checks": "-*,clang-analyzer-*"
   }
   ```

   **Note**: Ensure `clang-format` and `clang-tidy` are in your system's PATH. If not, provide the full paths.

3. **Auto-Formatting on Save**:

   With `"editor.formatOnSave": true`, your code will be automatically formatted when you save a file.

4. **Live Linting**:

   The editor will underline issues found by `clang-tidy` as you type.

## Development Guidelines

- Follow the coding style enforced by `clang-format`.
- Run `clang-tidy` and fix issues before submitting changes.
- Ensure new features have appropriate error handling.
- Update documentation as needed.

## Project Structure

- `main.cpp`: Entry point of the application.
- `eng_format.hpp/cpp`: Contains the `eng_format` class responsible for processing files and making API calls.
- `display.hpp/cpp`: Contains the `display` class for the interactive menu.
- `dotenv.h/cpp`: Manages environment variables.
- `common.hpp`: Common includes and declarations.
- `.env`: Contains environment variables like `API_KEY`.
- `format.sh`: Script to run `clang-format` on the codebase.
- `lint.sh`: Script to run `clang-tidy` on the codebase.

## Extending the Tool

### Adding New Actions

1. Update the `menuItems` vector in `main.cpp` with the new action.
2. Implement a new method in `eng_format` to handle the action.
3. Update the `process_files()` method to include the new action.

### Customizing Prompts

Modify the prompt messages in the `handle_file_input()` method of the `display` class.

### Enhancing Error Handling

Add additional checks and exception handling where necessary.

## Submitting Changes

1. **Fork the Repository**.

2. **Create a Feature Branch**:

   ```bash
   git checkout -b feature/YourFeature
   ```

3. **Commit Changes**:

   ```bash
   git commit -am 'Add new feature'
   ```

4. **Push to Branch**:

   ```bash
   git push origin feature/YourFeature
   ```

5. **Create a Pull Request**.

## Support

If you encounter any issues or have questions, please create an issue on the GitHub repository or contact the maintainer directly.

## Acknowledgments

- **libcurl**: For easy HTTP requests.
- **nlohmann/json**: For JSON parsing.
- **dotenv-cpp**: For environment variable management.
- **OpenAI**: For providing advanced language models.

---

**Thank you for contributing to EnglishFormatter!**
