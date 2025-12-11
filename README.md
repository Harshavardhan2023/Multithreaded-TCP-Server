# Multithreaded Concurrent TCP Server

A C-based networking project that implements a multithreaded TCP server capable of handling multiple client connections simultaneously using POSIX Threads (pthreads).

## Overview

This project demonstrates socket programming and concurrency in C. Unlike iterative servers that block new connections while processing a current one, this server spawns a new detached thread for every incoming client request. The specific application logic involves receiving an array of integers from a client, sorting them server-side, and returning the sorted array.

## Features
- **Concurrency:** Handles multiple clients simultaneously using `pthread_create`.
- **Resource Management:** Uses `pthread_detach` to automatically reclaim thread resources upon completion, preventing memory leaks.
- **Socket Programming:** Implements standard TCP/IP communication flow (Socket -> Bind -> Listen -> Accept).
- **Algorithm:** Server performs QuickSort on incoming data streams.

## Technical Details
- **Language:** C
- **Libraries:** `<pthread.h>`, `<sys/socket.h>`, `<netinet/in.h>`
- **Architecture:** Client-Server model

## How to Compile and Run

### 1. Compile the Server
We must link the pthread library using `-pthread`.
gcc server.c -o server -pthread

### 2. Compile the Client
gcc client.c -o client

### 3. Run the Server
Open a terminal window and run the server. It will listen for incoming connections.
./server

### 4. Run the Client
Open a new terminal window (keep the server running in the first one) and run the client:
./client

To test concurrency, you can open multiple terminal windows and run ./client in each one simultaneously.

Usage Example & Expected Output
Client Terminal Input/Output:
Plaintext

Connected to TCP Concurrent Sorting Server (Port 12347)
Enter the number of elements to sort (max 100): 5
Enter 5 unsorted numbers:
Number 1: 99
Number 2: 12
Number 3: 5
Number 4: 1
Number 5: 70

Sent 5 numbers to concurrent server for sorting...

Received sorted numbers from concurrent server:
1 5 12 70 99 
Server Terminal Output:
Plaintext

TCP Concurrent Sorting Server Started
Listening on port 12347...

Client connected from 127.0.0.1:58420
Thread handling client connection...
Thread received count: 5
Thread received numbers: 99 12 5 1 70 
Thread sorted numbers: 1 5 12 70 99 
Thread sent sorted numbers back to client
