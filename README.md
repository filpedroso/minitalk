# Minitalk
A 42 School project that implements interprocess communication using UNIX signals.

## Overview
Minitalk consists of a **client** and a **server** programs that communicate with each other using `SIGUSR1` and `SIGUSR2` signals. 
The client sends a string message to the server, which then reconstructs and displays it.

## Installation and Compilation
To compile the project, run:

```sh
make
```
This will generate two executables:
- `server`
- `client`

## Usage
### 1. Start the Server
Run the server to get its Process ID (PID):

```sh
./server
```

Example output:
```
Server PID: 12345
```

### 2. Send a Message from the Client
Use the client to send a message to the server by providing the server's PID and the message:

```sh
./client 12345 "Hello, Minitalk!"
```

The server should receive and display:
```
Received: Hello, Minitalk!
```

The servers sends an aknowledgement message back to the client for every bit received and processed, and another when the entire message is already printed.

## How It Works
- The client converts each character into its binary representation.
- It sends bits one by one using `SIGUSR1` (1) and `SIGUSR2` (0).
- The server receives signals, reconstructs characters, and prints the message.
- The server must be running before sending a message.

## Features
✅ Sends messages of any length
✅ Handles signals asynchronously
✅ Implements error handling for invalid PIDs and message failures
✅ Uses **usleep()** for synchronization
✅ Unicode characters support 😎

## Cleaning Up
To remove compiled files:
```sh
make clean  # Removes object files
make fclean # Removes object files and executables
```
To recompile from scratch:
```sh
make re
```

## Testing
Try sending different messages and edge cases:
```sh
./client 12345 "42 is awesome!"
./client 12345 "Signals are fun 🎉"
./client 99999 "Invalid PID test"
```
