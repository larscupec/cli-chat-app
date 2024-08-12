#include "Debug.hpp"
#include <string>
#include <ctime>
#include "Console.hpp"

bool Debug::writeToConsole = false;

std::vector<std::string> Debug::messages;

void Debug::Log(std::string message) {
  messages.push_back("[" + GetCurrentDateTime() + "] " + message);

  if (writeToConsole) {
    Console::WriteLine(messages.back());
  }
}

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
