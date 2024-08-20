#pragma once

#include "ICommand.hpp"

class LeaveCommand : public ICommand {
public:
  LeaveCommand() {}

  virtual void Execute(std::vector<std::string> args) override;
};
