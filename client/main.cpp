#include <iostream>
#include <ncurses.h>
#include <vector>
#include <thread>
#include <boost/algorithm/string.hpp>

#include "client.h"
#include "chatWindow.h"

Client client;

bool programRunning = true;

void processAppCommand(std::string command, std::vector<std::string> args)
{
    if (command == "exit") {
        // Exit application
        programRunning = false;
    }
    else if (command == "connect") {
        if (args.size() < 1) printw("Invalid server address\n");
        else {
            std::vector<std::string> ipport;
            boost::split(ipport, args[0], boost::is_any_of(":"));
            client.connect(ipport[0], std::stoi(ipport[1]));
        }
    }
    else {
        printw("Unknow command\n");
    }
}

int main()
{
    ChatWindow cWin;

    client.cWin = &cWin;
    cWin.client = &client;

    if (client.init() != 0) return 1;

    // Load the client info
    client.loadClientInfo();

    // Init ncurses window and show greeting message
    initscr();
    clear();
    keypad(stdscr, TRUE);
    printw("Program started... Hello %s!\n", client.username.c_str());

    if (client.autoconnectIp != "") {
        std::vector<std::string> vec;
        vec.push_back(client.autoconnectIp);
        processAppCommand("connect", vec);
    }

    // Start the main program loop
    while (programRunning)
    {
        char command[50];

        if (client.connected) {
            cWin.init();

            // Start the message loop (for receiving messages)
            std::thread t1(&Client::update, &client);

            // Enter chat room
            wprintw(cWin.scanWin, ">>> ");
            
            while (client.connected)
            {
                cWin.update();
            }

            // End message loop thread
            t1.join();

            cWin.destroy();

            clear();
            printw("You left the server.\n");
        }
        else {
            echo();
            getstr(command);

            std::vector<std::string> args;
            boost::split(args, command, boost::is_any_of(" "));
            std::string cmd(command);
            if (args.size() > 1) {
                cmd = args[0];
                // Remove the first command
                args[0] = args[args.size() - 1];
                args.pop_back();
            }
            
            processAppCommand(cmd, args);
        }
    }

    endwin();

    client.destroy();

    return 0;
}