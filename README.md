# cli-chat-app

A simple chat app that runs in your terminal.

![Imgur Image](https://imgur.com/HPxQdCz.jpg)

## Instalation

Once I build it with static libs you will just have to run the .exe file and have fun, but until then... you can't! Yes, there is no download for now. Best you can do is compile the source code yourself if you want it that bad.

## Usage

Currently the app can be run with two optional command line arguments: `--server` or `-S` and `--host` or `-H`. The `--server` argument tells the cli-chat-app to run in server mode (without the UI). This is useful if you want to have a dedicated server. The `--host` argument makes it run the server with the UI so that you can use the app and host a server simultaneously.

### clientInfo.json

The "clientInfo.json" contains information about you such as your:

 - username

And that's it! For now. This is the username with which you will join servers.

### Console Modes

While using the cli-chat-app you will be interacting with it through a console at the bottom of the screen. The Console is used to execute commands and send chat messages. Currently there are two modes, Command Mode and Chat Mode. You can switch between these two modes with ease by pressing `Ctrl+Q`, which activates the Command Mode, or `Ctrl+A`, which activates the Chat Mode.

While In Chat Mode everything you type will be processed as a chat message and sent to the server. When in Command Mode you can execute commands. The **command list** is given below:

#### Client commands:

 - `connect <ip> <port>`
	 - Used for connecting to a server with the ip address `<ip>` on port `<port>`.
 - `leave`
	 - Used for disconnecting from the server.

#### Server commands:

- `stop`
	- Stops the server.

#### General commands:

 - `exit`
	 - Closes the application.

## Dependencies

- NCurses (https://invisible-island.net/ncurses/)
- ENet Reliable UDP networking library (http://enet.bespin.org/)
- Niels Lohmann's JSON for Modern C++ (https://json.nlohmann.me/)

## TODO

 - Add window scrolling
 - Add command history
 - More server commands (kick, ban, unban, mute)
 - Closing and opening windows

## Disclaimer

Not in any way affiliated with Razer Inc.
