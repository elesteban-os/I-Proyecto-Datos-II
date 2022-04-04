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

class Memory
{
private:
    PROCESS_MEMORY_COUNTERS_EX pmc;
    SIZE_T currentMemoryUsage = pmc.WorkingSetSize;
    int maxMemoryCards = 5;
    linkedCard inMemoryCards;
    char inMemoryCardsInfo[20];
    int pageHit = 0;
    int pageFault = 0;
    const char *adressCards[15] = { "images/0.jpg", "images/1.jpg", "images/2.jpg", "images/3.jpg", "images/4.jpg",
                                    "images/5.jpg", "images/6.jpg", "images/7.jpg", "images/8.jpg", "images/9.jpg",
                                    "images/10.jpg", "images/11.jpg", "images/12.jpg", "images/13.jpg", "images/14.jpg" };
    int cardsMatrix[5][6];
    Server *server = new Server();
public:
    Memory();
    void memoryUsage();
    int getCurrentMemoryUsage();
    void newCard();
    void randomCards();
    void deleteCard();
    void initInMemoryCards();
    void createInMemoryCardsInfo();
    void startGame();
};

#endif // MEMORY_H