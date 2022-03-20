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
    struct addrinfo *res = NULL,
                    *ptr = NULL,
                    hints;
    const char *message = "Hello, world!";
    int recBufferLen = 1024;
    char recBuffer[recBufferLen];

    char hostname[64];

    struct sockaddr_in client;
    struct hostent *host = NULL;

    // Winsock 
    num = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (num != 0) {
        printf("WSAStartup error");
        return 1;
    }


    /*
    // Direcciones de red
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Get address
    num = getaddrinfo(argv[1], PORT_PORT, &hints, &res);
    if (num != 0){
        printf("Error getaddrinfo");
        WSACleanup();
        return 1;
    } */

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



    // Intentar conectar a un addr creando socket y conectando (connect)

    /*
    for(ptr = res; ptr != NULL; ptr = ptr->ai_next) {

        clientSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        printf("qqqqq");

        if (clientSocket == INVALID_SOCKET) {
            printf("Error client socket");
            WSACleanup();
            return 1;
        }

        num = connect(clientSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

        if (num == SOCKET_ERROR) {
            printf("Error connect client socket");
            closesocket(clientSocket);
            clientSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    */

   /*
    if (clientSocket == INVALID_SOCKET) {
        printf("Error client socket not connected");
        WSACleanup();
        return 1;
    }
        

    num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
    if (num2 == -1) {
            printf("Error message \n");
            closesocket(clientSocket);
            clientSocket = INVALID_SOCKET;
        
    }

    printf("Mensajes: %s\n", recBuffer);
    memset(recBuffer, 0, recBufferLen);

    num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
    if (num2 == -1) {
            printf("Error message \n");
            closesocket(clientSocket);
            clientSocket = INVALID_SOCKET;
        
    }
    printf("Mensajes: %s\n", recBuffer);
    memset(recBuffer, 0, recBufferLen);
    
    */

   return 0;
    
}