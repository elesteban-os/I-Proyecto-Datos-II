#include "game.h"

Game::Game()
{

}

void Game::addScore(int player, int score) {
    scores[player] += score;
}

char* Game::getPlayerName() {
    return playerName;
}

char* Game::getOpponentName() {
    return opponentName;
}

int Game::getScore(int player) {
    return scores[player];
}

void Game::setPlayerName(char *name) {
    memcpy(playerName, name, strlen(name));
}

void Game::setOpponentName(char *name) {
    memcpy(playerName, name, strlen(name));
}

