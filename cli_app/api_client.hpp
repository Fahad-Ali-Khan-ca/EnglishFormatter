// api_client.hpp - make api calls to models
//
// 11-Oct-24	F.khan		Created.

#ifndef _API_CLIENT_H_
#define _API_CLIENT_H_
#define CURL_STATICLIB
#include "curl/curl.h"
#ifdef _DEBUG
#pragma comment(lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment(lib, "curl/libcurl_a.lib")
#endif
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "advapi32.lib")

#include "common.hpp"

using json =
    nlohmann::json;  // This alias is necessary for using 'json' directly

class api_client {
 private:
  std::string api_url;
  std::string api_key;

 public:
  api_client();
  void set_api_url(const std::string& api_url);
  void set_api_key(const std::string& api_key);
  std::string make_api_call(const std::string& prompt);
  static size_t WriteCallback(void* contents, size_t size, size_t nmemb,
                              void* userp);
};

#endif  // !_API_CLIENT_H_
