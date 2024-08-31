#pragma once

#include "ICommand.hpp"

class MuteCommand : public ICommand
{
public:
    MuteCommand() {}

    virtual void Execute(std::vector<std::string> args) override;
};