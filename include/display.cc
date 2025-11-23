export module Display;

import Observer;
import Board;

export class Display : public Observer {
    Board *board;
    int currentPlayer;
    bool isAlternating;
protected:
    virtual void drawBoard() = 0;
public:
    Display(Board *board, int currentPlayer, bool isAlternating);

    int getCurrentPlayer();
    bool getIsAlternating();

    void setCurrentPlayer(int);
    void setIsAlternating(bool);

    void notify() override;
};