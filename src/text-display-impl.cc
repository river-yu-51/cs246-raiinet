module Display;

import <iostream>;

import Core;

TextDisplay::TextDisplay(Board *board, int currentPlayer, bool isAlternating)
    : Display{board, currentPlayer, isAlternating} {}

void TextDisplay::drawBoard() {
    const auto &grid = board->getGrid();

    // draw stuff
}
