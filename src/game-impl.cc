module Game;

import <vector>;
import <string>;
import <iostream>;
import <sstream>;
import <fstream>;

import Core;
import Abilities;

Game::Game(Board *board, std::vector<Player*> players, int moveNumber,
           bool hasStarted, bool isGameOver)
    : board{board}, players{players}, moveNumber{moveNumber},
      hasStarted{hasStarted}, isGameOver{isGameOver} {}

void Game::initializeGame(int playerCount) {
    // for now - only 2 player mode
    if (playerCount != 2) {
        std::cerr << "initializeGame: only 2-player mode implemented.\n";
        return;
    }

    auto &grid = board->getGrid();
    int rows = grid.size();
    if (rows == 0) return;
    int cols = grid[0].size();

    int topRow = 0;
    int bottomRow = rows - 1;

    int portCol1 = cols / 2 - 1;
    int portCol2 = cols / 2;

    // set ports
    std::vector<int> portRows = {topRow, bottomRow};
    std::vector<int> portCols = {portCol1, portCol2};

    for (int r : portRows) {
        for (int c : portCols) {
            Tile *tile = board->getTile(r, c);
            tile->setIsPort(true);
            tile->setSymbol('#');
        }
    }

    // place starting symbols
    const std::vector<std::vector<char>> symbolSets = {
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
        {'s', 't', 'u', 'v', 'w', 'x', 'y', 'z'},
        {'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}
    };

    const auto &p1Symbols = symbolSets[players[0]->getPlayerNum() % symbolSets.size()];
    const auto &p2Symbols = symbolSets[players[1]->getPlayerNum() % symbolSets.size()];

    {
        int mainRow = topRow;
        int altRow  = topRow + 1;
        for (int i = 0; i < (int)p1Symbols.size() && i < cols; ++i) {
            int c = i;
            int r = board->getTile(mainRow, c)->getIsPort() ? altRow : mainRow;
            Tile *t = board->getTile(r, c);
            t->setSymbol(p1Symbols[i]);
            // DO NOT setLink yet – will be attached when links are created
        }
    }

    {
        int mainRow = bottomRow;
        int altRow  = bottomRow - 1;
        for (int i = 0; i < (int)p2Symbols.size() && i < cols; ++i) {
            int c = i;
            int r = board->getTile(mainRow, c)->getIsPort() ? altRow : mainRow;
            Tile *t = board->getTile(r, c);
            t->setSymbol(p2Symbols[i]);
            // DO NOT setLink yet
        }
    }

    board->notifyObservers();
}

void Game::startGame(int startingPlayer) {
    hasStarted = true;
    moveNumber = 0;
    // All board geometry should already be set up by initializeGame,
    // and link->tile attachments should be done when players choose placements
}

bool Game::executeCommand(std::string command, Player *player) {
    //if (!hasStarted || isGameOver) return false;
    std::istringstream iss{command};
    std::string action;
    iss >> action;

    // std::cout << "EXECUTING " << command << std::endl;

    if (!iss) {
        std::cout << "Please enter a command." << std::endl;
        return false;
    }
    if (action == "move") {
        char A;
        std::string dir;
        iss >> A >> dir;
        return executeMoveCommand(A, dir, player);
    } else if (action == "abilities") {
        executeAbilitiesCommand(player);
        return false;
    } else if (action == "ability") {
        int abilityIndex;
        iss >> abilityIndex;
        return executeAbilityUseCommand(abilityIndex, player, iss);
    } else if (action == "board") {
        executeBoardCommand(player);
        return false;
    } else if (action == "sequence") {
        std::cout << "sequence";
        std::string filename;
        iss >> filename;
        return executeSequenceCommand(filename, player);
    } else if (action == "quit") {
        executeQuitCommand();
        return true;
    } else if (action == "link1") {
        std::string order;
        iss >> order;
        if (!getPlayer(0)->generateLinks(order, std::cout, board)) {
            std::cout << "Invalid link order." << std::endl;
            return false;
        }
        initL1 = true;
        return true;
    } else if (action == "link2") {
        std::string order;
        iss >> order;
        if (!getPlayer(1)->generateLinks(order, std::cout, board)) {
            std::cout << "Invalid link order." << std::endl;
            return false;
        }
        initL2 = true;
        return true;
    } else if (action == "ability1") {
        std::string order;
        iss >> order;
        if (!generateAbilitiesForPlayer(getPlayer(0), order)) {
            std::cout << "Invalid ability string." << std::endl;
            return false;
        }
        initA1 = true;
        return true;
    } else if (action == "ability2") {
        std::string order;
        iss >> order;
        if (!generateAbilitiesForPlayer(getPlayer(1), order)) {
            std::cout << "Invalid ability string." << std::endl;
            return false;
        }
        initA2 = true;
        return true;
    }

    else {
        std::cout << "Invalid command." << std::endl;
    }
    return false;
}

bool Game::moveLink(Link *link, int x, int y) {
    if (x == -1 && link->getPlayer()->getPlayerNum() == 1) {
        players[1]->download(link);
    } else if (x == board->getGrid().size() && link->getPlayer()->getPlayerNum() == 0) {
        players[0]->download(link);
    }

    Tile *targetTile = board->getTile(x, y);

    if (!targetTile) {
        std::cout << "Invalid move: out of bounds." << std::endl;
        return false;
    }

    if (targetTile->getIsWalled()) {
        std::cout << "Invalid move: tile is walled." << std::endl;
        return false;
    }

    if (targetTile->getLink() && targetTile->getLink()->getPlayer() == link->getPlayer()) {
        std::cout << "Invalid move: cannot attack own link." << std::endl;
        return false;
    }

    if (targetTile->getLink()) {
        battle(link, targetTile->getLink());
    } else if (targetTile->getIsPort()) {
        // 2 player ports for now
        if (targetTile->getX() == 0) {
            players[0]->download(link);
        } else {
            players[1]->download(link);
        }
    } else {
        board->moveLink(link, x, y);
    }

    return true;
}

void Game::useAbility(Ability *ability, const AbilityParam &param) {
    ability->activate(param);
}

bool Game::executeMoveCommand(char A, std::string dir, Player *player) {
    for (Link *link : player->getLinks()) {
        if (link->getSymbol() == A && link->getTile()) {
            int x = link->getTile()->getX(); // row
            int y = link->getTile()->getY(); // col

            // up/down should change row (x), left/right change col (y)
            if (dir == "up") {
                x -= 1;
            } else if (dir == "down") {
                x += 1;
            } else if (dir == "left") {
                y -= 1;
            } else if (dir == "right") {
                y += 1;
            } else {
                std::cout << "Invalid direction." << std::endl;
                return false;
            }
            moveLink(link, x, y);
            return true;
        }
    }
    std::cout << "Link " << A << " not found." << std::endl;
    return false;
}

void Game::executeAbilitiesCommand(Player *player) {
    std::cout << "Abilities:" << std::endl;
    for (size_t i = 0; i < player->getAbilities().size(); ++i) {
        std::cout << i + 1 << ". " << player->getAbilities()[i]->getType() << std::endl;
    }
}

bool Game::executeAbilityUseCommand(int abilityIndex, Player *player, std::istream &in) {
    if (abilityIndex < 1 || abilityIndex > static_cast<int>(player->getAbilities().size())) {
        std::cout << "Invalid ability index." << std::endl;
        return false;
    }
    Ability *ability = player->getAbilities()[abilityIndex - 1];

    if (ability->getType() == AbilityType::Download) {
        Link *targetLink = nullptr;
        while (!targetLink) {
            std::cout << "Specify link to download (symbol): ";
            char linkSymbol;
            in >> linkSymbol;
            for (auto &row : board->getGrid()) {
                for (Tile *tile : row) {
                    Link *link = tile->getLink();
                    if (link && link->getSymbol() == linkSymbol) {
                        targetLink = link;
                        break;
                    }
                }
                if (targetLink) break;
            }
            if (!targetLink) {
                std::cout << "Link not found." << std::endl;
            }
        }
        AbilityParam param{player, targetLink, nullptr, nullptr};
        useAbility(ability, param);
        return true;

    } else if (ability->getType() == AbilityType::Firewall) {
        Tile *targetTile = nullptr;
        while (!targetTile) {
            std::cout << "Specify tile to place firewall (x y): ";
            int x, y;
            in >> x >> y;
            if (x < 0 || x >= static_cast<int>(board->getGrid().size()) ||
                y < 0 || y >= static_cast<int>(board->getGrid()[0].size())) {
                std::cout << "Invalid tile coordinates." << std::endl;
                continue;
            }
            targetTile = board->getTile(x, y);
        }
        AbilityParam param{player, nullptr, nullptr, targetTile};
        useAbility(ability, param);
        return true;

    } else if (ability->getType() == AbilityType::LinkBoost) {
        Link *targetLink = nullptr;
        while (!targetLink) {
            std::cout << "Specify link to boost (symbol): ";
            char linkSymbol;
            in >> linkSymbol;
            for (Link *link : player->getLinks()) {
                if (link->getSymbol() == linkSymbol) {
                    targetLink = link;
                    break;
                }
            }
            if (!targetLink) {
                std::cout << "Link not found." << std::endl;
            }
        }
        AbilityParam param{player, targetLink, nullptr, nullptr};
        useAbility(ability, param);
        return true;

    } else if (ability->getType() == AbilityType::Scan) {
        Tile *targetTile = nullptr;
        while (!targetTile) {
            std::cout << "Specify tile to scan (x y): ";
            int x, y;
            in >> x >> y;
            if (x < 0 || x >= static_cast<int>(board->getGrid().size()) ||
                y < 0 || y >= static_cast<int>(board->getGrid()[0].size())) {
                std::cout << "Invalid tile coordinates." << std::endl;
                continue;
            }
            targetTile = board->getTile(x, y);
        }
        AbilityParam param{player, nullptr, nullptr, targetTile};
        useAbility(ability, param);
        return true;

    } else if (ability->getType() == AbilityType::Upgrade) {
        Link *targetLink = nullptr;
        while (!targetLink) {
            std::cout << "Specify link to upgrade (symbol): ";
            char linkSymbol;
            in >> linkSymbol;
            for (Link *link : player->getLinks()) {
                if (link->getSymbol() == linkSymbol) {
                    targetLink = link;
                    break;
                }
            }
            if (!targetLink) {
                std::cout << "Link not found." << std::endl;
            }
        }
        AbilityParam param{player, targetLink, nullptr, nullptr};
        useAbility(ability, param);
        return true;

    } else if (ability->getType() == AbilityType::Polarize) {
        Tile *targetTile = nullptr;
        while (!targetTile) {
            std::cout << "Specify tile to polarize (x y): ";
            int x, y;
            in >> x >> y;
            if (x < 0 || x >= static_cast<int>(board->getGrid().size()) ||
                y < 0 || y >= static_cast<int>(board->getGrid()[0].size())) {
                std::cout << "Invalid tile coordinates." << std::endl;
                continue;
            }
            targetTile = board->getTile(x, y);
        }
        AbilityParam param{player, nullptr, nullptr, targetTile};
        useAbility(ability, param);
        return true;

    } else if (ability->getType() == AbilityType::Immunity) {
        Link *targetLink = nullptr;
        while (!targetLink) {
            std::cout << "Specify link to grant immunity (symbol): ";
            char linkSymbol;
            in >> linkSymbol;
            for (Link *link : player->getLinks()) {
                if (link->getSymbol() == linkSymbol) {
                    targetLink = link;
                    break;
                }
            }
            if (!targetLink) {
                std::cout << "Link not found." << std::endl;
            }
        }
        AbilityParam param{player, targetLink, nullptr, nullptr};
        useAbility(ability, param);
        return true;

    } else if (ability->getType() == AbilityType::Wall) {
        Tile *targetTile = nullptr;
        while (!targetTile) {
            std::cout << "Specify tile to place wall (x y): ";
            int x, y;
            in >> x >> y;
            if (x < 0 || x >= static_cast<int>(board->getGrid().size()) ||
                y < 0 || y >= static_cast<int>(board->getGrid()[0].size())) {
                std::cout << "Invalid tile coordinates." << std::endl;
                continue;
            }
            targetTile = board->getTile(x, y);
        }
        AbilityParam param{player, nullptr, nullptr, targetTile};
        useAbility(ability, param);
        return true;
    }

    std::cout << "Ability not found." << std::endl;
    return false;
}

void Game::executeBoardCommand(Player *viewer) {
    // assume players[0] is Player 1, players[1] is Player 2
    Player *p1 = players[0];
    Player *p2 = players[1];

    bool viewerIsP1 = (viewer == p1);
    bool viewerIsP2 = (viewer == p2);

    // player 1 info (reveal if viewer is P1)
    displayInfo(std::cout, p1, viewerIsP1);

    board->notifyObservers(); // draws board

    // player 2 info (reveal if viewer is P2)
    displayInfo(std::cout, p2, viewerIsP2);
}

bool Game::executeSequenceCommand(std::string filename, Player *player) {
    std::ifstream file{filename};
    if (!file) {
        std::cout << "Could not open file: " << filename << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        executeCommand(line, player);

        if (isGameOver) { return true; } // stop if game over
    }
    return false;
}

void Game::executeQuitCommand() {
    isGameOver = true;
    std::cout << "Game over. Thanks for playing!" << std::endl;
}

Board *Game::getBoard() { return board; }
Player *Game::getPlayer(int playerNum) { return players[playerNum]; }
int Game::getMoveNumber() { return moveNumber; }
bool Game::getHasStarted() { return hasStarted; }
bool Game::getIsGameOver() { return isGameOver; }

void Game::battle(Link *attacker, Link *defender) {
    Link *winner = nullptr;
    Link *loser = nullptr;

    if (attacker->getStrength() >= defender->getStrength()) {
        winner = attacker;
        loser = defender;
    } else {
        winner = defender;
        loser = attacker;
    }

    Tile *tile = loser->getTile();
    if (tile) {
        tile->setLink(nullptr);
    }

    auto &loserLinks = loser->getPlayer()->getLinks();
    for (auto it = loserLinks.begin(); it != loserLinks.end(); ++it) {
        if (*it == loser) {
            loserLinks.erase(it);
            break;
        }
    }

    if (tile) {
        winner->setTile(tile);
        tile->setLink(winner);
    }

    winner->getPlayer()->download(loser);  // will delete loser
}

bool Game::getAbility1() { return p1Ability; }
bool Game::getAbility2() { return p2Ability; }
bool Game::getLinks1() { return p1Links; }
bool Game::getLinks2() { return p2Links; }
void Game::setAbility1(bool set) { p1Ability = set; }
void Game::setAbility2(bool set) { p2Ability = set; }
void Game::setLinks1(bool set) { p1Links = set; }
void Game::setLinks2(bool set) { p2Links = set; }

void Game::incrementMoveNumber() { moveNumber++; }

bool Game::gameReady() {
    return p1Ability && p2Ability && p1Links && p2Links;
}

void Game::gameOver() {
    isGameOver = true;
    // other stuff idk
}
