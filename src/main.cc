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
    // textDisplay->drawBoard();

    cin.ignore();

    while (!game->getIsGameOver()) {
        Player *currentPlayer = game->getPlayer((game->getMoveNumber()) % playerCount);
        cout << "Player " << currentPlayer->getPlayerNum() + 1 << "'s turn. Enter command: ";
        string command;
        getline(cin, command);
        game->executeCommand(command, currentPlayer);
    }

    // for (auto player : players) {
    //     displayInfo(cout, game->getPlayer(0), player->getPlayerNum() == 0);
    //     board->notifyObservers();
    //     displayInfo(cout, game->getPlayer(1), player->getPlayerNum() == 1);
    //     cout << "Generating links for Player " << player->getPlayerNum() + 1 << ":\n";
    //     player->generateLinks(cin, cout, board);
    //     cout << endl;
    //     clearConsole();
    // }

    game->startGame(0);

    delete game;
}
