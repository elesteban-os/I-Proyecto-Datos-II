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
    if (noRandomTurns == 0) {
        int i = 0;
        int j = 0;
        int completeIndex = 0;
        int randomNum = 0;
        int readyNums[15];
        srand(time(0));
        for (int i = 0; i < 15; i++) {
            if (availableCards[i]) {
                readyNums[i] = 0;
            } else {
                completeIndex++;
                readyNums[i] = 2;
            }

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
            bool ready = false;
            while (!ready) {
                if (j == 6) {
                    i++;
                    j = 0;
                }
                if (availableButtons[i][j]) {
                    cardsMatrix[i][j] = randomNum;
                    j++;
                    ready = true;
                } else {
                    cardsMatrix[i][j] = -1;
                    j++;
                }

            }

        }

    } else {
        noRandomTurns -= 1;
    }


    QString text;
    for (int i = 0; i < 5; i++) {
        text.append("[");
        for (int j = 0; j < 6; j++) {
            text.append(QString::number(cardsMatrix[i][j]));
            text.append(", ");
        }
        text.append("]");
        qDebug() << text;
        text = "";
    }

}

void Memory::startGame() {
    randomCards();
    initInMemoryCards();
    server->startServer();
    std::thread tNames(&Memory::getNames, this);
    tNames.detach();
}

void Memory::changeTurn() {
    if (game->getTurn() == 0) {
        game->setTurn(1);
    } else {
        game->setTurn(0);
    }
    if (game->getPlaying()) {
        server->sendMessage("turn", game->getTurn(), 4);
    }

}

void Memory::newCard(int id) {
    qDebug() << "newCard" << id;
    const char* cardAddr;
    if (id == 0) {
        cardAddr = "images/0.jpg";
    } else if (id == 1) {
        cardAddr = "images/1.jpg";
    } else if (id == 2) {
        cardAddr = "images/2.jpg";
    } else if (id == 3) {
        cardAddr = "images/3.jpg";
    } else if (id == 4) {
        cardAddr = "images/4.jpg";
    } else if (id == 5) {
        cardAddr = "images/5.jpg";
    } else if (id == 6) {
        cardAddr = "images/6.jpg";
    } else if (id == 7) {
        cardAddr = "images/7.jpg";
    } else if (id == 8) {
        cardAddr = "images/8.jpg";
    } else if (id == 9) {
        cardAddr = "images/9.jpg";
    } else if (id == 10) {
        cardAddr = "images/10.jpg";
    } else if (id == 11) {
        cardAddr = "images/11.jpg";
    } else if (id == 12) {
        cardAddr = "images/12.jpg";
    } else if (id == 13) {
        cardAddr = "images/13.jpg";
    } else if (id == 14) {
        cardAddr = "images/14.jpg";
    } else {
        cardAddr = adressCards[id];
    }
    QImage image(cardAddr);

    qDebug() << "image" << id;

    int size = image.sizeInBytes();
    char data[size];
    memcpy(data, image.bits(), size);

    inMemoryCards.add(data, size, id);

    qDebug() << "add" << id;
}

char* Memory::getAnyCard(int x, int y) {
    int searchID = cardsMatrix[x][y];
    cardsSelected++;
    if (cardsSelected == 1) {
        cardSelected1 = searchID;
        firstButtonsSelected[0] = x;
        firstButtonsSelected[1] = y;
    } else {
        cardSelected2 = searchID;
    }
    qDebug() << "searchid" << searchID;

    char* data = inMemoryCards.getDataByID(searchID);
    if (data != NULL) {
        pageHit++;
        if (cardsSelected == 1) {
            pageHitCard = true;
        }
        return data;
    } else {
        inMemoryCards.deleteLastData();
        newCard(searchID);
        pageFault++;
        return inMemoryCards.getDataByID(searchID);
    }
}

void Memory::sendEnemyOneIndicator(int player, int indicator, int button) {
    QImage image(adressIndicator[indicator]);
    int size = image.sizeInBytes();
    char data[size];
    memcpy(data, image.bits(), size);

    sleep_for(std::chrono::milliseconds(50));
    server->sendMessage("enemyCard", player, 9);
    sleep_for(std::chrono::milliseconds(50));
    server->sendMessage(data, player, size);
    sleep_for(std::chrono::milliseconds(50));
    server->sendMessage(" ", player, button);
    sleep_for(std::chrono::milliseconds(50));

    if (indicator == 1) {
        server->sendMessage(" ", player, 1);
        sleep_for(std::chrono::milliseconds(50));
    } else {
        server->sendMessage(" ", player, 2);
        sleep_for(std::chrono::milliseconds(50));
    }
}

