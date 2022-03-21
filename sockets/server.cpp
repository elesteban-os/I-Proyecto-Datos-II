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

class Server {
    private:
        WSADATA WsaData;
        int num, num2, clientLong;
        int bufferLen = 1024;
        char buffer[1024];
        struct sockaddr_in server1;
        struct sockaddr_in client1;
        int serverSocket = 0;
        int clients[2];
        int i = 0;

    public:
        int wsaCreate() {
            int num = WSAStartup(MAKEWORD(2,2), &WsaData);
            if (num != 0){
                printf("Error: WSAStartup() failed\n");
                return 1;
            }
            return num;
        }

        int createServerSocket() {
            serverSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (serverSocket == INVALID_SOCKET) {
                printf("Error Server Socket");
                WSACleanup();
                return 1;
            }
            return num;
        }

        int addressCreate() {
            memset(&server1, 0, sizeof(server1));
            server1.sin_family = AF_INET;
            server1.sin_addr.s_addr = htons(INADDR_ANY);
            server1.sin_port = htons(PORT_PORT);
            return 0;
        };

        int bindServerSocket() {
            num = bind(serverSocket, (struct sockaddr *)&server1, sizeof(server1));
            if (num < 0) {
                printf("Error Bind");
                WSACleanup();
                return 1;
            }
            return num;
        }

        int listenServerSocket() {
            num = listen(serverSocket, 10);
            if (num < 0) {
                printf("Error Listening");
                WSACleanup();
                return 1;
            }
            return num;
        }

        int acceptSocket() {
            socklen_t clilen = sizeof(client1);
            for (int i = 0; i < 2; i++) {
                clients[i] = accept(serverSocket, (struct sockaddr *)&client1, &clilen); 
            
            }
            return 0;
        }

        int readClients() {
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



        int startServer() {
            wsaCreate();
            createServerSocket();
            addressCreate();
            bindServerSocket();
            listenServerSocket();
            acceptSocket();
            readClients();

            return 0;
        }
};