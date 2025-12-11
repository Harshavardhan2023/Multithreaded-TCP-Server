# Multithreaded Concurrent TCP Server

A C-based networking project that implements a multithreaded TCP server capable of handling multiple client connections simultaneously using POSIX Threads (`pthreads`).

## Overview

This project demonstrates socket programming and concurrency in C. Unlike iterative servers that block new connections while processing a current one, this server spawns a new detached thread for every incoming client request. The specific application logic involves receiving an array of integers from a client, sorting them server-side, and returning the sorted array.

## Features

* **Concurrency:** Handles multiple clients simultaneously using `pthread_create`.
* **Resource Management:** Uses `pthread_detach` to automatically reclaim thread resources upon completion, preventing memory leaks.
* **Socket Programming:** Implements standard TCP/IP communication flow (`socket` -> `bind` -> `listen` -> `accept`).
* **Algorithm:** Server performs QuickSort on incoming data streams.

## Technical Details

* **Language:** C
* **Libraries:** `<pthread.h>`, `<sys/socket.h>`, `<netinet/in.h>`
* **Architecture:** Client-Server model

## How to Compile and Run

### 1. Compile the Server

We must link the pthread library using `-pthread`.

```bash
gcc server.c -o server -pthread
```

### 2. Compile the Client

```bash
gcc client.c -o client
```

### 3. Run the Server

Open a terminal window and run the server. It will listen for incoming connections.

```bash
./server
```

### 4. Run the Client

Open a new terminal window (keep the server running in the first one) and run the client:

```bash
./client
```

To test concurrency, open multiple terminal windows and run `./client` in each one simultaneously.

## Usage Example & Expected Output

### Client Terminal (example interaction)

```
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
```

### Server Terminal Output (example)

```
TCP Concurrent Sorting Server Started
Listening on port 12347...

Client connected from 127.0.0.1:58420
Thread handling client connection...
Thread received count: 5
Thread received numbers: 99 12 5 1 70
Thread sorted numbers: 1 5 12 70 99
Thread sent sorted numbers back to client
```

> **Note:** The example addresses and port numbers are illustrative. Replace them with the actual client IP/port when testing across machines.

## Implementation Tips

* Ensure proper error checking for all socket calls (`socket`, `bind`, `listen`, `accept`, `recv`, `send`).
* Use `pthread_detach` immediately after `pthread_create` if you do not plan to `pthread_join` the child thread.
* Limit the maximum number of elements to a reasonable value (e.g., 100) to avoid large allocations on the stack.

---

If you want, I can also provide a compact `README.md` optimized for a CV or a short version suitable for GitHub project listings.
