#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "sockets/server.cpp"

#pragma comment (lib, "wsock.lib")

#define PORT_PORT 1337

int main(void) {
    Server server;
    server.startServer();
}