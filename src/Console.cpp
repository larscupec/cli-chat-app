#include "Console.hpp"
#include "ChatMode.hpp"
#include "Client.hpp"
#include "ClientCommandMode.hpp"
#include "ConsoleWindow.hpp"
#include "Debug.hpp"
#include "Window.hpp"
#include <ncurses/ncurses.h>
#include "App.hpp"

Console *Console::instance = nullptr;

Console *Console::GetInstance() {
  if (!instance) {
    instance = new Console();
  }
  return instance;
}

std::string Console::ReadInput() { return ConsoleWindow::ReadLine(); }

void Console::ClearInput() { ConsoleWindow::ClearLine(); }

void Console::Edit() {
  const int leftmostCursorPositionX = 0;

  Window *consoleWindow = ConsoleWindow::GetWindow();
  WINDOW *pad = consoleWindow->GetPad();

  keypad(pad, true);
  noecho();
  scrollok(pad, false);

  int lastCharacterPositionX = leftmostCursorPositionX;

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
      // Ctrl+Q sets the console mode to Client Command Mode
      if (!App::GetInstance()->GetIsServer()) {
	SetConsoleMode(ClientCommandMode::GetInstance());
      }
      break;
    }
    case ('A' & 0x1F): {
      // Ctrl+A sets the console mode to Chat Mode
      if (!Client::GetInstance()->GetIsConnected()) {
        Debug::Log("You must be connected to a server to enable Chat Mode");
        return;
      }
      SetConsoleMode(ChatMode::GetInstance());
      break;
    }
    case KEY_HOME:
      wmove(pad, currentPositionY, 0);
      break;
    case KEY_END:
      wmove(pad, currentPositionY, lastCharacterPositionX);
      break;
    case '\n':
      mvwaddch(pad, currentPositionY, lastCharacterPositionX, '\n');
      break;
    case KEY_PPAGE:
    case KEY_NPAGE:
    case KEY_IC:
    case KEY_EXIT:
    case KEY_F(0):
    case KEY_F(1):
    case KEY_F(2):
    case KEY_F(3):
    case KEY_F(4):
    case KEY_F(5):
    case KEY_F(6):
    case KEY_F(7):
    case KEY_F(8):
    case KEY_F(9):
    case KEY_F(10):
    case KEY_F(11):
    case KEY_F(12):
      break;
    default:
      winsch(pad, character);
      wmove(pad, currentPositionY, currentPositionX + 1);
      if (consoleWindow->GetCursorPositionX() > lastCharacterPositionX) {
        lastCharacterPositionX = currentPositionX + 1;
      } else {
        lastCharacterPositionX++;
      }
      break;
    }
    consoleWindow->Refresh();
  } while (character != '\n');
}

void Console::ProcessInput() {
  Edit();
  std::string input = ReadInput();
  ClearInput();
  if (input.size() == 0) {
    return;
  }
  consoleMode->HandleInput(input);
}

void Console::SetConsoleMode(IConsoleMode *consoleMode) {
  this->consoleMode = consoleMode;
  Debug::Log("Console Mode set to " + consoleMode->ToString());
}
