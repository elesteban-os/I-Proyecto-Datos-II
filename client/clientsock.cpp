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

void clientSock::understandMessage() {
    const char* message1 = "newimage";
    if (strcmp(lastMessage, message1) == 0) {
        printf("understand: %s\n", "Imagen");
        bool reading = true;
        char readingchar[1024];
        //sleep_for(std::chrono::milliseconds(5000));
        /*
        while (reading) {
            sleep_for(std::chrono::milliseconds(100));
            num2 = recv(clientSocket, data, recBufferLen, 0);
            if ()
            printf("num2: %i\n", num2);
            printf("Data %s/n", data);
        } */
        sleep_for(std::chrono::milliseconds(100));
        num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
        memcpy(data, recBuffer, num2);
        //printf("num2: %i\n", num2);
        printf("Data %s/n", data);
        printf("num2: %i\n", num2);
    }
}

void clientSock::readServer() {
    while (1) {
        num2 = recv(clientSocket, recBuffer, recBufferLen, 0);
        if (num2 != -1) {
                printf("num2: %i\n", num2);
                //recBuffer[num2] = "/0";
                printf("Mensajes: %s\n", recBuffer);
                writeLastMessage(num2);

                understandMessage();

                memset(recBuffer, 0, recBufferLen);

        } else {
            printf("error");
        }
        sleep_for(std::chrono::milliseconds(1000));
    }
}

char* clientSock::getData() {
    return data;
}

void clientSock::startClient() {
    wsaCreate();
    createSocket();
    connectSocket();
    t = std::thread(&clientSock::readServer, this);
    memset(&lastMessage, 0, sizeof(lastMessage));
    printf("Client started\n");
}
