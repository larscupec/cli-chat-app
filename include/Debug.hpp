#pragma once

#include <string>
#include <vector>

class Debug
{
public:
  static void Log(std::string message);

  static void SetWriteToConsole(bool state) { writeToConsole = state; }

private:
  static std::vector<std::string> messages;

  static bool writeToConsole;

  static const std::string GetCurrentDateTime();
};    
