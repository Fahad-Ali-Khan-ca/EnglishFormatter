
# EnglishFormatter

EnglishFormatter is a command-line tool designed to help users format, summarize, or paraphrase text documents using advanced language models. It provides an interactive menu-driven interface and supports customization through command-line arguments.

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

- **C++17 or higher**: The project requires a compiler that supports C++17.
- **libcurl**: For making HTTP requests to the API.
- **nlohmann/json**: For JSON parsing and serialization.
- **dotenv-cpp**: To manage environment variables from a `.env` file.
- **An API Key**: You'll need an API key from the language model provider (e.g., OpenAI).

---

## Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/EnglishFormatter.git
   cd EnglishFormatter
   ```

2. **Install Dependencies**

   - **libcurl**

     - **Windows**: Download the pre-built binaries from the [official website](https://curl.se/windows/).
     - **Unix/Linux**:

       ```bash
       sudo apt-get install libcurl4-openssl-dev
       ```

   - **nlohmann/json**

     - Download the single-header `json.hpp` file from the [GitHub repository](https://github.com/nlohmann/json/releases).

   - **dotenv-cpp**

     - Clone the repository:

       ```bash
       git clone https://github.com/motdotla/dotenv-cpp.git
       ```

     - Include the `dotenv.h` and `dotenv.cpp` in your project.

3. **Set Up the .env File**

   Create a `.env` file in the project's root directory:

   ```
   API_KEY=your_api_key_here
   ```

   Replace `your_api_key_here` with your actual API key.

4. **Build the Project**

   - **Using g++**

     ```bash
     g++ -std=c++17 -o EnglishFormatter main.cpp eng_format.cpp display.cpp dotenv.cpp -lcurl -pthread
     ```

   - **Using Visual Studio**

     - Open the solution file or create a new project.
     - Add all source files to the project.
     - Link against `libcurl` and ensure all dependencies are included.
     - Build the project.

---

## Configuration

- **API Key**

  The tool requires an API key to access the language model API. Set the `API_KEY` in the `.env` file or as an environment variable.

- **Default Model**

  The default language model is `llama3-8b-8192`. You can change this using the `--model` command-line option.

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
  -m, --model MODEL     Specify the language model to use (default: llama3-8b-8192)
  -o, --output SUFFIX   Specify the output file suffix (default: _modified)
```

- **--help (-h)**: Displays help information.
- **--version (-v)**: Shows the tool's version.
- **--model (-m)**: Sets a custom language model.
- **--output (-o)**: Sets a custom suffix for output files.

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

- **main.cpp**: Entry point of the application.
- **eng_format.hpp/cpp**: Contains the `eng_format` class responsible for processing files and making API calls.
- **display.hpp/cpp**: Contains the `display` class for the interactive menu.
- **dotenv.h/cpp**: Manages environment variables.
- **common.hpp**: Common includes and declarations.
- **.env**: Contains environment variables like `API_KEY`.

### Building from Source

Ensure all dependencies are installed and build the project using your preferred compiler.

---

## Contributing

Contributions are welcome! Please follow these steps:

1. **Fork the Repository**
2. **Create a Feature Branch**

   ```bash
   git checkout -b feature/YourFeature
   ```

3. **Commit Changes**

   ```bash
   git commit -am 'Add new feature'
   ```

4. **Push to Branch**

   ```bash
   git push origin feature/YourFeature
   ```

5. **Create a Pull Request**

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Contact

For any questions or suggestions, please open an issue or contact the maintainer.

---

## Acknowledgments

- **libcurl**: For easy HTTP requests.
- **nlohmann/json**: For JSON parsing.
- **dotenv-cpp**: For environment variable management.
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
  1. Update the `menuItems` vector in `main.cpp` with the new action.
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
