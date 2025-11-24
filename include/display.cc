export module Display;
// contains: Display, TextDisplay, GraphicsDisplay

import <iostream>;

import Observer;
import Core;

export class Display : public Observer {
protected:
    Board *board;
    int currentPlayer;
    bool isAlternating;

    virtual void drawBoard() = 0;
public:
    Display(Board *board, int currentPlayer, bool isAlternating);

    int getCurrentPlayer();
    bool getIsAlternating();

    void setCurrentPlayer(int);
    void setIsAlternating(bool);

    void notify() override;
};

export class TextDisplay : public Display {
    void drawBoard() override;
public:
    TextDisplay(Board *board, int currentPlayer, bool isAlternating);
};

export class GraphicsDisplay : public Display {
    void drawBoard() override;
public:
    GraphicsDisplay(Board *board, int currentPlayer, bool isAlternating);
};
