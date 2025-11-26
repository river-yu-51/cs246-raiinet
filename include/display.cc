export module Display;
// contains: Display, TextDisplay, GraphicsDisplay

import <iostream>;
import <vector>;

import Observer;
import Core;

export class Display : public Observer {
protected:
    Board *board;
    int currentPlayer;
    bool isAlternating;

public:
    Display(Board *board, int currentPlayer, bool isAlternating);

    int getCurrentPlayer();
    bool getIsAlternating();

    void setCurrentPlayer(int currentPlayer);
    void setIsAlternating(bool isAlternating);

    void notify() override;   // NOTE: no parameters

    virtual void drawBoard() = 0;
};

export class TextDisplay : public Display {

public:
    TextDisplay(Board *board, int currentPlayer, bool isAlternating);

    void drawBoard() override;
};

export class GraphicsDisplay : public Display {
    
public:
    GraphicsDisplay(Board *board, int currentPlayer, bool isAlternating);

    void drawBoard() override;
};

export void displayWall(std::ostream &os, int n);
export void displayLinkSummary(std::ostream &os, const std::vector<Link*> &link, bool reveal);
export void displayInfo(std::ostream &os, Player *player, bool reveal);
