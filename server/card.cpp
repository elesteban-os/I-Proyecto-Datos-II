#include "card.h"

card::card(char *image, int size, int num)
{
    memcpy(imageBits, image, size);
    ID = num;
}

card::card() {

}

char* card::getImage() {
    return imageBits;
}

void card::setImage(char* image, int size) {
    memcpy(imageBits, image, size);
}

void card::setNext(card *next1) {
    next = next1;
}

card* card::getNext() {
    return next;
}

int card::getID() {
    return ID;
}

void card::setID(int num) {
    ID = num;
}
