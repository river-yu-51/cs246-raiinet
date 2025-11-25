import <vector>;
import <iostream>;
import <string>;

import Core;
import Game;
import Display;
import Abilities;
import Observer;
import Subject;

using namespace std;

int main() {
    int playerCount = 0;
    while (playerCount != 2 && playerCount != 4) {
        cout << "Enter number of players (2 or 4): ";
        cin >> playerCount;
    }
    cin.ignore(); // to clear the newline character from the input buffer
    vector<Player*> players;
    for (int i = 0; i < playerCount; ++i) {
        // For simplicity, players have no links or abilities initially
        players.push_back(new Player{i, {}, {}, {}, false, 0, 0});
    }
    int rows = (playerCount == 2) ? 8 : 10;
    int cols = rows;

    vector<vector<Tile*>> grid(rows, vector<Tile*>(cols, nullptr));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = new Tile{i, j, '.', false, false, nullptr, -1};
        }
    }

    Board *board = new Board{grid};
    Game *game = new Game{board, players, 0, false, false};

    for (auto player : players) {
        cout << "Generating links for Player " << player->getPlayerNum() + 1 << ":\n";
        player->generateLinks(cin, cout);
    }

    TextDisplay *textDisplay = new TextDisplay{board, 0, false}; // default for now
    board->attach(textDisplay);
    game->startGame(0);

    int lastRow = rows - 1;

    for (int i = 0; i < cols; i++) {
        Tile *tileTop = board->getTile(0, i);
        Tile *tileBottom = board->getTile(lastRow, i);

        Link *linkTop = players[0]->getLinks()[i];
        Link *linkBottom = players[1]->getLinks()[i];

        tileTop->setLink(linkTop);
        linkTop->setTile(tileTop);
        tileBottom->setLink(linkBottom);
        linkBottom->setTile(tileBottom);
    }

    while (!game->getIsGameOver()) {
        Player *p = players[game->getMoveNumber() % playerCount];
        cout << "Player " << p->getPlayerNum() + 1 << "'s turn." << endl;
        string command;
        cout << "Enter command: ";
        getline(cin, command);
        if (game->executeCommand(command, p)) {
            game->getBoard()->notifyObservers();
            game->setMoveNumber(game->getMoveNumber() + 1);
        }
    }

    // Cleanup
    for (auto player : players) { delete player; }
    delete board;
    delete textDisplay;
    delete game;
}
