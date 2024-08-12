#include "JsonFileWriter.hpp"
#include <filesystem>
#include <fstream>
#include "json/json.hpp"
#include <string>

using nlohmann::json;

JsonFileWriter::JsonFileWriter(std::string path) : path(path) {}

JsonFileWriter::~JsonFileWriter() {}

template<typename T>
void JsonFileWriter::Write(std::string key, T value) {
  json target;

  if (std::filesystem::exists(path)) {
    std::ifstream file(path);
    file >> target;
    file.close();
  }

  target[key] = value;

  std::ofstream file(path);
  file << target;
  file.close();
}

template void JsonFileWriter::Write<int>(std::string, int);
template void JsonFileWriter::Write<std::string>(std::string, std::string);
