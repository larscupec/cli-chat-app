#pragma once

#include <string>
#include <vector>

class Debug {
public:
  Debug() = delete;

  static void Log(std::string message);
  static void LogError(std::string message);
  static void LogWarning(std::string message);

private:
  static std::vector<std::string> messages;
};
