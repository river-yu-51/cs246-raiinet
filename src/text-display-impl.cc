module Display;

import <iostream>;

import Core;

TextDisplay::TextDisplay(Board *board, int currentPlayer, bool isAlternating)
    : Display{board, currentPlayer, isAlternating} {}

void TextDisplay::drawBoard() {
    const auto &grid = board->getGrid(); // assumes tht Board::getGrid() returns a 2d container of Tiles

    // draw stuff
    for (std::size_t row = 0; row < grid.size(); ++row) {
        for (std::size_t col = 0; col < grid[row].size(); ++col) {
            std::cout << grid[row][col]->getSymbol();
        }
        std::cout << '\n';
    }

}
