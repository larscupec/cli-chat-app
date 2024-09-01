#include "JsonFileReader.hpp"
#include <stdexcept>

JsonFileReader::JsonFileReader(std::string path) : path(path)
{
  std::ifstream file(path);

  if (!file.good()) {
    throw std::runtime_error("Could not open file '" + path + "'");
  }

  if (!json::accept(file))
  {
    throw std::runtime_error("'" + path + "' is not a valid JSON object");
  }

  file.seekg(0);
  file >> data;
}

template <typename T>
T JsonFileReader::Read(std::string key) {
  if (!data.contains(key)) {
    throw std::runtime_error("'" + path + "' does not contain an entry with the key '" + key + "'");
  }
  
  return data[key].get<T>();
}

template int JsonFileReader::Read<int>(std::string);
template std::string JsonFileReader::Read<std::string>(std::string);
