// cli.cpp - Function declarations for the eng_format class
// 
// 09-Sep-24  F.Khan         Created.
// 11-Sep-24  F.Khan         Added Curl
// 14-Sep-24  F.Khan         Added nlohman json for parsing json objects
#ifndef _ENG_FORMAT_H_
#define _ENG_FORMAT_H_
#include "common.hpp"
#define CURL_STATICLIB
#include "curl/curl.h"
#include "json.hpp"  // Path based on where you saved json.hpp
using json = nlohmann::json;  // This alias is necessary for using 'json' directly


#ifdef _DEBUG
#pragma comment (lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment (lib, "curl/libcurl_a.lib")
#endif
#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")


class eng_format
{
private:

public:
    eng_format(/* args */);
    ~eng_format();
    void api_call();
    void save_file();

};

#endif //_ENG_FORMAT_ H_
