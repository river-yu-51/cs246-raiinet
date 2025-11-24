module Display;

import <iostream>;

import Core;

GraphicsDisplay::GraphicsDisplay(Board *board, int currentPlayer, bool isAlternating)
    : Display{board, currentPlayer, isAlternating} {}

void GraphicsDisplay::drawBoard() {
    const auto &grid = board->getGrid();

    // draw stuff
}
