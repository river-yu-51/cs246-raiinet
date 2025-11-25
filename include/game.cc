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
    Game(Board *board, std::vector<Player*> players, int moveNumber, bool hasStarted, bool isGameOver);

    void startGame(int startingPlayer);
    bool executeCommand(std::string command, Player *player);
    void moveLink(Link *link, int x, int y);
    void useAbility(Ability *ability, const AbilityParam& param);

    bool executeMoveCommand(char direction, std::string args, Player *player);
    void executeAbilitiesCommand(Player *player);
    bool executeAbilityUseCommand(int, Player *player, std::istream &is);
    void executeBoardCommand(Player *player);
    bool executeSequenceCommand(std::string args, Player *player);
    void executeQuitCommand();

    Board *getBoard();
    Player *getPlayer(int playerNum);
    int getMoveNumber();
    bool getHasStarted();
    bool getIsGameOver();

    void setMoveNumber(int n);

    void gameOver(Player *winner);
};
