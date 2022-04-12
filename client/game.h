#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string.h>

class Game
{
private:
    int scores[2];
    char playerName[20];
    char opponentName[20];

public:
    Game();
    int getScore(int player);
    void addScore(int player, int score);
    char* getPlayerName();
    char* getOpponentName();
    void setPlayerName(char* name);
    void setOpponentName(char* name);
};

#endif // GAME_H
