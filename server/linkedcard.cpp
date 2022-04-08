#include "linkedcard.h"

linkedCard::linkedCard()
{

}

void linkedCard::add(char* data, int size, int num) {
    if (head == NULL) {
        head = new card(data, size, num);
        printf("%s", "if add");
    } else {
        card *tmp = head;
        while (tmp->getNext() != NULL) {
            tmp = tmp->getNext();
        }
        tmp->setNext(new card);
        tmp->getNext()->setImage(data, size);
        tmp->getNext()->setID(num);
        printf("%s", "else add");
    }
    this->size++;
}

char* linkedCard::getData(int index) {
    if (index < size && index >= 0) {
        card *tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->getNext();
        }
        return tmp->getImage();
    } else {
        return NULL;
    }
}

int linkedCard::getID(int index) {
    if (index < size && index >= 0) {
        card *tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->getNext();
        }
        return tmp->getID();
    } else {
        return -1;
    }
}

int linkedCard::deleteData(int index) {
    if (size == 1 && index == 0) {
        delete(head);
        size--;
        return 1;
    } else if (size == 0) {
        return -1;
    } else if (index < size && index >= 0) {
        card *tmp = head;
        for (int i = 0; i < index - 1; i++) {
            tmp = tmp->getNext();
        }
        card *tmpNext = tmp->getNext()->getNext();
        delete(tmp->getNext());
        tmp->setNext(tmpNext);
        size--;
        return 1;
    }
    return 0;
}

void linkedCard::deleteLastData() {
    deleteData(size - 1);
}

int linkedCard::getSize() {
    return size;
}
