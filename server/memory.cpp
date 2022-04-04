#include "memory.h"
#include "card.h"
#include "linkedlist.h"

Memory::Memory() {
    randomCards();
    initInMemoryCards();
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
    printf("%s", "[");
    for (i = 0; i < 5; i++) {
        printf("%s", "[");
        for (j = 0; j < 6; j++) {
            printf("%d, ", cardsMatrix[i][j]);
        }
        printf("%s\n", "]");
    }
    printf("%s\n", "]");

}

void Memory::startGame() {
    randomCards();
    initInMemoryCards();
    server->startServer();
}

void Memory::createInMemoryCardsInfo() {
    memset(&inMemoryCardsInfo, 0, 20);
    int ID;
    char IDchar[5];
    for (int i = 0; i < inMemoryCards.getSize() - 1; i++) {
        ID = inMemoryCards.getID(i);

        std::sprintf(IDchar, "%d", ID);

        printf("%s", IDchar);

        //strncat(inMemoryCardsInfo, 1, 1);
    }
}

void Memory::initInMemoryCards() {
    int size = 0;
    for(int i = 0; i < maxMemoryCards; i++) {
        // Imagen
        QImage image(adressCards[i]);
        size = image.sizeInBytes();
        char data[size];
        memcpy(data, image.bits(), size);

        printf("%s", "imagen copiada");

        // Agregar a la lista
        inMemoryCards.add(data, size, i);

        printf("%s", "se agrega a la lista");
    }
    createInMemoryCardsInfo();
}


