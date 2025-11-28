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
    // bool p1Ability;
    // bool p2Ability;
    // bool p1Links;
    // bool p2Links;
public:
    // bool initL1 = false, initL2 = false, initA1 = false, initA2 = false;

    Game(Board *board, std::vector<Player*> players, int moveNumber, bool hasStarted, bool isGameOver);

    void startGame(int);
    bool executeCommand(std::string command, Player *player, std::string order = "");
    bool moveLink(Link *link, int x, int y);
    void useAbility(Ability *ability, const AbilityParam &param);

    Board *getBoard();
    Player *getPlayer(int playerNum);
    Link *getLink(char c);
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
    // bool getAbility1();
    // bool getAbility2();
    // bool getLinks1();
    // bool getLinks2();
    // void setAbility1(bool set);
    // void setAbility2(bool set);
    // void setLinks1(bool set);
    // void setLinks2(bool set);
    void incrementMoveNumber();
    bool gameReady();
    void gameOver();

    ~Game();
};
