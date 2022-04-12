#include "memory.h"
#include "card.h"
#include "linkedlist.h"

Memory::Memory() {
    this->pageHit = 0;
    this->pageFault = 0;
}

void Memory::memoryUsage() {
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    currentMemoryUsage = pmc.WorkingSetSize;
}

int Memory::getCurrentMemoryUsage() {
    memoryUsage();
    return currentMemoryUsage;
}


void Memory::randomCards() {
    int i = 0;
    int j = 0;
    int completeIndex = 0; 
    int randomNum = 0;
    int readyNums[15];
    for (int i = 0; i < 15; i++) {
        readyNums[i] = 0;
    }
    while (completeIndex != 15) {
        randomNum = rand() % 15;
        while (readyNums[randomNum] == 2) {
            randomNum++;
            if (randomNum == 15) {
                randomNum = 0;
            }
        }
        readyNums[randomNum]++;
        if (readyNums[randomNum] == 2) {
            completeIndex++;
        }
        if (j == 6) {
            i++;
            j = 0;
        }
        cardsMatrix[i][j] = randomNum;
        j++;  
    }
}

void Memory::startGame() {
    randomCards();
    initInMemoryCards();
    server->startServer();
    std::thread tNames(&Memory::getNames, this);
    tNames.detach();
}

void Memory::newCard(int id) {
    qDebug() << "newCard" << id;
    const char* cardAddr;
    if (id == 0) {
        cardAddr = "images/0.jpg";
    } else if (id == 1) {
        cardAddr = "images/1.jpg";
    } else {
        cardAddr = adressCards[id];
    }
    QImage image(cardAddr);

    qDebug() << "image";

    int size = image.sizeInBytes();
    char data[size];
    memcpy(data, image.bits(), size);

    inMemoryCards.add(data, size, id);

    qDebug() << "add" << id;
}

char* Memory::getAnyCard(int x, int y) {
    int searchID = cardsMatrix[x][y];

    qDebug() << "searchid" << searchID;

    char* data = inMemoryCards.getDataByID(searchID);
    if (data != NULL) {
        pageHit++;
        return data;
    } else {
        inMemoryCards.deleteLastData();
        newCard(searchID);
        pageFault++;
        return inMemoryCards.getDataByID(searchID);
    }
}

void Memory::getCardsPetition() {
    int x = 0;
    int y = 0;
    while (game->getPlaying()) {
        while (!server->getNewCardPetition()) {
            sleep_for(std::chrono::milliseconds(100));
        }
        x = server->getCardPetition() % 10;
        y = server->getCardPetition() / 10;
        qDebug() << "Matriz00" << cardsMatrix[0][0];
        char* image = getAnyCard(x, y);

        server->sendMessage("card", server->getClientPetition(), 4);
        sleep_for(std::chrono::milliseconds(10));
        server->sendMessage(image, server->getClientPetition(), 47000);
        server->setNewCardPetition(false);
        randomCards();

    }
}

void Memory::gameInitAlgorithm() {
    game->setPlaying(true);
    std::thread tCards(&Memory::getCardsPetition, this);
    tCards.detach();
    server->sendMessage("started", 0, 7);
    sleep_for(std::chrono::milliseconds(10));
    server->sendMessage("started", 1, 7);
    sleep_for(std::chrono::milliseconds(10));
    if (game->getPlaying()) {
        if (game->getTurn() == 0) {
            server->sendMessage("turn", 0, 4);
        }
    }
}

// Se debe enviar a todos los clientes.
void Memory::sendQuestionImages() {
    //sleep_for(std::chrono::milliseconds(700));
    QImage image(adressIndicator[0]);
    int size = image.sizeInBytes();
    char data[size];
    memcpy(data, image.bits(), size);

    for (int i = 0; i < 2; i++) {
        server->sendMessage("imgq", i, 4);
        sleep_for(std::chrono::milliseconds(10));
        server->sendMessage(data, i, size);
        sleep_for(std::chrono::milliseconds(200));
    }
    game->setTurn(0);
    gameInitAlgorithm();

}

void Memory::sendPlayersName() {
    server->sendMessage("enemyName", 0, 9);
    sleep_for(std::chrono::milliseconds(10));
    server->sendMessage(game->getPlayer2name(), 0, strlen(game->getPlayer2name()));
    sleep_for(std::chrono::milliseconds(10));
    server->sendMessage("enemyName", 1, 9);
    sleep_for(std::chrono::milliseconds(10));
    server->sendMessage(game->getPlayer1name(), 1, strlen(game->getPlayer1name()));
    sleep_for(std::chrono::milliseconds(10));

    //server->sendMessage("imgq", 0, 4);
    sendQuestionImages();
}

void Memory::getNames() {
    for (int i = 0; i < 2; i++) {
        while (!server->getNewNameBool()) {
            sleep_for(std::chrono::milliseconds(500));
        }
        if (i == 0) {
            game->setPlayer1name(server->getName());
            server->clearName();
            server->setNewNameBool(false);
            qDebug() << "Nombre1:" << game->getPlayer1name();
        } else {
            game->setPlayer2name(server->getName());
            server->clearName();
            server->setNewNameBool(false);
            qDebug() << "Nombre2:" << game->getPlayer2name();
        }
    }
    sendPlayersName();
}



void Memory::createCardsInfo(char* buffer, int* ids, int size) {
    char IDchar[5];
    for (int i = 0; i < size; i++) {
        std::sprintf(IDchar, "%d", ids[i]);
        strcat(buffer, IDchar);
        if (i < size - 1) {
            strcat(buffer, ", ");
        }
    }

}

void Memory::createInDiscCardsInfo() {
    memset(&inDiscCardsInfo, 0, 20);
    int size = inMemoryCards.getSize();
    int cardsSize = 15;
    cardsSize -= size;
    int IDarray[cardsSize];
    //int ID = 0;
    int j = 0;
    for (int i = 0; i < 15; i++) {
        if (!inMemoryCards.searchForID(i)) {
            IDarray[j] = i;
            j++;
        }
    }
    createCardsInfo(inDiscCardsInfo, IDarray, cardsSize);
    //printf("%d", IDarray);
}

void Memory::createInMemoryCardsInfo() {
    memset(&inMemoryCardsInfo, 0, 20);
    int ID;
    int cardsSize = inMemoryCards.getSize();
    int IDarray[cardsSize];
    for (int i = 0; i < cardsSize; i++) {
        ID = inMemoryCards.getID(i);
        IDarray[i] = ID;
    }
    createCardsInfo(inMemoryCardsInfo, IDarray, cardsSize);
}

void Memory::initInMemoryCards() {
    int size = 0;
    for(int i = 0; i < maxMemoryCards; i++) {
        // Imagen
        QImage image(adressCards[i]);
        size = image.sizeInBytes();
        char data[size];
        memcpy(data, image.bits(), size);
        inMemoryCards.add(data, size, i);
    }
    createInMemoryCardsInfo();
}

char* Memory::getInMemoryCardsInfo() {
    return inMemoryCardsInfo;
}

char* Memory::getInDiscCardsInfo() {
    return inDiscCardsInfo;
}

int Memory::getPageFault() {
    return pageFault;
}

int Memory::getPageHit() {
    return pageHit;
}


Server* Memory::getServer() {
    return this->server;
}

Game* Memory::getGame() {
    return this->game;
}


