#include "Eng_Format.hpp"



// Parse the response from the API
std::string eng_format::parse_response(const std::string& response)
{
    try
    {
        json jsonResponse = json::parse(response);

        if (jsonResponse.contains("choices") && !jsonResponse["choices"].empty())
        {
            return jsonResponse["choices"][0]["message"]["content"].get<std::string>();
        }
        else if (jsonResponse.contains("error"))
        {
            std::string errorMessage = jsonResponse["error"]["message"].get<std::string>();
            throw std::runtime_error("API Error: " + errorMessage);
        }
        else
        {
            throw std::runtime_error("Invalid API response format");
        }
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error("Failed to parse API response: " + std::string(e.what()));
    }
}


// Function to save content to a file
void eng_format::save_file(const std::string& fileName, const std::string& content)
{
    std::ofstream outFile(fileName);
    if (!outFile.is_open())
    {
        throw std::runtime_error("Cannot open file for writing: " + fileName);
    }

    outFile << content;
    if (!outFile)
    {
        throw std::runtime_error("Error writing to file: " + fileName);
    }

    outFile.close();
}




// Read file content into a string
std::string eng_format::read_file_content(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + fileName);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Convert file using the API call and save the output
void eng_format::convert_file(std::string filename, std::string action)
{
    try
    {
        // 1. Read the file contents and generate the data
        std::string content = read_file_content(filename);

        // 2. Generate the prompt for the API call
        std::string prompt = format("Can you please {0} the text and provide the {0} text only. {1}", action, content);

        // 3. Get response from API
        std::string response = AI_api.make_api_call(prompt);

        // 4. Parse the response
        std::string parsed_data = parse_response(response);

        // 5. Save it to a file
        filename += output_name;
        save_file(filename, parsed_data);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error converting file " << filename << ": " << e.what() << std::endl;
        throw;
    }
}

// Function to get token usage information from the API response
std::string eng_format::get_token_info(const std::string& response)
{
    try
    {
        auto json_response = json::parse(response);
        if (json_response.contains("usage"))
        {
            int prompt_tokens = json_response["usage"]["prompt_tokens"];
            int completion_tokens = json_response["usage"]["completion_tokens"];
            int total_tokens = json_response["usage"]["total_tokens"];

            return "Token usage:\nPrompt tokens: " + std::to_string(prompt_tokens) +
                "\nCompletion tokens: " + std::to_string(completion_tokens) +
                "\nTotal tokens: " + std::to_string(total_tokens);
        }
        else
        {
            return "Token usage information not found in response.";
        }
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error("Failed to parse token info from response: " + std::string(e.what()));
    }
}
