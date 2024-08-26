#include "OpenWindowCommand.hpp"
#include "Debug.hpp"
#include "WindowManager.hpp"

void OpenWindowCommand::Execute(std::vector<std::string> args)
{
    if (args.size() != 1)
    {
        Debug::LogError("Invalid number of arguments " + std::to_string(args.size()) + " (open)");
        return;
    }

    std::string windowTitle = args.front();

    WindowManager::OpenWindow(windowTitle);
}