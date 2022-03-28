#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>

#define PORT_PORT 1337
using std::this_thread::sleep_for;

class Client {
    private:
        WSADATA wsaData;
        int num, num2;
        int clientSocket = 0;
        int recBufferLen = 1024;
        char recBuffer[1024];
        char lastMessage[1024]; 
        struct sockaddr_in client;
        std::thread t;

        int wsaCreate() {
            num = WSAStartup(MAKEWORD(2,2), &wsaData);
            if (num != 0) {
                printf("WSAStartup error1");
            }
            return num;
        }

        int createSocket() {
            clientSocket = socket(AF_INET, SOCK_STREAM, 0);
            memset(&client, 0, sizeof(client));
            client.sin_family = AF_INET;
            client.sin_port = htons(PORT_PORT);
            client.sin_addr.s_addr = inet_addr("127.0.0.1");  
            return 0;    
        }   
    
        int connectSocket() {
            num = connect(clientSocket, (struct sockaddr *)&client, sizeof(client));
            return num;
        }

        void writeLastMessage(char message[], int len) {
            memset(lastMessage, 0, len);
            for (int i = 0; i < len; i++) {
                 lastMessage[i] = message[i];               
            }
        }

        int readServer() {
            int i = 0;
            while (1) {
                for (i; i < 2; i++) {
                    num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
                    if (num2 != -1) {
                        printf("Mensajes: %s\n", recBuffer);
                        writeLastMessage(recBuffer, num2);
                        memset(recBuffer, 0, recBufferLen);
                    }
                }
                i = 0;
                sleep_for(std::chrono::milliseconds(1));
            }
            return 0;
        }

    public:
        int startClient() {
            wsaCreate();
            createSocket();
            connectSocket();
            t = std::thread(&Client::readServer, this);
            t.join();
            printf("Client started\n");
            return 0;
        }

        int sendMessage(const char* message) {
            int err = send(clientSocket, message, sizeof(message), 0);
            return err;
        } 
        
};
