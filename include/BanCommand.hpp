#pragma once

#include "ICommand.hpp"

class BanCommand : public ICommand {
public:
  BanCommand() {}

  virtual void Execute(std::vector<std::string> args) override;
};
