#include "JsonFileWriter.hpp"

JsonFileWriter::JsonFileWriter(std::string path) : path(path)
{
  file = std::ofstream(path);

  if (!file.good()) {
    throw std::runtime_error("Could not open file '" + path + "'");
  }
}

JsonFileWriter::~JsonFileWriter()
{
  file.close();
}

template<typename T>
void JsonFileWriter::Write(std::string key, T value) {
  json json;

  if (std::filesystem::exists(path)) {
    std::ifstream target(path);
    if (json::accept(target))
    {
      target.seekg(0);
      target >> json;
      target.close();
    }
  }

  json[key] = value;

  file << json;
}

template void JsonFileWriter::Write<int>(std::string, int);
template void JsonFileWriter::Write<std::string>(std::string, std::string);

void JsonFileWriter::Write(json json) {
  file << json;
}
