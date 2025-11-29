export module Display;

import <vector>;
import <iostream>;
import <sstream>;

import Observer;
import Core;
import xwindow;

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

    static void displayWall(std::ostream &os, int n);
    static void displayLinkSummary(std::ostream &os, const std::vector<Link*> &link, bool reveal);
    static void displayInfo(std::ostream &os, Player *player, bool reveal);

    void notify() override;
    virtual void drawBoard() = 0;
};

export class TextDisplay : public Display {
public:
    TextDisplay(Board *board, int currentPlayer, bool isAlternating);
    void drawBoard() override;
};

export class GraphicsDisplay : public Display {
    Xwindow *win; // ptr to graphics window
    std::vector<Player*> players;
public:
    GraphicsDisplay(Board *board, std::vector<Player*> players, int currentPlayer, bool isAlternating);

    void drawBoard() override;

    ~GraphicsDisplay();
};


