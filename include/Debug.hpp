#pragma once

#include <string>
#include <vector>

class Debug {
public:
  Debug() = delete;

  static void Log(std::string message);
  static void LogError(std::string message);
  static void LogWarning(std::string message);

  static size_t GetMessageCount() { return messages.size(); }
  static const std::vector<std::string>& GetMessages() { return messages; }

private:
  static std::vector<std::string> messages;
};
