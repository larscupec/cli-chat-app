#pragma once

#include "ICommand.hpp"

class ConnectCommand : public ICommand {
public:
  ConnectCommand() {}

  virtual void Execute(std::vector<std::string> args) override;
};
