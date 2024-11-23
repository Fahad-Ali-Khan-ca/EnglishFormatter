# EnglishFormatter

EnglishFormatter is a command-line tool designed to help users format, summarize, or paraphrase text documents using advanced language models. It provides an interactive menu-driven interface and supports customization through command-line arguments.

[Here's a link to a demo of the tool in action using VSCode](https://youtu.be/6LvhQ6r_KDE).

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Configuration](#configuration)
- [Usage](#usage)
  - [Command-Line Options](#command-line-options)
  - [Interactive Menu](#interactive-menu)
- [Examples](#examples)
- [Development](#development)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)
- [Acknowledgments](#acknowledgments)
- [Notes](#notes)
- [FAQ](#frequently-asked-questions-faq)
- [Detailed Class Explanations](#detailed-class-explanations)
- [Extending the Tool](#extending-the-tool)
- [Support](#support)

---

## Features

- **Format Documents**: Improve the readability and structure of your text.
- **Summarize Documents**: Generate concise summaries of lengthy texts.
- **Paraphrase Documents**: Rephrase text while preserving the original meaning.
- **Customizable Models**: Choose different language models for processing.
- **Output Customization**: Define custom suffixes for output files.
- **Interactive Menu**: User-friendly navigation through the tool's features.
- **Cross-Platform Support**: Compatible with Windows and Unix-like systems.

---

## Prerequisites

- **CMake 3.20 or higher**: For building the project.
- **C++20 Compiler**: A compiler that supports C++20 (e.g., GCC 10+, Clang 10+, MSVC 2019+).
- **Vcpkg**: For dependency management.
- **An API Key**: You'll need an API key from the language model provider (e.g., OpenAI).

---

## Installation

### 1. Install Vcpkg

Vcpkg is a package manager for C++ libraries.

- **Clone Vcpkg**

  ```bash
  git clone https://github.com/microsoft/vcpkg.git
  ```

- **Bootstrap Vcpkg**

  ```bash
  cd vcpkg
  # On Unix/Linux/macOS
  ./bootstrap-vcpkg.sh
  # On Windows (PowerShell)
  .\bootstrap-vcpkg.bat
  ```

### 2. Clone the Repository

```bash
git clone https://github.com/yourusername/EnglishFormatter.git
cd EnglishFormatter
```

### 3. Set Up the `.env` File

Create a `.env` file in the project's root directory:

```
API_KEY=your_api_key_here
```

Replace `your_api_key_here` with your actual API key.

### 4. Build the Project

#### Using CMake and Vcpkg

- **Create a Build Directory**

  ```bash
  mkdir build
  cd build
  ```

- **Configure the Project with CMake**

  ```bash
  cmake .. -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
  ```

- **Build the Project**

  ```bash
  cmake --build .
  ```

**Note**: On Windows with Visual Studio, you may need to specify the configuration:

```bash
cmake --build . --config Release
```

### 5. Run the Application

- **Unix/Linux/macOS**

  ```bash
  ./EnglishFormatter
  ```

- **Windows**

  ```bash
  .\EnglishFormatter.exe
  ```

---

## Configuration

- **API Key**

  The tool requires an API key to access the language model API. Set the `API_KEY` in the `.env` file or as an environment variable.

- **Default Model**

  The default language model is `gpt-3.5-turbo`. You can change this using the `--model` command-line option.

- **Output Suffix**

  The default suffix for output files is `_modified`. Customize it using the `--output` command-line option.

---

## Usage

### Command-Line Options

```bash
EnglishFormatter [options]

Options:
  -h, --help            Show this help message and exit
  -v, --version         Show the tool's version and exit
  -m, --model MODEL     Specify the language model to use (default: gpt-3.5-turbo)
  -o, --output SUFFIX   Specify the output file suffix (default: _modified)
  -t, --token-usage     Show token usage and exit
```

- **--help (-h)**: Displays help information.
- **--version (-v)**: Shows the tool's version.
- **--model (-m)**: Sets a custom language model.
- **--output (-o)**: Sets a custom suffix for output files.
- **--token-usage (-t)**: Shows token-usage information.

### Interactive Menu

Run the tool without any arguments to start the interactive menu:

```bash
./EnglishFormatter
```

#### Menu Options

- **Format document**: Format text files.
- **Summarize document**: Summarize text files.
- **Paraphrase document**: Paraphrase text files.
- **Exit**: Exit the application.

#### Navigation

- Use the **Up** and **Down** arrow keys to navigate the menu.
- Press **Enter** to select an option.

#### Processing Files

1. Select an action from the menu.
2. When prompted, enter the names of the files you want to process, separated by spaces.
3. The tool will process each file and save the output with the specified suffix.

---

## Examples

### Formatting Documents

```bash
./EnglishFormatter --model gpt-3.5-turbo --output _formatted
```

- **Select**: Format document
- **Enter**: `document1.txt document2.txt`

**Output Files**:

- `document1.txt_formatted.txt`
- `document2.txt_formatted.txt`

### Summarizing a Document

```bash
./EnglishFormatter
```

- **Select**: Summarize document
- **Enter**: `report.txt`

**Output File**:

- `report.txt_modified.txt`

### Changing the Language Model

```bash
./EnglishFormatter --model gpt-4
```

- **Select**: Paraphrase document
- **Enter**: `essay.txt`

**Output File**:

- `essay.txt_modified.txt`

---

## Development

### Project Structure

- **cli_app/**

  - **src/**: Source code files.
    - `cli.cpp`: Entry point of the application.
    - `eng_format.cpp`: Contains the `eng_format` class responsible for processing files and making API calls.
    - `display.cpp`: Contains the `display` class for the interactive menu.
  - **include/**: Header files.
    - `eng_format.hpp`
    - `display.hpp`
    - `common.hpp`: Common includes and declarations.

- **vcpkg.json**: Manifest file for Vcpkg dependencies.

- **.env**: Contains environment variables like `API_KEY`.

### Dependencies Managed by Vcpkg

- **curl**: For making HTTP requests.
- **fmt**: For formatting strings.
- **nlohmann-json**: For JSON parsing.
- **dotenv-cpp**: For environment variable management.
- **GoogleTest**: For unit testing.

### Building the Project

Follow the instructions in the [Installation](#installation) section.

### Running Tests

After building the project, you can run the tests using:

```bash
ctest
```

---

## Contributing

Contributions are welcome! Please follow these steps:

1. **Fork the repository**.
2. **Create a new branch** for your feature or bug fix.
3. **Commit your changes** with clear and descriptive messages.
4. **Push to your fork** and submit a **Pull Request**.

For development and contribution guidelines, refer to [CONTRIBUTING.md](CONTRIBUTING.md).

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Contact

For any questions or suggestions, please open an issue on the GitHub repository or contact the maintainer.

---

## Acknowledgments

- **libcurl**: For easy HTTP requests.
- **nlohmann/json**: For JSON parsing.
- **dotenv-cpp**: For environment variable management.
- **fmt**: For formatting strings.
- **GoogleTest**: For unit testing.
- **OpenAI**: For providing advanced language models.

---

## Notes

- **API Usage**: Be aware of the API usage policies and costs associated with the language model provider.
- **Error Handling**: The tool includes error handling for missing files, API errors, and invalid inputs.
- **Extensibility**: The code is modular, making it easy to add new features or support for additional models.

---

## Frequently Asked Questions (FAQ)

### **Q1: I receive an error about the API key not being set.**

**A**: Ensure that your `.env` file is in the correct directory and contains the `API_KEY` variable. Alternatively, set the `API_KEY` as an environment variable in your system.

### **Q2: Can I use a different language model provider?**

**A**: Yes. Modify the `eng_format` class to adjust the API endpoint and parameters according to the provider's documentation.

### **Q3: How can I process files in a different format?**

**A**: Currently, the tool supports text files. To add support for other formats, extend the `read_file_content` and `save_file` methods in the `eng_format` class.

---

## Detailed Class Explanations

### **eng_format Class**

- **Purpose**: Handles file processing and API communication.
- **Key Methods**:
  - `process_files()`: Processes a list of files based on the selected action.
  - `make_api_call()`: Sends a request to the language model API.
  - `parse_response()`: Parses the API response to extract the result.
  - `read_file_content()`: Reads the content of a file.
  - `save_file()`: Writes the processed content to an output file.

### **display Class**

- **Purpose**: Provides an interactive menu for user interaction.
- **Key Methods**:
  - `navigate_menu()`: Handles menu navigation and selection.
  - `show_menu()`: Displays the menu options.
  - `handle_file_input()`: Prompts the user for file names.

---

## Extending the Tool

- **Adding New Actions**:
  1. Update the `menuItems` vector in `cli.cpp` with the new action.
  2. Implement a new method in `eng_format` to handle the action.
  3. Update the `process_files()` method to include the new action.

- **Customizing Prompts**:
  - Modify the prompt messages in the `handle_file_input()` method of the `display` class.

- **Enhancing Error Handling**:
  - Add additional checks and exception handling where necessary.

---

## Support

If you encounter any issues or have questions, please create an issue on the GitHub repository or contact the maintainer directly.

---