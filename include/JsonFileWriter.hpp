#pragma once

#include <string>
#include "json/json.hpp"

using nlohmann::json;

class JsonFileWriter
{
public:
  JsonFileWriter(std::string path);
  ~JsonFileWriter();

  template<typename T>
  void Write(std::string key, T value);
  
  void Write(json json);

private:
  std::string path = "";
};    
