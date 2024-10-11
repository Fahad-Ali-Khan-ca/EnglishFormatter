// common.hpp - To include the most common files
//
// 19-Sep-24  F.Khan         Created.
// 11-Oct-23  F.Khan		 Edited: Created Namespace to put the global
// variables in

#ifndef _COMMON_HPP_
#define _COMMON_HPP_
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <conio.h>
#endif
#include <filesystem>
#include <functional>
#include <map>
#include <sstream>
#include <stdexcept>

#include "json.hpp"  // Path based on where you saved json.hpp
// Declare variables as extern
// extern std::string model;
// extern std::string output_name;
namespace fs = std::filesystem;

namespace Config {
extern std::string model;
extern std::string output_name;
extern bool showTokenUsage;
extern const std::string TOOL_NAME;
extern const std::string TOOL_VERSION;
}  // namespace Config

using namespace Config;

using json =
    nlohmann::json;  // This alias is necessary for using 'json' directly

#endif  // !_COMMON_HPP_
