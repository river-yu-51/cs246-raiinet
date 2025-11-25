export module Game;
// contains: Game

import <vector>;
import <string>;

import Core;
import Abilities;
import Display;

export class Game {
    Board *board;
    std::vector<Player*> players;
    int moveNumber;
    bool hasStarted;
    bool isGameOver;
public:
    Game(Board*, std::vector<Player*>, int, bool, bool);

    void startGame(int);
    void executeCommand(std::string, Player*);
    void moveLink(Link*);
    void useAbility(Ability*);

    Board *getBoard();
    Player *getPlayer(int);
    int getMoveNumber();
    bool getHasStarted();
    bool getIsGameOver();

    void gameOver();
};
