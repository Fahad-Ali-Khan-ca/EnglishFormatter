// cli.cpp - Function declarations for the eng_format class
//
// 09-Sep-24  F.Khan         Created.
// 11-Sep-24  F.Khan         Added Curl
// 14-Sep-24  F.Khan         Added nlohman json for parsing json objects
// 19-Sep-24  I.Parmar       Added token Info feature
#ifndef _ENG_FORMAT_H_
#define _ENG_FORMAT_H_
#include "common.hpp"
#define CURL_STATICLIB
#include "curl/curl.h"
#include "json.hpp"          // Path based on where you saved json.hpp
using json = nlohmann::json; // This alias is necessary for using 'json' directly

#ifdef _DEBUG
#pragma comment(lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment(lib, "curl/libcurl_a.lib")
#endif
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "advapi32.lib")

class eng_format
{
private:
    std::string api_url;
    std::string api_key;

public:
    eng_format();
    std::string read_file_content(const std::string &fileName);
    std::string make_api_call(const std::string &prompt);
    std::string parse_response(const std::string &response);
    void save_file(const std::string &fileName, const std::string &content);
    void convert_file(std::string filename, std::string Action);
    std::string get_token_info(const std::string &response);
};

#endif //_ENG_FORMAT_ H_
