export module TextDisplay;

import Display;

export class TextDisplay : public Display {
    void drawBoard() override;
public:
    TextDisplay(Board *board, int currentPlayer, bool isAlternating);
};