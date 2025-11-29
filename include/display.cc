export module Display;

import <vector>;
import <iostream>;
import <sstream>;

import Observer;
import Core;
import xwindow;

// Base Display class
export class Display : public Observer {
protected:
    Board *board;
    int currentPlayer;
    bool isAlternating;
public:
    Display(Board *board, int currentPlayer, bool isAlternating);

    // Getters
    int getCurrentPlayer();
    bool getIsAlternating();

    // Setters
    void setCurrentPlayer(int currentPlayer);
    void setIsAlternating(bool isAlternating);

    // Static helper functions for displaying info
    static void displayWall(std::ostream &os, int n);
    static void displayLinkSummary(std::ostream &os, const std::vector<Link*> &link, bool reveal);
    static void displayInfo(std::ostream &os, Player *player, bool reveal);

    // Observer override
    void notify() override;

    // Pure virtual function to draw the board
    virtual void drawBoard() = 0;
};

// Text-based Display class in command line
export class TextDisplay : public Display {
public:
    TextDisplay(Board *board, int currentPlayer, bool isAlternating);

    // Draws board as text in command line
    void drawBoard() override;
};

// Graphics-based Display class using Xwindow
export class GraphicsDisplay : public Display {
    Xwindow *win; // ptr to graphics window
    std::vector<Player*> players;
public:
    GraphicsDisplay(Board *board, std::vector<Player*> players, int currentPlayer, bool isAlternating);

    // Draws board graphically using Xwindow
    void drawBoard() override;

    // Dtor to remove Xwindow ptr
    ~GraphicsDisplay();
};


