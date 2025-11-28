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

void drawGameState(Game *game, Display *display, ostream &os) {
    os << "Current game state:" << endl;
    Player *currentPlayer = game->getPlayer(game->getMoveNumber() % 2);

    displayInfo(os, game->getPlayer(0), currentPlayer == game->getPlayer(0));
    game->getBoard()->notifyObservers();
    displayInfo(os, game->getPlayer(1), currentPlayer == game->getPlayer(1));
}

int main(int argc, char * argv[]) {
    int playerCount = 0;
    while (playerCount != 2  /*&& playerCount != 4 */) {
        cout << "Enter number of players [ONLY 2]: ";
        cin >> playerCount;
    }
    vector<Player*> players;
    for (int i = 0; i < playerCount; ++i) {
        // For simplicity, players have no links or abilities initially
        players.push_back(new Player{i, {}, {}, {}, false, false, 0, 0});
    }

    int rows = 8; // 2 player default
    int cols = rows;

    vector<vector<Tile*>> grid(rows, vector<Tile*>(cols, nullptr));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = new Tile{nullptr, i, j, -1, false, false, '.'};
        }
    }

    Board *board = new Board{grid};
    Game *game = new Game{board, players, 0, false, false};

    TextDisplay *textDisplay = new TextDisplay{board, 0, false}; // default for now
    board->attach(textDisplay);


    game->initializeGame(playerCount);

    //clearConsole();
    cin.ignore();

    std::string command;
    std::string order;
    for (int i = 1; i+1 < argc; i+=2) {
        command = argv[i];
        order = argv[i+1];
        game->executeCommand(command, game->getPlayer(0), order);
    }

    if (!game->gameReady()) {
        if (!game->getAbility1()) {
            game->executeCommand("-ability1", game->getPlayer(0), "LFDSP");
        }
        if (!game->getAbility2()) {
            game->executeCommand("-ability2", game->getPlayer(1), "LFDSP");
        }
        if (!game->getLinks1()) {
            game->executeCommand("-link1", game->getPlayer(0), "V1V2V3V4D1D2D3D4");
        }
        if (!game->getLinks2()) {
            game->executeCommand("-link2", game->getPlayer(1), "V1V2V3V4D1D2D3D4");
        }
    }
    
    game->startGame(0);

    while (!game->getIsGameOver()) {
        //clearConsole();
        drawGameState(game, textDisplay, cout);

        Player *currentPlayer = game->getPlayer((game->getMoveNumber()) % playerCount);

        string command;
        bool endTurn = false;
        while (!endTurn) {
            cout << "Player " << currentPlayer->getPlayerNum() + 1 << "'s turn. Enter command: ";

            
            getline(cin, command);

            endTurn = game->executeCommand(command, currentPlayer);
        }

        game->incrementMoveNumber();

        if (currentPlayer->getIsWon()) {
            cout << "Player " << currentPlayer->getPlayerNum() + 1 << " has won the game!" << endl;
            game->gameOver();
        } else if (currentPlayer->getIsEliminated()) {
            cout << "Player " << currentPlayer->getPlayerNum() + 1 << " has been eliminated!\nPlayer " << 1 - currentPlayer->getPlayerNum() + 1 << " wins!" << endl;
            game->gameOver();
        }
    }
    

    delete game;
}
