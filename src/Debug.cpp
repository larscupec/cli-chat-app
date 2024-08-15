#include "Debug.hpp"
#include "Color.hpp"
#include "DebugWindow.hpp"
#include <ctime>
#include <iostream>
#include <string>

std::vector<std::string> Debug::messages;

// Taken from (lol)
// https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
const std::string GetCurrentDateTime() {
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

  return buf;
}

void Debug::Log(std::string message) {
  message = "[" + GetCurrentDateTime() + "] " + message;
  messages.push_back(message);
  DebugWindow::PrintLine(message);
  std::cout << message << std::endl;
}

void Debug::LogError(std::string message) {
  DebugWindow::ActivateColor(Color::RED);
  Log("Error: " + message);
  DebugWindow::DeactivateColor(Color::RED);
}

void Debug::LogWarning(std::string message) {
  DebugWindow::ActivateColor(Color::YELLOW);
  Log("Warning: " + message);
  DebugWindow::DeactivateColor(Color::YELLOW);
}
