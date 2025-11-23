export module Display;

export class Display {
    int currentPlayer;
    bool isAlternating;
public:
    virtual void notify() = 0;
};