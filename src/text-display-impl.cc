module Display;

import <iostream>;
import <vector>;

import Core;

TextDisplay::TextDisplay(Board *board, int currentPlayer, bool isAlternating)
    : Display{board, currentPlayer, isAlternating} {}

void displayWall(int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << "=";
    }
    std::cout << std::endl;
}

void displayLinkSummary(std::ostream &os,
                        const std::vector<Link*> &links,
                        bool reveal) {
    const int perRow = 4; // 4 columns per text row

    for (std::size_t i = 0; i < links.size(); ++i) {
        Link *link = links[i];
        if (!link) continue;

        char sym = link->getSymbol();

        os << sym << ": ";

        if (reveal) {
            char typeChar = (link->getType() == "data") ? 'D' : 'V';
            os << typeChar << link->getStrength();
        } else {
            os << "?";
        }

        bool endOfRow = ((i + 1) % perRow == 0) || (i + 1 == links.size());
        if (endOfRow) {
            os << '\n';
        } else {
            os << "    ";
        }
    }
}

void displayInfo(std::ostream &os, Player *player, bool revealLinks) {
    os << "Player " << player->getPlayerNum() + 1 << ":\n";
    os << "Downloaded: " << player->getDataCount() << "D, "
       << player->getVirusCount() << "V\n";

    os << "Abilities: " << player->getAbilities().size() << "\n";

    displayLinkSummary(os, player->getLinks(), revealLinks);
    os << std::endl;
}


void TextDisplay::drawBoard() {
    const auto &grid = board->getGrid();
    if (grid.empty()) return;

    int width = static_cast<int>(grid[0].size());

    displayWall(width);

    for (const auto &row : grid) {
        for (const auto &tile : row) {
            if (Link *link = tile->getLink()) {
                std::cout << link->getSymbol();
            } else {
                std::cout << tile->getSymbol();
            }
        }
        std::cout << std::endl;
    }

    displayWall(width);
}
