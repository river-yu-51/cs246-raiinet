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
    clearConsole();
    Player *currentPlayer = game->getPlayer(game->getMoveNumber() % 2);

    displayInfo(os, game->getPlayer(0), currentPlayer == game->getPlayer(0));
    game->getBoard()->notifyObservers();
    displayInfo(os, game->getPlayer(1), currentPlayer == game->getPlayer(1));
}

int main() {
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

    clearConsole();
    cin.ignore();

    while (game->initL1 == false || game->initL2 == false || game->initA1 == false || game->initA2 == false) {
        clearConsole();
        drawGameState(game, textDisplay, cout);
        cout << "Enter link and ability setup commands for both players. " << endl;
        cout << "Remaining: " << endl;
        if (game->initL1 == false) { cout << "* Player 1 links " << endl; }
        if (game->initL2 == false) { cout << "* Player 2 links " << endl; }
        if (game->initA1 == false) { cout << "* Player 1 abilities " << endl; }
        if (game->initA2 == false) { cout << "* Player 2 abilities " << endl; }
        string command;
        getline(cin, command);
        game->executeCommand(command, game->getPlayer(0));
    }

    while (!game->getIsGameOver()) {
        clearConsole();
        drawGameState(game, textDisplay, cout);

        Player *currentPlayer = game->getPlayer((game->getMoveNumber()) % playerCount);
        cout << "Player " << currentPlayer->getPlayerNum() + 1 << "'s turn. Enter command: ";
        string command;
        getline(cin, command);
        game->executeCommand(command, currentPlayer);
    }

    game->startGame(0);

    delete game;
}
