#pragma once

#include "ICommand.hpp"
#include <enet/enet.h>

class KickCommand : public ICommand {
public:
  KickCommand() {}

  virtual void Execute(std::vector<std::string> args) override;
};
