#ifndef CLIENTSOCK_H
#define CLIENTSOCK_H

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <iostream>
#include <future>
#include <pthread.h>
#include <string.h>

#define PORT_PORT 1337
using std::this_thread::sleep_for;

class clientSock
{
public:
    clientSock();
    void startClient();
    char* getData();

    bool getWievedDataReceived();
private:
    WSADATA wsaData;
    int num, num2;
    int clientSocket = 0;
    int recBufferLen = 202500;
    char recBuffer[202500];
    char lastMessage[1024];
    struct sockaddr_in client;
    std::thread t;
    char data[203000];
    bool dataReceived = false;
    bool viewedDataReceived = true;
    bool running = true;
    void wsaCreate();
    void createSocket();
    void connectSocket();
    void readServer();
    void writeLastMessage(int len);
    void understandMessage();
};

#endif // CLIENTSOCK_H
