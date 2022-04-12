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
#include <QDebug>

#define PORT_PORT 1337
using std::this_thread::sleep_for;

class clientSock
{
public:
    clientSock();
    void startClient();
    char* getData();
    bool getWievedDataReceived();
    bool getPlayable();
    bool setPlayable(bool value);
    void sendMessage(char* message);
    void sendMessage(char* message, int size);
    bool getImgIndBool();
    char* getImgInd();
    char* getEnemyName();
    bool getEnemyNameReceived();
    bool getTurn();
    void setTurn(bool value);
    bool getNewData();
    void setNewData(bool value);
    void clearData();

private:
    WSADATA wsaData;
    int num, num2;
    int clientSocket = 0;
    int recBufferLen = 202500;
    char recBuffer[202500];
    char lastMessage[1024];
    struct sockaddr_in client;
    std::thread t;
    char data[50000];
    bool newData = false;
    char imgInd[50000];
    char enemyName[30];
    bool enemyNameReceived = false;
    bool imgIndBool = false;
    bool playable = false;
    bool dataReceived = false;
    bool viewedDataReceived = true;
    bool running = true;
    bool turn = false;
    void wsaCreate();
    void createSocket();
    void connectSocket();
    void readServer();
    void writeLastMessage(int len);
    void understandMessage();
    
};

#endif // CLIENTSOCK_H
