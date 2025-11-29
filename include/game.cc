export module Game;
// contains: Game

import <vector>;
import <string>;
import <iostream>;

import Core;
import Abilities;
import Display;

// Game class - contains game state and logic
export class Game {
    Board *board;
    std::vector<Player*> players;
    int moveNumber;
    bool hasStarted;
    bool isGameOver;
public:
    bool initL1 = false, initL2 = false, initA1 = false, initA2 = false; // command line arguments

    Game(Board *board, std::vector<Player*> players, int moveNumber, bool hasStarted, bool isGameOver);

    // Game flow methods
    void startGame(int);
    bool executeCommand(std::string command, Player *player, std::string order = "");
    bool moveLink(Link *link, int x, int y);

    // Getters
    Board *getBoard();
    Player *getPlayer(int playerNum);
    Link *getLink(char c);
    int getMoveNumber();
    bool getHasStarted();
    bool getIsGameOver();

    // Game initialization
    void initializeGame(int playerCount);

    // Command execution methods
    bool executeMoveCommand(char A, std::string dir, Player *player);
    void executeAbilitiesCommand(Player *player);
    bool executeAbilityUseCommand(int abilityIndex, Player *player, std::istream &in);
    void executeBoardCommand(Player *player);
    bool executeSequenceCommand(std::string filename, Player *player);
    void executeQuitCommand();

    // Processes battles between links
    void battle(Link *attacker, Link *defender);

    // Game state management
    void incrementMoveNumber();
    bool gameReady();
    void gameOver();

    ~Game();
};
