#include "clientsock.h"

clientSock::clientSock()
{

}

void clientSock::wsaCreate() {
    num = WSAStartup(MAKEWORD(2,2), &wsaData);
      if (num != 0) {
           printf("WSAStartup error1");
      }
}


void clientSock::createSocket() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT_PORT);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
}

void clientSock::connectSocket() {
     num = connect(clientSocket, (struct sockaddr *)&client, sizeof(client));
}

void clientSock::writeLastMessage(int len) {
    memset(lastMessage, 0, 1024);
    printf("Last Message: %s\n", recBuffer);
    memcpy(lastMessage, recBuffer, len);
}

void clientSock::setImgIndBool(bool value) {
    imgIndBool = value;
}

void clientSock::understandMessage() {
    const char* message1 = "card";
    const char* message2 = "imgq";
    const char* message3 = "enemyName";
    const char* message4 = "turn";
    const char* message5 = "started";
    const char* message6 = "correct";
    const char* message7 = "incorrect";
    const char* message8 = "enemyCard";
    memset(&recBuffer, 0, recBufferLen);
    if (strcmp(lastMessage, message1) == 0) {
        qDebug() << "card";
        sleep_for(std::chrono::milliseconds(100));
        num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
        memcpy(data, recBuffer, num2);
        memset(&recBuffer, 0, recBufferLen);
        newData = true;
    }
    if (strcmp(lastMessage, message2) == 0) {
        qDebug() << "imgq";
        sleep_for(std::chrono::milliseconds(100));
        num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
        memcpy(imgInd, recBuffer, num2);
        qDebug() << imgInd << num2;
        imgIndBool = true;
        memset(&recBuffer, 0, recBufferLen);
    }
    if (strcmp(lastMessage, message3) == 0) {
        num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
        memcpy(enemyName, recBuffer, num2);
        qDebug() << "Enemy" << enemyName;
        enemyNameReceived = true;
        //playable = true;
        memset(&recBuffer, 0, recBufferLen);
    }
    if (strcmp(lastMessage, message4) == 0) {
        turn = true;
        qDebug() << "Turn";     
    }
    if (strcmp(lastMessage, message5) == 0) {
        playable = true;   
        qDebug() << "Playable";     
    }
    if (strcmp(lastMessage, message6) == 0) {
        correct = 1;   
        qDebug() << "Correct";     
    }
    if (strcmp(lastMessage, message7) == 0) {
        correct = 0;   
        qDebug() << "Inorrect";     
    }
    if (strcmp(lastMessage, message8) == 0) {
        qDebug() << "enemyCard";
        memset(&data, 0, 50000);
        //sleep_for(std::chrono::milliseconds(10));
        num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
        qDebug() << num2;
        memcpy(data, recBuffer, num2);
        memset(&recBuffer, 0, recBufferLen);
        sleep_for(std::chrono::milliseconds(10));
        num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
        if (num2 == 100) {
            enemyCardLocation = 0;
        } else {
            enemyCardLocation = num2;
        }
        sleep_for(std::chrono::milliseconds(10));
        num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
        if (num2 == 1) {
            correctEnemyCardSelected = true;
        } else {
            correctEnemyCardSelected = false;
        }

        qDebug() << enemyCardLocation;
        enemyDataReceived = true;
        memset(&recBuffer, 0, recBufferLen);   
        qDebug() << "enemyCardReady";
    } 
}

bool clientSock::getCorrectEnemyCardSelected() {
    return correctEnemyCardSelected;
}


void clientSock::setCorrectEnemyCardSelected(bool value) {
    correctEnemyCardSelected = value;
}

bool clientSock::getEnemyDataReceived() {
    return enemyDataReceived;
}

void clientSock::setEnemyDataReceived(bool value) {
    enemyDataReceived = value;
}

int clientSock::getEnemyCardLocation() {
    return enemyCardLocation;
}

int clientSock::getCorrect() {
    return correct;
}

void clientSock::setCorrect(int value) {
    correct = value;
}

bool clientSock::getNewData() {
    return newData;
}

void clientSock::setNewData(bool value) {
    this->newData = value;
}

void clientSock::clearData() {
    memset(&data, 0, 50000);
}

bool clientSock::getImgIndBool() {
    return imgIndBool;
}

char* clientSock::getImgInd() {
    return imgInd;
}

char* clientSock::getEnemyName() {
    return enemyName;
}

void clientSock::readServer() {
    while (1) {
        num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
        if (num2 != -1) {
                printf("Mensajes: %s\n", recBuffer);
                writeLastMessage(num2);
                understandMessage();
                memset(recBuffer, 0, recBufferLen);

        } else {
            printf("error");
        }
        sleep_for(std::chrono::milliseconds(1));
    }
}

char* clientSock::getData() {
    return data;
}

bool clientSock::getPlayable() {
    return playable;
}

bool clientSock::setPlayable(bool value) {
    this->playable = value;
}

void clientSock::sendMessage(char *message) {
    num2 = send(clientSocket, message, strlen(message), 0);
}

void clientSock::sendMessage(char *message, int size) {
    num2 = send(clientSocket, message, size, 0);
}

bool clientSock::getEnemyNameReceived() {
    return enemyNameReceived;
}

void clientSock::startClient() {
    wsaCreate();
    createSocket();
    connectSocket();
    t = std::thread(&clientSock::readServer, this);
    memset(&lastMessage, 0, sizeof(lastMessage));
    printf("Client started\n");
}

bool clientSock::getTurn() {
    return this->turn;
}

void clientSock::setTurn(bool value) {
    this->turn = value;
}
