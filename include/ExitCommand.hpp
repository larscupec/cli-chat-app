#pragma once

#include "ICommand.hpp"

class App;

class ExitCommand : public ICommand {
public:
  ExitCommand(App *app) : app(app) {}

  virtual void Execute(std::vector<std::string> args) override;

private:
  App *app = nullptr;
};
