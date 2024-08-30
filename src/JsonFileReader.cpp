#include "JsonFileReader.hpp"
#include <stdexcept>

JsonFileReader::JsonFileReader(std::string path) : path(path)
{
  file = std::ifstream(path);

  if (!file.good()) {
    throw std::runtime_error("Could not open file '" + path + "'");
  }
}

JsonFileReader::~JsonFileReader()
{
  file.close();
}

template <typename T>
T JsonFileReader::Read(std::string key) {
  json target;
  
  file >> target;

  if (!target.contains(key)) {
    throw std::runtime_error("'" + path + "' does not contain an entry with the key '" + key + "'");
  }
  
  return target[key].get<T>();
}

template int JsonFileReader::Read<int>(std::string);
template std::string JsonFileReader::Read<std::string>(std::string);

json JsonFileReader::ReadJson()
{
  json result;

  file >> result;

  return result;
}