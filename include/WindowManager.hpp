#pragma once

class Window;

class WindowManager {
public:
  ~WindowManager();

  static WindowManager *GetInstance();

  Window *GetChatWindow() { return chatWindow; }
  Window *GetConsoleWindow() { return consoleWindow; }
  Window *GetDebugWindow() { return debugWindow; }

private:
  WindowManager();
  static WindowManager *instance;

  Window *chatWindow = nullptr;
  Window *consoleWindow = nullptr;
  Window *debugWindow = nullptr;
};
