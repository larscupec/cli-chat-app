#include "JsonFileWriter.hpp"
#include <filesystem>
#include <fstream>
#include "json/json.hpp"
#include <string>

JsonFileWriter::JsonFileWriter(std::string path) : path(path) {}

JsonFileWriter::~JsonFileWriter() {}

template<typename T>
void JsonFileWriter::Write(std::string key, T value) {
  json json;

  if (std::filesystem::exists(path)) {
    std::ifstream target(path);
    target >> json;
    target.close();
  }

  json[key] = value;

  std::ofstream target(path);
  target << json;
  target.close();
}

template void JsonFileWriter::Write<int>(std::string, int);
template void JsonFileWriter::Write<std::string>(std::string, std::string);

void JsonFileWriter::Write(json json) {
  std::ofstream target(path);
  target << json;
  target.close();
}
