#pragma once

#include "ICommand.hpp"

class StopServerCommand : public ICommand {
public:
  StopServerCommand() {}

  virtual void Execute(std::vector<std::string> args) override;
};
