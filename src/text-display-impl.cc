module Display;

import <iostream>;

import Core;

TextDisplay::TextDisplay(Board *board, int currentPlayer, bool isAlternating)
    : Display{board, currentPlayer, isAlternating} {}

void displayWall(int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << "=";
    }
    std::cout << std::endl;
}

void TextDisplay::drawBoard() {
    const auto &grid = board->getGrid();

    displayWall(static_cast<int>(grid[0].size()));

    for (const auto &row : grid) {
        for (const auto &tile : row) {
            if (tile->getLink()) {
                std::cout << tile->getLink()->getSymbol();
            } else {
                std::cout << tile->getSymbol();
            }
        }
        std::cout << std::endl;
    }

    displayWall(static_cast<int>(grid[0].size()));
}
