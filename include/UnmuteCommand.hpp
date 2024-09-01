#pragma once

#include "ICommand.hpp"

class UnmuteCommand : public ICommand
{
public:
    UnmuteCommand() {}

    virtual void Execute(std::vector<std::string> args) override;
};