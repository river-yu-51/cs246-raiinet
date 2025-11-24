export module Game;
// contains: Game

import <vector>;
import <iostream>;
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
    bool executeCommand(std::string, Player*);
    void moveLink(Link*, int, int);
    void useAbility(Ability*, const AbilityParam&);

    bool executeMoveCommand(char, std::string, Player*);
    void executeAbilitiesCommand(Player*);
    bool executeAbilityUseCommand(int, Player*, std::istream&);
    void executeBoardCommand(Player*);
    bool executeSequenceCommand(std::string, Player*);
    void executeQuitCommand();

    Board *getBoard();
    Player *getPlayer(int);
    int getMoveNumber();
    bool getHasStarted();
    bool getIsGameOver();

    void gameOver(Player*);
};
