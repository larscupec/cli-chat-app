#include "Debug.hpp"
#include "WindowManager.hpp"
#include <string>
#include <ctime>
#include "Window.hpp"

std::vector<std::string> Debug::messages;

void Debug::Log(std::string message) {
  message = "[" + GetCurrentDateTime() + "] " + message;
  messages.push_back(message);
  WindowManager::GetInstance()->GetDebugWindow()->PrintLine(message);
}

void Debug::LogError(std::string message) { Log("Error: " + message); }

void Debug::LogWarning(std::string message) { Log("Warning: " + message); }

// Taken from (lol)
// https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
const std::string Debug::GetCurrentDateTime() {
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
  // for more information about date/time format
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

  return buf;
}
