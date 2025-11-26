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

    void setCurrentPlayer(int currentPlayer);
    void setIsAlternating(bool isAlternating);

    void notify() override;
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
