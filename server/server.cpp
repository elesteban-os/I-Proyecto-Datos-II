#include "server.h"

Server::Server()
{

}

void Server::writeLastMessage (char message[], int len) {
    memset(lastMessage, 0, len);
    for (int i = 0; i < len; i++) {
            lastMessage[i] = message[i];               
    }
}

bool Server::getNewNameBool() {
    return this->newName;
}

void Server::setNewNameBool(bool name) {
    this->newName = name;
}

char* Server::getName() {
    return name;
}

void Server::clearName() {
    memset(name, 0, 1024);
}

int Server::getPowerUpSelected() {
    return powerUpSelected;
}

void Server::setPowerUpSelected(int value) {
    this->powerUpSelected = value;
}

int Server::getClientPowerUp() {
    return clientPowerUp;
}

void Server::setClientPowerUpSelected(int value) {
    clientPowerUp = value;
}

void Server::understandMessage(int i) {
    const char *message1 = "name";
    const char *message2 = "card";
    const char *message3 = "pu1";
    const char *message4 = "pu2";
    const char *message5 = "pu3";
    memset(buffer, 0, sizeof(buffer));
    //char* token = strtok(lastMessage, " ");
    qDebug() << "LM: \"" << lastMessage << "\"" << "\n";

    if (strcmp(lastMessage, message1) == 0) {
        //token = strtok(NULL, "-");
        
        num2 = recv(clients[i], buffer, sizeof(buffer), 0);
        memset(name, 0, sizeof(name));
        memcpy(name, buffer, num2);
        qDebug() << "Nombre:" << name << "\n";
        newName = true;
        //num2 = recv(clients[i], buffer, sizeof(buffer), 0); 
    }
    if (strcmp(lastMessage, message2) == 0) {
        num2 = recv(clients[i], buffer, sizeof(buffer), 0);
        if (num2 == 100) {
            cardPetition = 0;
        } else {
            cardPetition = num2;
        }
        qDebug() << "CardPetition" << cardPetition << "\n";
        newCardPetition = true;
        clientPetition = i;
    }
    if (strcmp(lastMessage, message3) == 0) {
        powerUpSelected = 1;
        clientPowerUp = i;
    }
    if (strcmp(lastMessage, message4) == 0) {
        powerUpSelected = 2;
        clientPowerUp = i;
    }
    if (strcmp(lastMessage, message5) == 0) {
        powerUpSelected = 3;
        clientPowerUp = i;
    }
}

int Server::readClient(int i) {
    char buffer[1024];
    int bufferLen = 1024;
    int num2;
    while(1) {
        num2 = recv(clients[i], buffer, sizeof(buffer), 0);
        if (num2 != -1) {
            qDebug() << "Mensaje:" << "\"" << buffer << "\"" << "\n";
            memset(lastMessage, 0, 1024);
            memcpy(lastMessage, buffer, num2);
            understandMessage(i);
            memset(buffer, 0, sizeof(buffer));
        } 

        //num2 = send(clients[i], "recibido\0", 10, 0);
        sleep_for(std::chrono::milliseconds(10));
    }
}                         

int Server::acceptSocket() {
    socklen_t clilen = sizeof(client1);
    for (int i = 0; i < 2; i++) {
        clients[i] = accept(serverSocket, (struct sockaddr *)&client1, &clilen);
        std::thread tRead(&Server::readClient, this, i);
        tRead.detach();
    }
    readyQuestionImage = true;
    return 0;
}

int Server::wsaCreate() {
    int num = WSAStartup(MAKEWORD(2,2), &WsaData);
    if (num != 0){
        printf("Error: WSAStartup() failed\n");
        return 1;
    }
    return num;
}

int Server::createServerSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Error Server Socket");
        WSACleanup();
        return 1;
    }
    return num;
}

int Server::addressCreate() {
    memset(&server1, 0, sizeof(server1));
    server1.sin_family = AF_INET;
    server1.sin_addr.s_addr = htons(INADDR_ANY);
    server1.sin_port = htons(PORT_PORT);
    return 0;
};

int Server::bindServerSocket() {
    num = bind(serverSocket, (struct sockaddr *)&server1, sizeof(server1));
    if (num < 0) {
        printf("Error Bind");
        WSACleanup();
        return 1;
    }
    return num;
}

int Server::listenServerSocket() {
    num = listen(serverSocket, 10);
    if (num < 0) {
        printf("Error Listening");
        WSACleanup();
        return 1;
    }
    return num;
}



char* Server::getLastMessage() {
    return lastMessage;
}

int Server::startServer() {
    wsaCreate();
    createServerSocket();
    addressCreate();
    bindServerSocket();
    listenServerSocket();

    tacpt = std::thread(&Server::acceptSocket, this);
                
    memset(&lastMessage, 0, sizeof(lastMessage));
    //t = std::thread(&Server::readClients, this);
    printf("Server started");
    return 0;
}

void Server::sendMessage(const char* message, int client) {
    num = send(clients[client], message, strlen(message), 0);
}

void Server::sendMessage(char *message, int client) {
    num = send(clients[client], message, strlen(message), 0);
}

void Server::sendMessage(char *message, int client, int size) {
    num = send(clients[client], message, size, 0);
}

void Server::setZeroesLastMessage() {
    memset(&lastMessage, 0, sizeof(lastMessage));
}

bool Server::getReadyQuestionImage() {
    return readyQuestionImage;
}

int Server::getCardPetition() {
    return cardPetition;
}

bool Server::getNewCardPetition() {
    return newCardPetition;
}

void Server::setNewCardPetition(bool value) {
    this->newCardPetition = value;
}

int Server::getClientPetition() {
    return clientPetition;
}
