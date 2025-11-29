module Display;

import <vector>;
import <iostream>;
import <sstream>;

import Core;
import xwindow;

GraphicsDisplay::GraphicsDisplay(
    Board *board,
    std::vector<Player*> players,
    int currentPlayer,
    bool isAlternating): Display{board, currentPlayer, isAlternating},
    win{new Xwindow{400, 600}}, // default size 400x600
    players{players}
{
    // style if needed
}

// Draws board graphically using Xwindow
void GraphicsDisplay::drawBoard() {
    auto &grid = board->getGrid();
    if (grid.empty()) return;

    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    // layout parameters
    int cellSize = 40;
    int margin = 10;
    int lineHeight = 15;

    win->fillRectangle(0, 0, 1000, 1000, Xwindow::White); // clear background

    int textX = margin;
    int yStart = margin;

    win->drawString(textX, yStart, "Current game state:");
    int y = yStart + lineHeight;

    // get player info
    std::ostringstream oss1, oss2;
    bool revealP1 = (currentPlayer == 0);
    bool revealP2 = (currentPlayer == 1);
    displayInfo(oss2, players[1], revealP2);    
    displayInfo(oss1, players[0], revealP1);

    // draw player 1 info
    std::istringstream iss1(oss1.str());
    std::string line;
    while (std::getline(iss1, line)) {
        if (!line.empty()) {
            win->drawString(textX, y, line);
        }
        y += lineHeight;
    }

    // draw board
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            Tile *t = grid[row][col];
            int x = margin + col * cellSize;

            win->fillRectangle(x, y, cellSize, cellSize, Xwindow::Black); // tile border

            int fillColour = Xwindow::White;

            win->fillRectangle(x + 1, y + 1, cellSize - 2, cellSize - 2, fillColour); // tile fill

            // draw symbol
            char c;
            int textColour = Xwindow::Black;
            if (Link *link = t->getLink()) {
                c = link->getSymbol();

                bool isOwner = (link->getPlayer()->getPlayerNum() == currentPlayer);
                bool isPublic = link->isRevealed();

                if (isOwner || isPublic) {
                    if (link->getType() == "data") {
                        textColour = Xwindow::Green;
                    } else if (link->getType() == "virus") {
                        textColour = Xwindow::Red;
                    }
                }
            } else {
                c = t->getSymbol();
            }

            // center character in cell
            std::string s(1, c);
            win->drawString(x + cellSize / 2 - 4, y + cellSize / 2 + 4, s, textColour);
        }
        y += cellSize; // move to next row
    }

    y += lineHeight;

    // draw player 2 info
    std::istringstream iss2(oss2.str());
    while (std::getline(iss2, line)) {
        if (!line.empty()) {
            win->drawString(textX, y, line);
        }
        y += lineHeight;
    }
}

GraphicsDisplay::~GraphicsDisplay() { delete win; }
