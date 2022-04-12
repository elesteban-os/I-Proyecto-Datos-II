#ifndef MEMORY_H
#define MEMORY_H

#include "windows.h"
#include "psapi.h"
#include "linkedcard.h"
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include <iostream>
#include <QtGui/QImage>
#include "game.h"
#include <thread>
#include <QDebug>
using std::this_thread::sleep_for;

class Memory
{
private:
    PROCESS_MEMORY_COUNTERS_EX pmc;
    SIZE_T currentMemoryUsage = pmc.WorkingSetSize;
    int maxMemoryCards = 5;
    int inGameCards = 15;

    char inMemoryCardsInfo[20];
    char inDiscCardsInfo[20];

    const char *adressCards[15] = { "images/0.jpg", "images/1.jpg", "images/2.jpg", "images/3.jpg", "images/4.jpg",
                                    "images/5.jpg", "images/6.jpg", "images/7.jpg", "images/8.jpg", "images/9.jpg",
                                    "images/10.jpg", "images/11.jpg", "images/12.jpg", "images/13.jpg", "images/14.jpg" };
    const char *adressIndicator[1] = {"images/question.jpg"};

    int cardsMatrix[5][6];
    Server *server = new Server();
    Game *game = new Game;
    linkedCard inMemoryCards;
    int pageHit = 0;
    int pageFault = 0;
public:

    Memory();
    void memoryUsage();
    int getCurrentMemoryUsage();
    char* getInMemoryCardsInfo();
    char* getInDiscCardsInfo();
    void newCard(int id);
    void randomCards();
    void deleteCard();
    void initInMemoryCards();
    void createInMemoryCardsInfo();
    void createInDiscCardsInfo();
    void createCardsInfo(char* buffer, int* ids, int size);
    void sendQuestionImages();
    void startGame();
    void gameInitAlgorithm();
    Server* getServer();
    Game* getGame();
    void getNames();
    void sendPlayersName();
    void getCardsPetition();
    char* getAnyCard(int x, int y);

    int getPageHit();
    int getPageFault();
};

#endif // MEMORY_H
