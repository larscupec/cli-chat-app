#include "JsonFileReader.hpp"
#include "json/json.hpp"
#include <filesystem>
#include <fstream>
#include <stdexcept>

using nlohmann::json;

JsonFileReader::JsonFileReader(std::string path) : path(path) {}

JsonFileReader::~JsonFileReader() {}

template <typename T>
T JsonFileReader::Read(std::string key) {
  json target;

  if (!std::filesystem::exists(path)) {
    throw std::runtime_error("Could not open file '" + path + "'");
  }
  
  std::ifstream file(path);
  file >> target;
  file.close();

  if (!target.contains(key)) {
    throw std::runtime_error("'" + path + "' does not contain an entry with the key '" + key + "'");
  }
  
  return target[key].get<T>();
}

template int JsonFileReader::Read<int>(std::string);
template std::string JsonFileReader::Read<std::string>(std::string);
