#include "Console.hpp"
#include "ChatMode.hpp"
#include "Client.hpp"
#include "CommandMode.hpp"
#include "Debug.hpp"
#include "Window.hpp"
#include "WindowManager.hpp"

Console::Console(App *app, Client *client) : app(app), client(client) {
  // note: The console starts in Command Mode
  CommandMode *commandMode = new CommandMode(app, client, this);
  SetConsoleMode(commandMode);
}

Console::~Console() { delete consoleMode; }

std::string Console::ReadInput() {
  return WindowManager::GetInstance()->GetConsoleWindow()->ReadLine();
}

void Console::ClearInput() {
  WindowManager::GetInstance()->GetConsoleWindow()->ClearLine();
}

void Console::Edit() {
  const short leftmostCursorPositionX = 1;

  Window *consoleWindow = WindowManager::GetInstance()->GetConsoleWindow();
  WINDOW *pad = WindowManager::GetInstance()->GetConsoleWindow()->GetPad();

  keypad(pad, true);
  noecho();

  short lastCharacterPositionX = leftmostCursorPositionX;

  int character;

  do {
    character = wgetch(pad);

    int currentPositionX = consoleWindow->GetCursorPositionX();
    int currentPositionY = consoleWindow->GetCursorPositionY();

    switch (character) {
    case KEY_LEFT:
      if (currentPositionX > leftmostCursorPositionX) {
        wmove(pad, currentPositionY, currentPositionX - 1);
      }
      break;
    case KEY_RIGHT:
      if (currentPositionX < lastCharacterPositionX) {
        wmove(pad, currentPositionY, currentPositionX + 1);
      }
      break;
    case KEY_BACKSPACE:
      if (currentPositionX > leftmostCursorPositionX) {
        mvwdelch(pad, currentPositionY, currentPositionX - 1);
        lastCharacterPositionX--;
      }
      break;
    case KEY_DC:
      if (currentPositionX < lastCharacterPositionX) {
        wdelch(pad);
        lastCharacterPositionX--;
      }
      break;
    case ('Q' & 0x1F): {
      // Ctrl+Q sets the console mode to Command Mode
      CommandMode *commandMode = new CommandMode(app, client, this);
      SetConsoleMode(commandMode);
      break;
    }
    case ('W' & 0x1F): {
      // Ctrl+W sets the console mode to Chat Mode
      if (!client->GetIsConnected()) {
        Debug::Log("You must be connected to a server to enable Chat Mode");
        return;
      }
      ChatMode *chatMode = new ChatMode(client);
      SetConsoleMode(chatMode);
      break;
    }
    case ('S' & 0x1F):
      // Ctrl+S switches the focus on windows
      WindowManager::GetInstance()->FocusNextWindow();
      break;
    case KEY_UP:
      WindowManager::GetInstance()->GetFocusedWindow()->Scroll(-1);
      break;
    case KEY_DOWN:
      WindowManager::GetInstance()->GetFocusedWindow()->Scroll(1);
      break;
    default:
      winsch(pad, character);
      wmove(pad, currentPositionY, currentPositionX + 1);
      lastCharacterPositionX = currentPositionX + 1;
      break;
    }
    consoleWindow->Refresh();
  } while (character != '\n');
}

void Console::ProcessInput() {
  Edit();
  std::string input = ReadInput();
  ClearInput();
  consoleMode->HandleInput(input);
}

void Console::SetConsoleMode(IConsoleMode *consoleMode) {
  delete Console::consoleMode;
  Console::consoleMode = consoleMode;
  Debug::Log("Console Mode set to " + consoleMode->ToString());
}
