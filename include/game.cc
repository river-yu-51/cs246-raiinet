export module Game;
// contains: Game

import <vector>;
import <string>;
import <iostream>;

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
    Game(Board *board, std::vector<Player*> players, int moveNumber, bool hasStarted, bool isGameOver);

    void startGame(int);
    bool executeCommand(std::string command, Player *player);
    bool moveLink(Link *link, int x, int y);
    void useAbility(Ability *ability, const AbilityParam &param);

    Board *getBoard();
    Player *getPlayer(int playerNum);
    int getMoveNumber();
    bool getHasStarted();
    bool getIsGameOver();

    void initializeGame(int playerCount);

    bool executeMoveCommand(char A, std::string dir, Player *player);
    void executeAbilitiesCommand(Player *player);
    bool executeAbilityUseCommand(int abilityIndex, Player *player, std::istream &in);
    void executeBoardCommand(Player *player);
    bool executeSequenceCommand(std::string filename, Player *player);
    void executeQuitCommand();

    void battle(Link *attacker, Link *defender);

    void gameOver();
};
