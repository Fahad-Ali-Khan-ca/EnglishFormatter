#include "Eng_Format.hpp"


// CURL WriteCallback function for writing response data into a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

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

// Function to make an API call with error handling
std::string eng_format::make_api_call(const std::string& prompt)
{
    CURL* curl = curl_easy_init();
    if (!curl)
    {
        throw std::runtime_error("Failed to initialize CURL");
    }

    // Prepare JSON payload
    json jsonData;
    jsonData["model"] = model;
    jsonData["messages"] = { {{"role", "user"}, {"content", prompt}} };

    std::string jsonString;
    try
    {
        jsonString = jsonData.dump(); // Attempt to dump the JSON
    }
    catch (const std::exception& e)
    {
        curl_easy_cleanup(curl);  // Clean up curl if error occurs
        throw std::runtime_error("Error during JSON serialization: " + std::string(e.what()));
    }

    std::string responseString;

    // Set up headers
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    std::string authHeader = "Authorization: Bearer " + api_key;
    headers = curl_slist_append(headers, authHeader.c_str());

    // Set CURL options
    curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

    // Perform the request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
    }

    // Clean up
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return responseString;
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

// Constructor to initialize API details
eng_format::eng_format()
{
    const char* apiKeyCStr = std::getenv("API_KEY");
    const char* apiUrlCStr = std::getenv("API_URL");

    if (apiKeyCStr == nullptr)
    {
        throw std::runtime_error("API key not found in environment variables.");
    }
    api_key = std::string(apiKeyCStr);  // Convert to std::string after null check

    if (apiUrlCStr == nullptr)
    {
        throw std::runtime_error("API URL not found in environment variables.");
    }
    api_url = std::string(apiUrlCStr);  // Convert to std::string after null check
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
        std::string response = make_api_call(prompt);

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
