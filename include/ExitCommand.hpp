#pragma once

#include "ICommand.hpp"

class ExitCommand : public ICommand {
public:
  ExitCommand() {}

  virtual void Execute(std::vector<std::string> args) override;
};
