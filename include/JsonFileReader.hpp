#pragma once

#include <string>

class JsonFileReader
{
public:
  JsonFileReader(std::string path);
  ~JsonFileReader();

  template<typename T>
  T Read(std::string key);

private:
  std::string path = "";
};    
