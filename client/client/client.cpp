#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define PORT_PORT 1337

int main(int argc, char **argv) {
    WSADATA wsaData;
    int num, num2;
    int clientSocket = 0;
    int recBufferLen = 1024;
    char recBuffer[recBufferLen];

    char hostname[64];

    struct sockaddr_in client;
    struct hostent *host = NULL;

    // Winsock 
    num = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (num != 0) {
        printf("WSAStartup error1");
        return 1;
    }

    // Get host
    num = gethostname(hostname, sizeof(hostname));
    if (num > 0){
        printf("Error get host");
        WSACleanup();
        return 1;
    }

    host = gethostbyname(hostname);

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_port = htons(PORT_PORT);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    
   
    num = connect(clientSocket, (struct sockaddr *)&client, sizeof(client));
    if (num < 0) {
        printf("error connect\n");
    }

    num2 = send(clientSocket, "hello", 5, 0);
    if (num2 < 0) {
        printf("error send\n");
    }

    num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
    if (num2 < 0) {
        printf("error send\n");
    }
    printf(recBuffer);
    memset(recBuffer, 0, recBufferLen);

    num2 = send(clientSocket, "hello2", 6, 0);
    if (num2 < 0) {
        printf("error send\n");
    }

    num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
    if (num2 < 0) {
        printf("error send\n");
    }
    printf(recBuffer);
    memset(recBuffer, 0, recBufferLen);

    num2 = send(clientSocket, "hello333", 8, 0);
    if (num2 < 0) {
        printf("error send\n");
    }

    num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
    if (num2 < 0) {
        printf("error send\n");
    }
    printf(recBuffer);
    memset(recBuffer, 0, recBufferLen);

    num2 = send(clientSocket, "hello2hell", 10, 0);
    if (num2 < 0) {
        printf("error send\n");
    }

    num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
    if (num2 < 0) {
        printf("error send\n");
    }
    printf(recBuffer);
    memset(recBuffer, 0, recBufferLen);

   return 0;
    
}