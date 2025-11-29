module Display;

import <iostream>;

import Core;

Display::Display(
    Board *board,
    int currentPlayer,
    bool isAlternating)
    : board{board}, currentPlayer{currentPlayer}, isAlternating{isAlternating} {}

int Display::getCurrentPlayer() { return currentPlayer; }

bool Display::getIsAlternating() { return isAlternating; }

void Display::setCurrentPlayer(int current) { currentPlayer = current; }

void Display::setIsAlternating(bool alternating) { isAlternating = alternating; }

void Display::notify() {
    // Board changed → redraw
    drawBoard();
}

void Display::displayWall(std::ostream &os, int n) {
    for (int i = 0; i < n; ++i) {
        os << "=";
    }
    os << std::endl;
}

// Displays player's links in summary format
void Display::displayLinkSummary(std::ostream &os, const std::vector<Link*> &links, bool reveal) {
    const int perRow = 4; // 4x2 display of links

    for (std::size_t i = 0; i < links.size(); ++i) {
        Link *link = links[i];
        if (!link) continue; // safety check

        char sym = link->getSymbol();
        os << sym << ": ";

        // Display type and strength if revealed or owner is viewing
        if (reveal || link->isRevealed()) {
            char typeChar = (link->getType() == "data") ? 'D' : 'V';
            os << typeChar << link->getStrength();
        } else {
            os << "?";
        }

        // Display spacing based on reveal status
        bool endOfRow = ((i + 1) % perRow == 0) || (i + 1 == links.size());
        if (endOfRow && i != links.size() - 1) {
            os << '\n';
        } else if (reveal || link->isRevealed()) {
            os << " ";
        } else {
            os << "  ";
        }
    }
}

// Displays overall player info
void Display::displayInfo(std::ostream &os, Player *player, bool reveal) {
    os << "Player " << player->getPlayerNum() + 1 << ":\n";
    os << "Downloaded: " << player->getDataCount() << "D, "
       << player->getVirusCount() << "V\n";

    os << "Abilities: " << player->getAbilities().size() << "\n";

    Display::displayLinkSummary(os, player->getLinks(), reveal);
    os << std::endl;
}