void Memory::sendPlayerOneIndicator(int player, int indicator) {
    QImage image(adressIndicator[indicator]);
    int size = image.sizeInBytes();
    char data[size];
    memcpy(data, image.bits(), size);

    sleep_for(std::chrono::milliseconds(50));
    server->sendMessage("imgq", player, 9);
    sleep_for(std::chrono::milliseconds(50));
    server->sendMessage(data, player, size);
    sleep_for(std::chrono::milliseconds(50));
}

void Memory::sendResult(bool result, int player) {
    if (result) {
        sendPlayerOneIndicator(player, 1);
        if (player == 0) {
            sendEnemyOneIndicator(1, 1, buttonsSelected[0]);
            sendEnemyOneIndicator(1, 1, buttonsSelected[1]);
        } else {
            sendEnemyOneIndicator(0, 1, buttonsSelected[0]);
            sendEnemyOneIndicator(0, 1, buttonsSelected[1]);
        }
    } else {
        // Enviar resultado de fallar al jugador.
        sendPlayerOneIndicator(player, 0);
        if (player == 0) {
            sendEnemyOneIndicator(1, 0, buttonsSelected[0]);
            sendEnemyOneIndicator(1, 0, buttonsSelected[1]);
        } else {
            sendEnemyOneIndicator(0, 0, buttonsSelected[0]);
            sendEnemyOneIndicator(0, 0, buttonsSelected[1]);
        }
    }
    buttonsSelected[0] = -1;
    buttonsSelected[1] = -1;
    changeTurn();
}

void Memory::recalculateInMemoryCards() {
    int newMaxCards = inGameCards / 3;
    if (newMaxCards > 0) {
        while (newMaxCards != maxMemoryCards) {
            inMemoryCards.deleteLastData();
            maxMemoryCards--;
        }
    }
    qDebug() << maxMemoryCards << "en memoria" << inGameCards << "en juego";
}

void Memory::verifyPair(int x, int y) {
    sleep_for(std::chrono::milliseconds(1000));
    if (cardSelected1 == cardSelected2) {
        server->sendMessage("correct", server->getClientPetition(), 7);
        sendResult(true, server->getClientPetition());
        availableButtons[x][y] = 0;
        availableButtons[firstButtonsSelected[0]][firstButtonsSelected[1]] = 0;
        availableCards[cardSelected1] = 0;
        sendPoints(server->getClientPetition());
        pageHitCard = false;
        inGameCards--;
        recalculateInMemoryCards();
    } else {
        doublePointsPU = false;
        server->sendMessage("incorrect", server->getClientPetition(), 9);
        sendResult(false, server->getClientPetition());
    }
}

void Memory::sendPoints(int player) {
    int points = 20;
    if (pageHitCard) {
        points *= 2;
    }
    if (doublePointsPU) {
        points *= 2;
        doublePointsPU = false;
    }
    game->addScore(player, points);
    int score = game->getScore(player);
    sleep_for(std::chrono::milliseconds(10));
    if (player == 0) {
        server->sendMessage("playerPoints", 0, 12);
        sleep_for(std::chrono::milliseconds(10));
        server->sendMessage(" ", 0, score);
        sleep_for(std::chrono::milliseconds(10));
        server->sendMessage("enemyPoints", 1, 11);
        sleep_for(std::chrono::milliseconds(10));
        server->sendMessage(" ", 1, score);
    } else {
        server->sendMessage("playerPoints", 1, 12);
        sleep_for(std::chrono::milliseconds(10));
        server->sendMessage(" ", 1, score);
        sleep_for(std::chrono::milliseconds(10));
        server->sendMessage("enemyPoints", 0, 11);
        sleep_for(std::chrono::milliseconds(10));
        server->sendMessage(" ", 0, score);
    }
}



void Memory::lastClientsButtons(int button) {
    if (buttonsSelected[0] == -1) {
        buttonsSelected[0] = button;
    } else {
        buttonsSelected[1] = button;
    }

}

