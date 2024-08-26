#pragma once

#include "ICommand.hpp"

class OpenWindowCommand : public ICommand
{
public:
    OpenWindowCommand() {}

    virtual void Execute(std::vector<std::string> args) override;
};