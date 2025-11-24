module Display;

import Core;

Display::Display(Board *board, int currentPlayer, bool isAlternating)
    : board{board}, currentPlayer{currentPlayer}, isAlternating{isAlternating} {}

int Display::getCurrentPlayer() { return currentPlayer; }

bool Display::getIsAlternating() { return isAlternating; }

void Display::setCurrentPlayer(int current) { currentPlayer = current; }

void Display::setIsAlternating(bool alternating) { isAlternating = alternating; }

void Display::notify() { drawBoard(); }
