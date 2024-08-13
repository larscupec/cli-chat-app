#pragma once

#include <string>

class IConsoleMode
{
public:
  virtual ~IConsoleMode() {}
  virtual void HandleInput(std::string input) = 0;
  virtual std::string ToString() = 0;
};    
