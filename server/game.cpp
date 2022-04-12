#include "game.h"

Game::Game()
{

}


void Game::addScore(int player, int score) {
    scores[player] += score;
}

char* Game::getPlayer1name() {
    return player1name;
}

char* Game::getPlayer2name() {
    return player2name;
}

int Game::getScore(int player) {
    return scores[player];
}

void Game::setPlayer1name(char *name) {
    memcpy(player1name, name, strlen(name));
}

void Game::setPlayer2name(char *name) {
    memcpy(player2name, name, strlen(name));
}

bool Game::getPlaying() {
    return this->playing;
}

void Game::setPlaying(bool value) {
    this->playing = value;
}

int Game::getTurn() {
    return this->turn;
}

void Game::setTurn(int value) {
    this->turn = value;
}
 
