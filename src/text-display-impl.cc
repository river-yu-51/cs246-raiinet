module TextDisplay;

import <iostream>;

import Board;
import Tile;
import Display;

TextDisplay::TextDisplay(Board *board, int currentPlayer, bool isAlternating)
    : Display{board, currentPlayer, isAlternating} {}

void TextDisplay::drawBoard() {
    const auto &grid = board->getGrid();

    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            std::cout << grid[i][j]->getSymbol();
        }
        std::cout << std::endl;
    }
}
