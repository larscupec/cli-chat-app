# cli-chat-app

A simple chat app that runs in your terminal.

![Imgur Image](https://imgur.com/HPxQdCz.jpg)

## Installation

Download the release versoin for your configuration and run the `clichatapp.exe`. That's it!

## Usage

Currently the app can be run with two optional command line arguments: `-server` or `-s` and `-host` or `-h`. The `-server` argument tells the cli-chat-app to run in server mode. This is useful if you want to have a dedicated server. The `-host` argument makes it so you can use the app as a client and host a server simultaneously.

### clientInfo.json

The "clientInfo.json" contains information about you such as your:

 - username

And that's it! For now. This is the username with which you will join servers.

### Console Modes

While using the cli-chat-app you will be interacting with it through a console at the bottom of the screen. The Console is used to execute commands and send chat messages. Currently there are two modes, Command Mode and Chat Mode. You can switch between these two modes with ease by pressing `Ctrl+Q`, which activates the Command Mode, or `Ctrl+A`, which activates the Chat Mode.

While In Chat Mode everything you type will be processed as a chat message and sent to the server. When in Command Mode you can execute commands. The **command list** is given below:

### Client commands:

 - `connect <ip> <port>`
	 - Used for connecting to a server with the IP address `<ip>` on port `<port>`.
 - `leave`
	 - Used for disconnecting from the server.

### Server commands:

 - `stop`
	 - Stops the server.
 - `kick <username>`
	 - Disconnects a user with the specified username from the server.
 - `ban <username>`
	 - Bans a user with the specified username from the server.
 - `unban <ip (decimal)>`
	 - Removes the specified `<ip>` from the ban list.
 - `mute <username> <seconds (optional)>`
	 - Mutes the user with the specified username for the specified amount of seconds. If no time value is passed the user is muted indefinitely.
 - `unmute <username>`
	 - Unmutes the user with the specified username.

### General commands:

 - `exit`
	 - Closes the application.
 - `open <window>`
	 - Opens the window with the title `<window>`.

### Shortcuts

There are also keyboard shortcuts for other functions, for example:

 - `Ctrl+S` - Switches the focus on windows. The focused window has a highlighted title.
 - `Ctrl+X` - Closes the focused window.
 - `Ctrl+R` - Redraws the focused window.

## Dependencies

 - NCurses (https://invisible-island.net/ncurses/)
 - ENet Reliable UDP networking library (http://enet.bespin.org/)
 - Niels Lohmann's JSON for Modern C++ (https://json.nlohmann.me/)

## Disclaimer

Not in any way affiliated with Razer Inc.
