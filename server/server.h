#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <string.h>
#include <iostream>

#define PORT_PORT 1337

using std::this_thread::sleep_for;

class Server
{
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
    char lastMessage[1024];   
    std::thread t; 
    std::thread tacpt;

    void writeLastMessage(char message[], int len);
    int readClients();
    int wsaCreate();
    int createServerSocket();
    int addressCreate();
    int bindServerSocket();
    int listenServerSocket();
    int acceptSocket();

public:
    Server();
    char* getLastMessage();
    int startServer();
    void sendMessage(const char* message, int client);
    void sendMessage(char *message, int client);
    void sendMessage(char *message, int client, int size);
    void setZeroesLastMessage();    

};

#endif // SERVER_H
