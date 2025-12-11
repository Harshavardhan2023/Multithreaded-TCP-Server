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
```bash
gcc server.c -o server -pthread