void Memory::sendPlayersCard(char* image, int clientPetition) {
    server->sendMessage("card", clientPetition, 4);
    sleep_for(std::chrono::milliseconds(10));
    server->sendMessage(image, clientPetition, 47000);
    sleep_for(std::chrono::milliseconds(30));

    int cardPetition = 0;
    if (server->getCardPetition() == 0) {
        cardPetition = 100;
    } else {
        cardPetition = server->getCardPetition();
    }
    lastClientsButtons(cardPetition);

    if (clientPetition == 0) {
        server->sendMessage("enemyCard", 1, 9);
        sleep_for(std::chrono::milliseconds(30));
        server->sendMessage(image, 1, 47000);
        sleep_for(std::chrono::milliseconds(30));
        server->sendMessage(" ", 1, cardPetition);
        sleep_for(std::chrono::milliseconds(30));
        server->sendMessage(" ", 1, 2);
        sleep_for(std::chrono::milliseconds(50));
    } else {
        server->sendMessage("enemyCard", 0, 9);
        sleep_for(std::chrono::milliseconds(30));
        server->sendMessage(image, 0, 47000);
        sleep_for(std::chrono::milliseconds(30));
        server->sendMessage(" ", 0, cardPetition);
        sleep_for(std::chrono::milliseconds(30));
        server->sendMessage(" ", 0, 2);
        sleep_for(std::chrono::milliseconds(50));
    }
}

void Memory::getCardsPetition() {
    int x = 0;
    int y = 0;
    while (game->getPlaying()) {
        while (!server->getNewCardPetition()) {
            sleep_for(std::chrono::milliseconds(100));
        }
        qDebug() << "getCardsPetition" << server->getCardPetition();
        x = server->getCardPetition() / 10;
        y = server->getCardPetition() % 10;

        char* image = getAnyCard(x, y);

        int clientPetition = server->getClientPetition();
        sendPlayersCard(image, clientPetition);

        server->setNewCardPetition(false);

        if (cardsSelected == 2) {
            verifyPair(x, y);
            randomCards();
            cardsSelected = 0;
        }


    }
}

void Memory::gameInitAlgorithm() {
    game->setPlaying(true);
    std::thread tCards(&Memory::getCardsPetition, this);
    tCards.detach();
    std::thread tPU(&Memory::powerUpsListener, this);
    tPU.detach();
    server->sendMessage("started", 0, 7);
    sleep_for(std::chrono::milliseconds(10));
    server->sendMessage("started", 1, 7);
    sleep_for(std::chrono::milliseconds(10));
    srand(time(0));
    int random = rand() % 2;
    game->setTurn(random);
    if (game->getPlaying()) {
        sleep_for(std::chrono::milliseconds(100));
        server->sendMessage("turn", random, 4);
    }
}

// Se debe enviar a todos los clientes.
void Memory::sendQuestionImages() {
    //sleep_for(std::chrono::milliseconds(700));
    QImage image(adressIndicator[0]);
    int size = image.sizeInBytes();
    char data[size];
    memcpy(data, image.bits(), size);

    qDebug() << "imgqSize" << size;

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

void Memory::powerUpsListener() {
    while(game->getPlaying()) {
        while(server->getPowerUpSelected() == 0) {
            sleep_for(std::chrono::milliseconds(50));
        }
        switch (server->getPowerUpSelected()) {
            case 1:
                powerUp1();
                server->setPowerUpSelected(0);
                server->setClientPowerUpSelected(-1);
                break;
            case 2:
                powerUp2();
                server->setPowerUpSelected(0);
                server->setClientPowerUpSelected(-1);
                break;
            case 3:
                powerUp3();
                server->setPowerUpSelected(0);
                server->setClientPowerUpSelected(-1);
                break;
        }
    }
}

void Memory::powerUp1() {
    bool ready = false;
    int correct = rand() % 15;
    int correct2 = rand() % 15;
    bool correctTurn = false;
    while (!availableCards[correct]) {
        correct++;
        if (correct == 15) {
            correct = 0;
        }
    }
    while (!availableCards[correct2]) {
        correct2++;
        if (correct2 == 15) {
            correct2 = 0;
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            if (correctTurn) {
                cardsMatrix[i][j] = correct;
                correctTurn = rand() % 2;
            } else {
                cardsMatrix[i][j] = correct2;
                correctTurn = rand() % 2;
            }
        }
    }
    QString text;
    for (int i = 0; i < 5; i++) {
        text.append("[");
        for (int j = 0; j < 6; j++) {
            text.append(QString::number(cardsMatrix[i][j]));
            text.append(", ");
        }
        text.append("]");
        qDebug() << text;
        text = "";
    }
}

void Memory::powerUp2() {
    noRandomTurns = 4;
}

void Memory::powerUp3() {
    doublePointsPU = true;
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


