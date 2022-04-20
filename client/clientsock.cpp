#include "clientsock.h"

clientSock::clientSock()
{

}

/**
 * @brief Funcion que inicia la funcionalidad de WSA de windows.
 * 
 */
void clientSock::wsaCreate() {
    num = WSAStartup(MAKEWORD(2,2), &wsaData);
      if (num != 0) {
           printf("WSAStartup error1");
      }
}

/**
 * @brief Crea el socket del servidor con sus respectiva configuración.
 * 
 */
void clientSock::createSocket() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT_PORT);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
}

/**
 * @brief Se realiza una conexión con el servidor desde el cliente.
 * 
 */
void clientSock::connectSocket() {
     num = connect(clientSocket, (struct sockaddr *)&client, sizeof(client));
}

/**
 * @brief Se realiza una escritura del último mensaje recibido a la variable "lastMessage".
 * @param len tamaño del mensaje.
 */
void clientSock::writeLastMessage(int len) {
    memset(lastMessage, 0, 1024);
    printf("Last Message: %s\n", recBuffer);
    memcpy(lastMessage, recBuffer, len);
}

/**
 * @brief Hace que el booleano de un indicador de imágenes cambie.
 * 
 * @param value valor.
 */
void clientSock::setImgIndBool(bool value) {
    imgIndBool = value;
}

/**
 * @brief Interpreta un mensaje recibido para saber que acciones tomar.
 * 
 */
void clientSock::understandMessage() {
    const char* message1 = "card";
    const char* message2 = "imgq";
    const char* message3 = "enemyName";
    const char* message4 = "turn";
    const char* message5 = "started";
    const char* message6 = "correct";
    const char* message7 = "incorrect";
    const char* message8 = "enemyCard";
    const char* message9 = "playerPoints";
    const char* message10 = "enemyPoints";
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
    if (strcmp(lastMessage, message9) == 0) {
        playerPoints = 0;
        points = recv(clientSocket, recBuffer, recBufferLen, 0);
    }
    if (strcmp(lastMessage, message10) == 0) {
        playerPoints = 1;
        points = recv(clientSocket, recBuffer, recBufferLen, 0);    
    }
}

/**
 * @brief Obtiene el jugador en el cuál se le actualiza el puntaje.
 * @return jugador.
 */
int clientSock::getPlayerPoints() {
    return playerPoints;
}

/**
 * @brief Coloca un valor al jugador del puntaje.
 * @param valor.
 */
void clientSock::setPlayerPoints(int value) {
    playerPoints = value;
}

/**
 * @brief Obtiene el puntaje de un jugador.
 * @return puntaje.
 */
int clientSock::getPoints() {
    return points;
}

/**
 * @brief Coloca un número en los puntajes.
 * @param puntaje.
 */
void clientSock::setPoints(int value) {
    points = value;
}

/**
 * @brief Obtiene el resultado de la elección de tarjetas.
 * 
 * @return El resultado del par elegido.
 */
bool clientSock::getCorrectEnemyCardSelected() {
    return correctEnemyCardSelected;
}

/**
 * @brief Coloca un valor en la variable "correctEnemyCardSelected".
 * 
 * @param value valor.
 */
void clientSock::setCorrectEnemyCardSelected(bool value) {
    correctEnemyCardSelected = value;
}

/**
 * @brief Obtiene un indicador que avisa si se hac recibido datos del oponente.
 * 
 * @return valor de la variable.
 * 
 */
bool clientSock::getEnemyDataReceived() {
    return enemyDataReceived;
}

/**
 * @brief Coloca un valor en la variable "enemeyDataReceived".
 * 
 * @param value valor.
 */
void clientSock::setEnemyDataReceived(bool value) {
    enemyDataReceived = value;
}

/**
 * @brief Obtiene el valor de la dirección de una carta elegida por el oponente.
 * 
 * @return La diección de la carta elegida-
 */
int clientSock::getEnemyCardLocation() {
    return enemyCardLocation;
}

/**
 * @brief Obtiene el valor de la carta que es correcta.
 * 
 * @return valor correcto.
 */
int clientSock::getCorrect() {
    return correct;
}

/**
 * @brief Coloca el valor correcto en la variable.
 * 
 * @param value valor.
 */
void clientSock::setCorrect(int value) {
    correct = value;
}

/**
 * @brief Avisa si la variable "data" tiene un nuevo array.
 * 
 * @return true si hay nuevos datos.
 */
bool clientSock::getNewData() {
    return newData;
}

/**
 * @brief Cambia el valor de la variable "newData".
 * 
 * @param value valor.
 */
void clientSock::setNewData(bool value) {
    this->newData = value;
}

/**
 * @brief Realiza una limpieza de la variable "data".
 * 
 */
void clientSock::clearData() {
    memset(&data, 0, 50000);
}

/**
 * @brief Obtiene si existe un nuevo indicador.
 * 
 * @return true si existe un nuevo indicador.
 */
bool clientSock::getImgIndBool() {
    return imgIndBool;
}

/**
 * @brief Obtiene datos de la imagen indicadora.
 * 
 * @return puntero a un char array de la imagen indicadora.
 */
char* clientSock::getImgInd() {
    return imgInd;
}

/**
 * @brief Obtiene el nombre del oponente.
 * 
 * @return puntero a un char array del oponente-
 */
char* clientSock::getEnemyName() {
    return enemyName;
}

/**
 * @brief Realiza una lectura constante de los mensajes que el servidor envía.
 * 
 */
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

/**
 * @brief Obtiene datos de una imagen recibida.
 * 
 * @return puntero a un char array de la imagen.
 */
char* clientSock::getData() {
    return data;
}

/**
 * @brief Obtiene información de la posibilidad de ininicar el juego.
 * 
 * @return true si es jugable.
 */
bool clientSock::getPlayable() {
    return playable;
}

/**
 * @brief Coloca un valor a la variable "playable".
 * 
 * @param value valor.
 */
void clientSock::setPlayable(bool value) {
    this->playable = value;
}

/**
 * @brief Envía un mensaje al servidor.
 * 
 * @param message Mensaje que se va a enviar.
 */
void clientSock::sendMessage(char *message) {
    num2 = send(clientSocket, message, strlen(message), 0);
}

/**
 * @brief Envía un mensaje al servidor.
 * 
 * @param message Mensaje que se va a enviar.
 * @param size Tamaño del mensaje.
 */
void clientSock::sendMessage(char *message, int size) {
    num2 = send(clientSocket, message, size, 0);
}

/**
 * @brief Obtiene si se ha recibido un nuevo mensaje del servidor.
 * 
 * @return true si se ha recibido un nuevo dato.
 */
bool clientSock::getEnemyNameReceived() {
    return enemyNameReceived;
}

/**
 * @brief Prepara las funciones y las inicializa para la correcta conexión con el servidor.
 * 
 */
void clientSock::startClient() {
    wsaCreate();
    createSocket();
    connectSocket();
    t = std::thread(&clientSock::readServer, this);
    memset(&lastMessage, 0, sizeof(lastMessage));
    printf("Client started\n");
}

/**
 * @brief Obtiene el turno de juego.
 * 
 * @return true si es el turno del jugador.
 */
bool clientSock::getTurn() {
    return this->turn;
}

/**
 * @brief Coloca un valor en la variable del turno.
 * 
 * @param value valor.
 */
void clientSock::setTurn(bool value) {
    this->turn = value;
}
