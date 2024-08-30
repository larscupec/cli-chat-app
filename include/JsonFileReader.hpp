#pragma once

#include <string>
#include "json/json.hpp"
#include <fstream>

using nlohmann::json;

class JsonFileReader
{
public:
  JsonFileReader(std::string path);
  ~JsonFileReader();

  template<typename T>
  T Read(std::string key);

  json ReadJson();

private:
  std::string path = "";
  std::ifstream file;
};    
