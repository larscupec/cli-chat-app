#pragma once

#include <string>
#include <vector>

class StringHelper {
public:
  StringHelper() = delete;

  static std::vector<std::string> SplitString(std::string string,
					      std::string delimiter);
  static std::string TrimString(std::string string);
};
