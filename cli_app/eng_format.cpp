#include "Eng_Format.hpp"


size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}


// Parse the **response** from the api 
std::string eng_format::parse_response(const std::string& response)
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
        throw std::runtime_error("Invalid API response");
    }
}

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
    jsonData["messages"] = { { {"role", "user"}, {"content", prompt} } };

    try
    {
        std::string jsonString = jsonData.dump();  // Attempt to dump the JSON
        std::cout << "JSON String: " << jsonString << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error during JSON serialization: " << e.what() << std::endl;
        throw;  // Re-throw the exception after logging
    }

    std::string jsonString = jsonData.dump();
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

void eng_format::save_file(const std::string& fileName, const std::string& content)
{
    std::ofstream outFile(fileName);
    if (!outFile.is_open())
    {
        throw std::runtime_error("Cannot open file for writing: " + fileName);
    }

    outFile << content;
    outFile.close();
}

eng_format::eng_format() {
    api_key = std::getenv("API_KEY");
    api_url = std::getenv("API_URL");
}

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

void eng_format::convert_file(std::string filename, std::string Action) {
    // 1. read the file contents and generate the data 
    std::string content = read_file_content(filename);
    // 2. generate prompt for the api call
    std::string prompt = format("Can you please {0} the text and please provide the {0} text only (not a single extra character). {1}", Action, content);
    //3. get response from api
    std::string response = make_api_call(prompt);
    //4. parse the response 
    std::string parsed_data = parse_response(response);
    //5. save it to file 
    filename += output_name;
    save_file(filename,parsed_data);
}

std::string eng_format::get_token_info(const std::string& response) {
    // Parse the JSON response
    auto json_response = json::parse(response);
    if (json_response.contains("usage")) {
        int prompt_tokens = json_response["usage"]["prompt_tokens"];
        int completion_tokens = json_response["usage"]["completion_tokens"];
        int total_tokens = json_response["usage"]["total_tokens"];

        // Format the token usage information
        return "Token usage:\nPrompt tokens: " + std::to_string(prompt_tokens) +
            "\nCompletion tokens: " + std::to_string(completion_tokens) +
            "\nTotal tokens: " + std::to_string(total_tokens);
    }
    else {
        return "Token usage information not found in response.";
    }
}