#pragma once
    
#include <string>

class JsonFileWriter
{
public:
  JsonFileWriter(std::string path);
  ~JsonFileWriter();

  template<typename T>
   void Write(std::string key, T value);

private:
  std::string path = "";
};    
