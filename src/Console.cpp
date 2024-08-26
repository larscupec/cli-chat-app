#include "Console.hpp"
#include "App.hpp"
#include "ChatMode.hpp"
#include "Client.hpp"
#include "ClientCommandMode.hpp"
#include "ConsoleWindow.hpp"
#include "Debug.hpp"
#include "Window.hpp"
#include "WindowManager.hpp"
#include <ncurses/ncurses.h>

Console *Console::instance = nullptr;

Console *Console::GetInstance() {
  if (!instance) {
    instance = new Console();
  }
  return instance;
}

std::string Console::ReadInput() { return ConsoleWindow::ReadLine(); }

void Console::ClearInput() { ConsoleWindow::Clear(); }

void Console::Edit() {
  const int leftmostCursorPositionX = 0;

  Window *consoleWindow = ConsoleWindow::GetWindow();
  WINDOW *consolePad = consoleWindow->GetPad();

  keypad(consolePad, true);
  noecho();
  scrollok(consolePad, false);

  int lastCharacterPositionX = leftmostCursorPositionX;
  int previousInputIndex = previousInput.size() - 1;
  int character;

  do {
    character = wgetch(consolePad);

    int currentPositionX = consoleWindow->GetCursorPositionX();
    int currentPositionY = consoleWindow->GetCursorPositionY();

    switch (character) {
    case KEY_LEFT:
      if (currentPositionX > leftmostCursorPositionX) {
        wmove(consolePad, currentPositionY, currentPositionX - 1);
      }
      break;
    case KEY_RIGHT:
      if (currentPositionX < lastCharacterPositionX) {
        wmove(consolePad, currentPositionY, currentPositionX + 1);
      }
      break;
    case KEY_BACKSPACE:
      if (currentPositionX > leftmostCursorPositionX) {
        mvwdelch(consolePad, currentPositionY, currentPositionX - 1);
        lastCharacterPositionX--;
      }
      break;
    case KEY_DC:
      if (currentPositionX < lastCharacterPositionX) {
        wdelch(consolePad);
        lastCharacterPositionX--;
      }
      break;
    case ('Q' & 0x1F):
      // Ctrl+Q sets the console mode to Client Command Mode
      if (!App::GetInstance()->GetIsServer()) {
        SetConsoleMode(ClientCommandMode::GetInstance());
      }
      break;
    case ('A' & 0x1F):
      // Ctrl+A sets the console mode to Chat Mode
      if (!Client::GetInstance()->GetIsConnected()) {
        Debug::Log("You must be connected to a server to enable Chat Mode");
        return;
      }
      SetConsoleMode(ChatMode::GetInstance());
      break;
    case ('S' & 0x1F):
      // Ctrl+S focuses next window
      WindowManager::FocusNextWindow();
      break;
    case ('R' & 0x1F):
      // Ctrl+R redraws the focused window
      WindowManager::GetFocusedWindow()->Redraw();
      break;
    case ('X' & 0x1F):
      // Ctrl+X closes the focused window
      WindowManager::CloseFocusedWindow();
      break;
    case KEY_HOME:
      wmove(consolePad, currentPositionY, 0);
      break;
    case KEY_END:
      wmove(consolePad, currentPositionY, lastCharacterPositionX);
      break;
    case '\n':
      mvwaddch(consolePad, currentPositionY, lastCharacterPositionX, '\n');
      previousInputIndex = previousInput.size() - 1;
      break;
    case KEY_UP:
      if (WindowManager::GetFocusedWindow()->GetPad() == consolePad &&
          previousInputIndex >= 0) {
        consoleWindow->Clear();
        consoleWindow->Print(previousInput[previousInputIndex]);
	lastCharacterPositionX = previousInput[previousInputIndex].size();
	previousInputIndex--;
	if (previousInputIndex < 0) {
	  previousInputIndex = 0;
	}
      } else {
        WindowManager::GetFocusedWindow()->Scroll(-1);
      }
      break;
    case KEY_DOWN:
      if (WindowManager::GetFocusedWindow()->GetPad() == consolePad &&
          previousInputIndex < previousInput.size()) {
        consoleWindow->Clear();
	previousInputIndex++;
	if (previousInputIndex > previousInput.size() - 1) {
	  previousInputIndex = previousInput.size() - 1;
	  break;
	}
	consoleWindow->Print(previousInput[previousInputIndex]);
	lastCharacterPositionX = previousInput[previousInputIndex].size();
      }
      else {
        WindowManager::GetFocusedWindow()->Scroll(1);
      }
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
      winsch(consolePad, character);
      wmove(consolePad, currentPositionY, currentPositionX + 1);
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
  previousInput.push_back(input);
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
