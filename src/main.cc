import <vector>;
import <iostream>;
import <string>;
import <sstream>;
import <fstream>;

import Core;
import Game;
import Display;
import Abilities;
import Observer;
import Subject;

using namespace std;

void clearConsole() {
    // ANSI escape code to clear screen
    cout << "\033[2J\033[1;1H";
}

void drawGameState(Game *game, Display *display, ostream &os, bool isGraphics) {
    os << "Current game state:" << endl;
    Player *currentPlayer = game->getPlayer(game->getMoveNumber() % 2);
    display->setCurrentPlayer(currentPlayer->getPlayerNum());

    if (!isGraphics) Display::displayInfo(os, game->getPlayer(0), currentPlayer == game->getPlayer(0));
    game->getBoard()->notifyObservers();
    if (!isGraphics) Display::displayInfo(os, game->getPlayer(1), currentPlayer == game->getPlayer(1));
}

int main(int argc, char * argv[]) {
    int playerCount = 2; // only 2 players for now

    // set graphics if applicable
    bool useGraphics = false;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-graphics") {
            useGraphics = true;
            break;
        }
    }

    // create players
    vector<Player*> players;
    for (int i = 0; i < playerCount; ++i) {
        players.push_back(new Player{i, {}, {}, false, false, 0, 0});
    }

    // create board
    int rows = 8;
    int cols = rows;
    vector<vector<Tile*>> grid(rows, vector<Tile*>(cols, nullptr));

    // initialize tiles
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[r][c] = new Tile{nullptr, r, c, -1, false, false, '.'};
        }
    }

    // create game
    Board *board = new Board{grid};
    Game *game   = new Game{board, players, 0, false, false};

    // attach display
    Display *display = nullptr;
    if (useGraphics) { display = new GraphicsDisplay{board, players, 0, false}; }
    else { display = new TextDisplay{board, 0, false}; }

    board->attach(display);

    game->initializeGame(playerCount);

    std::string command;
    std::string order;

    int i = 1;
    while (i < argc) {
        std::string arg = argv[i];

        // skip, handled earlier
        if (arg == "-graphics") {
            ++i;
            continue;
        }

        // options that require an order string
        if (arg == "-ability1" || arg == "-link1" ||
            arg == "-ability2" || arg == "-link2") {

            if (i + 1 >= argc) {
                std::cerr << "Missing argument for " << arg << "\n";
                break;
            }

            std::string ord = argv[i + 1];
            Player *target = (arg == "-ability1" || arg == "-link1") ?
                game->getPlayer(0) : game->getPlayer(1);

            game->executeCommand(arg, target, ord);

            // mark which ones were explicitly initialized by the user
            if (arg == "-ability1") game->initA1 = true;
            else if (arg == "-ability2") game->initA2 = true;
            else if (arg == "-link1") game->initL1 = true;
            else if (arg == "-link2") game->initL2 = true;

            i += 2;
        } else {
            std::cerr << "Unknown command line argument: " << arg << "\n";
            ++i;
        }
    }

    // apply defaults if applicable
    if (!game->initA1) game->executeCommand("-ability1", game->getPlayer(0), "LFDSP");
    if (!game->initA2) game->executeCommand("-ability2", game->getPlayer(1), "LFDSP");
    if (!game->initL1) game->executeCommand("-link1",    game->getPlayer(0), "V1V2V3V4D1D2D3D4");
    if (!game->initL2) game->executeCommand("-link2",    game->getPlayer(1), "V1V2V3V4D1D2D3D4");

    game->startGame(0);

    while (!game->getIsGameOver()) {
        drawGameState(game, display, cout, useGraphics);

        Player *currentPlayer = game->getPlayer(game->getMoveNumber() % playerCount);

        // get next command
        std::string line;
        bool endTurn = false;
        while (!endTurn) {
            cout << "Player " << currentPlayer->getPlayerNum() + 1
                 << "'s turn. Enter command: ";
            std::getline(cin, line);
            endTurn = game->executeCommand(line, currentPlayer);
        }

        game->incrementMoveNumber();

        // check if game is over
        if (currentPlayer->getIsWon()) {
            cout << "Player " << currentPlayer->getPlayerNum() + 1
                 << " has won the game!" << endl;
            game->gameOver();
        } else if (currentPlayer->getIsEliminated()) {
            cout << "Player " << currentPlayer->getPlayerNum() + 1
                 << " has been eliminated!\nPlayer "
                 << (1 - currentPlayer->getPlayerNum() + 1)
                 << " wins!" << endl;
            game->gameOver();
        }
    }

    // clean up (game dtor auto deletes board and players)
    delete display;
    delete game;
}
