module Game;

import <vector>;
import <string>;

import Core;
import Abilities;
//import Game;

Game::Game(Board *board, std::vector<Player*> players, int moveNumber,
           bool hasStarted, bool isGameOver)
    : board{board}, players{players}, moveNumber{moveNumber},
      hasStarted{hasStarted}, isGameOver{isGameOver} {}

void Game::startGame(int startingPlayer) {
    hasStarted = true;
    moveNumber = 0;
    // other stuff idk
}

void Game::executeCommand(std::string command, Player *player) {
    // parse command and execute
}

void Game::moveLink(Link *link) {
    // logic to move link
}

void Game::useAbility(Ability *ability) {
    // logic to use ability
}

Board *Game::getBoard() { return board; }

Player *Game::getPlayer(int playerNum) { return players[playerNum]; }

int Game::getMoveNumber() { return moveNumber; }

bool Game::getHasStarted() { return hasStarted; }

bool Game::getIsGameOver() { return isGameOver; }

void Game::gameOver() {
    isGameOver = true;
    // other stuff idk
}
