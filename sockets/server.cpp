#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#pragma comment (lib, "wsock.lib")

#define PORT_PORT 1337

int main(int argc, char **argv){

    printf("Variables ");
    // Variables 
    WSADATA WsaData;
    int num, num2, clientLong;
    int bufferLen = 1024;
    char buffer[bufferLen];

    struct sockaddr_in server1;
    struct sockaddr_in client1;
    
    // Sockets
    int serverSocket = 0;
    int clients[2];
    int i = 0;
    
    // Iniciar WSAData
    printf("Iniciando Winsock ");
    num = WSAStartup(MAKEWORD(2,2), &WsaData);
    if (num != 0){
        printf("Error: WSAStartup() failed\n");
        return 1;
    }

    // Crear un socket para la conexion con el server.
    printf("SS ");
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Error Server Socket");
        WSACleanup();
        return 1;
    }

    memset(&server1, 0, sizeof(server1));
    server1.sin_family = AF_INET;
    server1.sin_addr.s_addr = htons(INADDR_ANY);
    server1.sin_port = htons(PORT_PORT);

    // Avisar que se creo un socket (bind)
    printf("Bind ");
    num = bind(serverSocket, (struct sockaddr *)&server1, sizeof(server1));
    if (num < 0) {
        printf("Error Bind");
        WSACleanup();
        return 1;
    }

    // Socket en modo escucha (listen)
    printf("Listen ");
    num = listen(serverSocket, 10);
    if (num < 0) {
        printf("Error Listening");
        WSACleanup();
        return 1;
    }

    // Aceptar conexiones (accept)
    printf("Accept ");
    
    socklen_t clilen = sizeof(client1);
    clients[0] = accept(serverSocket, (struct sockaddr*)&client1, &clilen);
    clients[1] = accept(serverSocket, (struct sockaddr*)&client1, &clilen);

    while(1) {
        for (i; i < 2; i++) {
            num2 = recv(clients[i], buffer, sizeof(buffer), 0);
            if (num2 != -1) {
                printf("Mensajes: %s\n", buffer);
                memset(buffer, 0, sizeof(buffer));
            }
            num2 = send(clients[i], "recibido", 8, 0);
        }
        i = 0;
    }
    return 0;
}

