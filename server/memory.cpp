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
    int ID = 0;
    int j = 0;
    for (int i = 0; i < 15; i++) {
        ID = inMemoryCards.getID(i);
        if (ID == -1) {
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

        printf("%s\n", "imagen copiada");

        // Agregar a la lista
        inMemoryCards.add(data, size, i);

        printf("%s\n", "se agrega a la lista");
        printf("%d\n", inMemoryCards.getSize());
    }
    createInMemoryCardsInfo();
}

char* Memory::getInMemoryCardsInfo() {
    return inMemoryCardsInfo;
}

char* Memory::getInDiscCardsInfo() {
    return inDiscCardsInfo;
}


