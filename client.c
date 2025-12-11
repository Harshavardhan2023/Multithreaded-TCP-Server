#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 12347
#define BUFFER_SIZE 1024
#define MAX_NUMBERS 100

int main() {
    SOCKET sockfd;
    struct sockaddr_in server_addr;
    int numbers[MAX_NUMBERS];
    int count, i;
    WSADATA wsaData;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Connection failed: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("Connected to TCP Concurrent Sorting Server (Port %d)\n", SERVER_PORT);

    // Get number count from user
    printf("Enter the number of elements to sort (max %d): ", MAX_NUMBERS);
    if (scanf("%d", &count) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (count <= 0 || count > MAX_NUMBERS) {
        printf("Invalid number count\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Get numbers from user
    printf("Enter %d unsorted numbers:\n", count);
    for (i = 0; i < count; i++) {
        printf("Number %d: ", i + 1);
        scanf("%d", &numbers[i]);
    }

    // Send count first
    send(sockfd, (char*)&count, sizeof(count), 0);

    // Send numbers to server
    send(sockfd, (char*)numbers, count * sizeof(int), 0);
    printf("\nSent %d numbers to concurrent server for sorting...\n", count);

    // Receive sorted numbers
    recv(sockfd, (char*)numbers, count * sizeof(int), 0);

    printf("\nReceived sorted numbers from concurrent server:\n");
    for (i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    closesocket(sockfd);
    WSACleanup();
    return 0;
}