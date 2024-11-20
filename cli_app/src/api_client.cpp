// api_client.cpp -- Header file for api_client class
//
// 11-Oct-24	F.Khan		Created.
#include "api_client.hpp"
api_client::api_client() {
  const char* apiKeyCStr = std::getenv("API_KEY");
  const char* apiUrlCStr = std::getenv("API_URL");
  if (apiKeyCStr == nullptr) {
    throw std::runtime_error("API key not found in environment variables.");
  }
  api_key = std::string(apiKeyCStr);  // Convert to std::string after null check
  if (apiUrlCStr == nullptr) {
    throw std::runtime_error("API URL not found in environment variables.");
  }
  api_url = std::string(apiUrlCStr);  // Convert to std::string after null check
}
void api_client::set_api_url(const std::string& api_url) {
  this->api_url = api_url;
}
void api_client::set_api_key(const std::string& api_key) {
  this->api_key = api_key;
}
// Function to make an API call with error handling
std::string api_client::make_api_call(const std::string& prompt) {
  CURL* curl = curl_easy_init();
  if (!curl) {
    throw std::runtime_error("Failed to initialize CURL");
  }
  // Prepare JSON payload
  json jsonData;
  jsonData["model"] = Config::model;
  jsonData["messages"] = {{{"role", "user"}, {"content", prompt}}};
  std::string jsonString;
  try {
    jsonString = jsonData.dump();  // Attempt to dump the JSON
  } catch (const std::exception& e) {
    curl_easy_cleanup(curl);  // Clean up curl if error occurs
    throw std::runtime_error("Error during JSON serialization: " +
                             std::string(e.what()));
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
  if (res != CURLE_OK) {
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    throw std::runtime_error("CURL request failed: " +
                             std::string(curl_easy_strerror(res)));
  }
  // Clean up
  curl_easy_cleanup(curl);
  curl_slist_free_all(headers);
  return responseString;
}
// CURL WriteCallback function for writing response data into a string
size_t api_client::WriteCallback(void* contents, size_t size, size_t nmemb,
                                 void* userp) {
  size_t totalSize = size * nmemb;
  std::string* response = static_cast<std::string*>(userp);
  response->append(static_cast<char*>(contents), totalSize);
  return totalSize;
}