#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdint.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 12347
#define BUFFER_SIZE 1024
#define MAX_NUMBERS 100

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Thread function to handle each client
DWORD WINAPI client_handler(LPVOID arg) {
    SOCKET client_sock = (SOCKET)(uintptr_t)arg;
    int numbers[MAX_NUMBERS];
    int count, i;
    int bytes_received;

    printf("Thread handling client connection...\n");

    // Receive count
    bytes_received = recv(client_sock, (char*)&count, sizeof(count), 0);
    if (bytes_received <= 0) {
        printf("Failed to receive count or client disconnected\n");
        closesocket(client_sock);
        return 0;
    }
    printf("Thread received count: %d\n", count);

    // Receive numbers
    bytes_received = recv(client_sock, (char*)numbers, count * sizeof(int), 0);
    if (bytes_received <= 0) {
        printf("Failed to receive numbers\n");
        closesocket(client_sock);
        return 0;
    }

    printf("Thread received numbers: ");
    for (i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Sort the numbers
    qsort(numbers, count, sizeof(int), compare);

    printf("Thread sorted numbers: ");
    for (i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Send sorted numbers back
    send(client_sock, (char*)numbers, count * sizeof(int), 0);
    printf("Thread sent sorted numbers back to client\n\n");

    closesocket(client_sock);
    return 0;
}

int main() {
    SOCKET server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len;
    HANDLE thread_handle;
    WSADATA wsaData;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create TCP socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == INVALID_SOCKET) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(server_sock);
        WSACleanup();
        return 1;
    }

    // Listen for connections
    if (listen(server_sock, 5) == SOCKET_ERROR) {
        printf("Listen failed: %d\n", WSAGetLastError());
        closesocket(server_sock);
        WSACleanup();
        return 1;
    }

    printf("TCP Concurrent Sorting Server Started\n");
    printf("Listening on port %d...\n\n", SERVER_PORT);

    while (1) {
        client_addr_len = sizeof(client_addr);
        
        // Accept client connection
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_sock == INVALID_SOCKET) {
            printf("Accept failed: %d\n", WSAGetLastError());
            continue;
        }

        printf("Client connected from %s:%d\n",
               inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));

        // Create thread to handle client (concurrent - multiple clients simultaneously)
        // Note: Using uintptr_t to safe cast SOCKET to void*
        thread_handle = CreateThread(NULL, 0, client_handler, (LPVOID)(uintptr_t)client_sock, 0, NULL);
        if (thread_handle == NULL) {
            printf("Thread creation failed\n");
            closesocket(client_sock);
        } else {
            // Close handle to allow automatic cleanup when thread exits
            CloseHandle(thread_handle);
        }
    }

    closesocket(server_sock);
    WSACleanup();
    return 0;
}