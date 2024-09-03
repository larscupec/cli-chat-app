#pragma once

#include "ConsoleMode.hpp"
#include <string>
#include <vector>

class Console {
public:
  ~Console() {}

  static Console *GetInstance();

  void ProcessInput();

  void SetMode(ConsoleMode *mode);

private:
  Console() {}

  static Console *instance;
  
  ConsoleMode *mode = nullptr;

  std::string ReadInput();
  void ClearInput();
  void Edit();

  std::vector<std::string> previousInput;
};
