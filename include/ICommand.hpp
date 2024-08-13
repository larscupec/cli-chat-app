#pragma once

#include <string>
#include <vector>

class ICommand {
public:
  virtual ~ICommand() {}
  virtual void Execute(std::vector<std::string> args) = 0;
};
