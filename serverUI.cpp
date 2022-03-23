#include <stdio.h>
#include <string.h>
#include "sockets/server.cpp"
#include <iostream>
#include <thread>
#include <chrono>

using std::this_thread::sleep_for;

int main(void) {
    Server server;
    server.startServer();

    while (true) {
        if (server.getLastMessage() != NULL) {
            printf("%s", server.getLastMessage());
            server.setZeroesLastMessage();
            sleep_for(std::chrono::milliseconds(1));
        }
    }
}