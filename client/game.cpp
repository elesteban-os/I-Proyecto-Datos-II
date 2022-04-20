#include "game.h"

Game::Game()
{

}

/**
 * @brief Añade puntaje a un jugador.
 * 
 * @param player jugador.
 * @param score puntaje
 */
void Game::addScore(int player, int score) {
    scores[player] = score;
}

/**
 * @brief Obtiene el nombre del jugador.
 * 
 * @return puntero a un char array del jugador.
 */
char* Game::getPlayerName() {
    return playerName;
}

/**
 * @brief Obtiene el nombre del oponente.
 * 
 * @return puntero a un char array del oponente.
 */
char* Game::getOpponentName() {
    return opponentName;
}

/**
 * @brief Obtiene el puntaje de un jugador.
 * 
 * @param player Jugador
 * @return Entero del puntaje del jugador.
 */
int Game::getScore(int player) {
    return scores[player];
}

/**
 * @brief Coloca el nombre del jugador.
 * 
 * @param name puntero de un char array del nombre del jugador.
 */
void Game::setPlayerName(char *name) {
    memcpy(playerName, name, strlen(name));
}

/**
 * @brief Coloca el nombre del oponente.
 * 
 * @param name puntero de un char array del nombre del enemigo.
 */
void Game::setOpponentName(char *name) {
    memcpy(playerName, name, strlen(name));
}

