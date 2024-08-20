#include "StringHelper.hpp"
#include <algorithm>

// Taken from
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> StringHelper::SplitString(std::string string,
                                     std::string delimiter) {
  std::vector<std::string> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = string.find(delimiter)) != std::string::npos) {
    token = string.substr(0, pos);
    tokens.push_back(token);
    string.erase(0, pos + delimiter.length());
  }
  tokens.push_back(string);

  return tokens;
}

std::string StringHelper::TrimString(std::string string) {
  // Trim from start
  string.erase(string.begin(),
               std::find_if(string.begin(), string.end(), [](unsigned char ch) {
                 return !std::isspace(ch);
               }));
  // Trim from end
  string.erase(std::find_if(string.rbegin(), string.rend(),
                            [](unsigned char ch) { return !std::isspace(ch); })
                   .base(),
               string.end());
  return string;
}
