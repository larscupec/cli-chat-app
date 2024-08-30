#pragma once

#include "ICommand.hpp"

class UnbanCommand : public ICommand
{
public:
    UnbanCommand() {}

    virtual void Execute(std::vector<std::string> args) override;
};
