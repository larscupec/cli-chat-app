#include "Debug.hpp"
#include "Color.hpp"
#include "Window.hpp"
#include "WindowManager.hpp"
#include <ctime>
#include <string>

std::vector<std::string> Debug::messages;

// Taken from (lol)
// https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
const std::string GetCurrentDateTime() {
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
  // for more information about date/time format
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

  return buf;
}

void Debug::Log(std::string message) {
  message = "[" + GetCurrentDateTime() + "] " + message;
  messages.push_back(message);
  WindowManager::GetInstance()->GetDebugWindow()->PrintLine(message);
}

void Debug::LogError(std::string message) {
  WindowManager::GetInstance()->GetDebugWindow()->ActivateColor(Color::RED);
  Log("Error: " + message);
  WindowManager::GetInstance()->GetDebugWindow()->DeactivateColor(Color::RED);
}

void Debug::LogWarning(std::string message) {
  WindowManager::GetInstance()->GetDebugWindow()->ActivateColor(Color::YELLOW);
  Log("Warning: " + message);
  WindowManager::GetInstance()->GetDebugWindow()->DeactivateColor(
      Color::YELLOW);
}
