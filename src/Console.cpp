#include "Console.hpp"
#include "ChatMode.hpp"
#include "CommandMode.hpp"
#include "Debug.hpp"
#include "Window.hpp"
#include "WindowManager.hpp"
#include "Client.hpp"

Console::Console(App *app, Client *client) : app(app), client(client) {
  // note: The console starts in Command Mode
  CommandMode *commandMode = new CommandMode(app, client, this);
  SetConsoleMode(commandMode);
}

Console::~Console() { delete consoleMode; }

std::string Console::ReadLine() {
  Window *window = WindowManager::GetInstance()->GetConsoleWindow();
  return window->ReadLine();
}

void Console::Clear() {
  WindowManager::GetInstance()->GetConsoleWindow()->Clear();
}

void Console::Edit() {
  const short leftmostCursorPositionX = 1;

  Window *consoleWindow = WindowManager::GetInstance()->GetConsoleWindow();
  WINDOW *window =
      WindowManager::GetInstance()->GetConsoleWindow()->GetWindow();

  keypad(window, true);
  noecho();

  short lastCharacterPositionX = leftmostCursorPositionX;

  int character;

  do {
    character = wgetch(window);

    int currentPositionX = consoleWindow->GetCursorPositionX();
    int currentPositionY = consoleWindow->GetCursorPositionY();

    switch (character) {
    case KEY_LEFT:
      if (currentPositionX > leftmostCursorPositionX) {
        wmove(window, currentPositionY, currentPositionX - 1);
      }
      break;
    case KEY_RIGHT:
      if (currentPositionX < lastCharacterPositionX) {
        wmove(window, currentPositionY, currentPositionX + 1);
      }
      break;
    case KEY_BACKSPACE:
      if (currentPositionX > leftmostCursorPositionX) {
        mvwdelch(window, currentPositionY, currentPositionX - 1);
        lastCharacterPositionX--;
      }
      break;
    case KEY_DC:
      if (currentPositionX < lastCharacterPositionX) {
        wdelch(window);
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
	Debug::LogError("Client: You must be connected to a server to enable Chat Mode");
	return;
      }
      ChatMode *chatMode = new ChatMode(client);
      SetConsoleMode(chatMode);
      break;
    }
    default:
      winsch(window, character);
      wmove(window, currentPositionY, currentPositionX + 1);
      lastCharacterPositionX = currentPositionX + 1;
      break;
    }
  } while (character != '\n');
  consoleWindow->Refresh();
}

void Console::ProcessInput() {
  Edit();
  std::string input = ReadLine();
  Clear();
  consoleMode->HandleInput(input);
}

void Console::SetConsoleMode(IConsoleMode *consoleMode) {
  delete Console::consoleMode;
  Console::consoleMode = consoleMode;
  Debug::Log("Console Mode set to " + consoleMode->ToString());
}
