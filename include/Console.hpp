#pragma once

#include "IConsoleMode.hpp"
#include <string>
#include <vector>

class Console {
public:
  ~Console() {}

  static Console *GetInstance();

  void ProcessInput();

  void SetConsoleMode(IConsoleMode *consoleMode);

private:
  Console() {}

  static Console *instance;
  
  IConsoleMode *consoleMode = nullptr;

  std::string ReadInput();
  void ClearInput();
  void Edit();

  std::vector<std::string> previousInput;
};
