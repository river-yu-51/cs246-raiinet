module Display;

import <iostream>;
import <vector>;

import Core;

TextDisplay::TextDisplay(Board *board, int currentPlayer, bool isAlternating)
    : Display{board, currentPlayer, isAlternating} {}

void TextDisplay::drawBoard() {
    const auto &grid = board->getGrid();
    if (grid.empty()) return;

    int width = static_cast<int>(grid[0].size());

    displayWall(std::cout, width);

    for (const auto &row : grid) {
        for (const auto &tile : row) {
            // if there is a link on the tile, return the link's symbol
            if (Link *link = tile->getLink()) {
                std::cout << link->getSymbol();
            } else {
                // otherwise, return the symbol on the tile (wall/firewall/empty tile)
                std::cout << tile->getSymbol();
            }
        }
        std::cout << std::endl;
    }

    displayWall(std::cout, width);
}
