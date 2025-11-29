module Game;

import <vector>;
import <string>;
import <iostream>;
import <sstream>;
import <fstream>;

import Core;
import Abilities;
import Display;

Game::Game(
    Board *board,
    std::vector<Player*> players,
    int moveNumber,
    bool hasStarted,
    bool isGameOver) : board{board}, players{players}, moveNumber{moveNumber}, hasStarted{hasStarted}, isGameOver{isGameOver} {}

void Game::initializeGame(int playerCount) {
    // for now - only 2 player mode
    if (playerCount != 2) {
        std::cerr << "initializeGame: only 2-player mode implemented.\n";
        return;
    }

    // set up board
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

    // assign symbols to players
    const auto &p1Symbols = symbolSets[players[0]->getPlayerNum() % symbolSets.size()];
    const auto &p2Symbols = symbolSets[players[1]->getPlayerNum() % symbolSets.size()];

    int mainRow = topRow;
    int altRow  = topRow + 1;
    for (int i = 0; i < (int)p1Symbols.size() && i < cols; ++i) {
        int c = i;
        int r = board->getTile(mainRow, c)->getIsPort() ? altRow : mainRow;
        Tile *t = board->getTile(r, c);
        t->setSymbol(p1Symbols[i]);
        // DO NOT setLink yet – will be attached when links are created
    }

    mainRow = bottomRow;
    altRow  = bottomRow - 1;
    for (int i = 0; i < (int)p2Symbols.size() && i < cols; ++i) {
        int c = i;
        int r = board->getTile(mainRow, c)->getIsPort() ? altRow : mainRow;
        Tile *t = board->getTile(r, c);
        t->setSymbol(p2Symbols[i]);
        // DO NOT setLink yet - will be attached when links are created
    }

    board->notifyObservers();
}

void Game::startGame(int startingPlayer) {
    hasStarted = true;
    moveNumber = 0;
}

// Executes a command string for the given player
bool Game::executeCommand(std::string command, Player *player, std::string order) {
    std::istringstream iss{command};
    std::string action;
    iss >> action;

    if (!iss) { // empty command
        std::cout << "Please enter a command." << std::endl;
        return false;
    }
    if (action == "move") { // move command
        char A;
        std::string dir;
        iss >> A >> dir;
        return executeMoveCommand(A, dir, player);
    } else if (action == "abilities") { // display abilities
        executeAbilitiesCommand(player);
        return false;
    } else if (action == "ability") { // use ability
        int abilityIndex;
        iss >> abilityIndex;
        if (abilityIndex < 0 || abilityIndex > static_cast<int>(player->getAbilities().size()) - 1) {
            std::cout << "Ability index out of bounds." << std::endl;
            return false;
        }
        Ability *targetAbility = player->getAbilities()[abilityIndex];
        if (!targetAbility->isAvailable()) {
            std::cout << "Ability already used." << std::endl;
            return false;
        } else {
            switch(targetAbility->getType()) {
                case AbilityType::Download: {
                    char c;
                    iss >> c;
                    Link *l = getLink(c);
                    if (!l) {
                        std::cout << "Invalid link symbol." << std::endl;
                        return false;
                    } else if (l->isImmune()) {
                        std::cout << "Link is immune." << std::endl;
                        return false;
                    } else if (l->isDownloaded()) {
                        std::cout << "Link is already downloaded." << std::endl;
                        return false;
                    }
                    AbilityParam param{player, l, nullptr, nullptr};
                    targetAbility->setAvailable(false);
                    return targetAbility->activate(param);
                }
                case AbilityType::LinkBoost: {
                    char c;
                    iss >> c;
                    Link *l = getLink(c);
                    if (!l) {
                        std::cout << "Invalid link symbol." << std::endl;
                        return false;
                    } else if (l->isDownloaded()) {
                        std::cout << "Link is already downloaded." << std::endl;
                        return false;
                    }
                    AbilityParam param{player, l, nullptr, nullptr};
                    targetAbility->setAvailable(false);
                    return targetAbility->activate(param);
                }
                case AbilityType::Firewall: {
                    int x, y;
                    iss >> x >> y;
                    Tile *tile = board->getTile(x, y);
                    if (!tile) {
                        std::cout << "Invalid tile coordinates." << std::endl;
                        return false;
                    }
                    else if (tile->getIsWalled()) {
                        std::cout << "Tile is already walled." << std::endl;
                        return false;
                    }
                    else if (tile->getLink()) {
                        std::cout << "Tile is currently occupied by a link." << std::endl;
                        return false;
                    }
                    else if (tile->getFirewallPlayer() == 0 || tile->getFirewallPlayer() == 1) {
                        std::cout << "Tile is firewalled." << std::endl;
                        return false;
                    }
                    AbilityParam param{player, nullptr, nullptr, tile};
                    targetAbility->setAvailable(false);
                    return targetAbility->activate(param);
                }
                case AbilityType::Immunity: {
                    char c;
                    iss >> c;
                    Link *l = getLink(c);
                    if (!l) {
                        std::cout << "Invalid link symbol." << std::endl;
                        return false;
                    } else if (l->isDownloaded()) {
                        std::cout << "Link is already downloaded." << std::endl;
                        return false;
                    }
                    AbilityParam param{player, l, nullptr, nullptr};
                    targetAbility->setAvailable(false);
                    return targetAbility->activate(param);
                }
                case AbilityType::Polarize: {
                    char c;
                    iss >> c;
                    Link *l = getLink(c);
                    if (!l) {
                        std::cout << "Invalid link symbol." << std::endl;
                        return false;
                    } else if (l->isImmune()) {
                        std::cout << "Link is immune." << std::endl;
                        return false;
                    } else if (l->isDownloaded()) {
                        std::cout << "Link is already downloaded." << std::endl;
                        return false;
                    }
                    AbilityParam param{player, l, nullptr, nullptr};
                    targetAbility->setAvailable(false);
                    return targetAbility->activate(param);
                }
                case AbilityType::Scan: { 
                    char c;
                    iss >> c;
                    Link *l = getLink(c);
                    if (!l) {
                        std::cout << "Invalid link symbol." << std::endl;
                        return false;
                    } else if (l->isImmune()) {
                        std::cout << "Link is immune." << std::endl;
                        return false;
                    } else if (l->isDownloaded()) {
                        std::cout << "Link is already downloaded." << std::endl;
                        return false;
                    }
                    AbilityParam param{player, l, nullptr, nullptr};
                    targetAbility->setAvailable(false);
                    return targetAbility->activate(param);
                }
                case AbilityType::Upgrade: {
                    char c;
                    iss >> c;
                    Link *l = getLink(c);
                    if (!l) {
                        std::cout << "Invalid link symbol." << std::endl;
                        return false;
                    } else if (l->getStrength() == 4) {
                        std::cout << "Link is already at max strength." << std::endl;
                        return false;
                    } else if (l->isDownloaded()) {
                        std::cout << "Link is already downloaded." << std::endl;
                        return false;
                    }
                    AbilityParam param{player, l, nullptr, nullptr};
                    targetAbility->setAvailable(false);
                    return targetAbility->activate(param);
                }
                case AbilityType::Wall: {
                    int x, y;
                    iss >> x >> y;
                    Tile *tile = board->getTile(x, y);
                    if (!tile) {
                        std::cout << "Invalid tile coordinates." << std::endl;
                        return false;
                    }
                    if (tile->getIsWalled()) {
                        std::cout << "Tile is already walled." << std::endl;
                        return false;
                    } else if (tile->getLink()) {
                        std::cout << "Tile is currently occupied by a link." << std::endl;
                        return false;
                    }
                    else if (tile->getFirewallPlayer() == 0 || tile->getFirewallPlayer() == 1) {
                        std::cout << "Tile is firewalled." << std::endl;
                        return false;
                    }
                    AbilityParam param{player, nullptr, nullptr, tile};
                    targetAbility->setAvailable(false);
                    return targetAbility->activate(param);

                }
            }
            return false;
        }
        return false;
    } else if (action == "board") { // display board
        executeBoardCommand(player);
        return false;
    } else if (action == "sequence") { // execute sequence from file
        std::string filename;
        iss >> filename;
        executeSequenceCommand(filename, player);
        // sequence toggled the turn once at the end of execution, so we need to change it back
        incrementMoveNumber();
        return true;
    } else if (action == "quit") { // quit game
        executeQuitCommand();
        return true;
    } else if (action == "-link1") { // generate links for player 1
        if (!getPlayer(0)->generateLinks(order, std::cout, board)) {
            std::cout << "hello";
            std::cout << order;
            std::cout << "Invalid link order." << std::endl;
            return false;
        }
        return true;
    } else if (action == "-link2") { // generate links for player 2
        if (!getPlayer(1)->generateLinks(order, std::cout, board)) {
            std::cout << "Invalid link order." << std::endl;
            return false;
        }
        return true;
    } else if (action == "-ability1") { // generate abilities for player 1
        if (!generateAbilitiesForPlayer(getPlayer(0), order)) {
            std::cout << "Invalid ability string." << std::endl;
            return false;
        }
        return true;
    } else if (action == "-ability2") { // generate abilities for player 2
        if (!generateAbilitiesForPlayer(getPlayer(1), order)) {
            std::cout << "Invalid ability string." << std::endl;
            return false;
        }
        return true;
    } else { // invalid command
        std::cout << "Invalid command." << std::endl;
    }
    return false;
}

// Gets the link with the given symbol
Link* Game::getLink(char c) {
    // search both players' links
    std::vector<Link*>& p1Links = players[0]->getLinks();
    for (size_t i = 0; i < p1Links.size(); i++) {
        Link* currLink = p1Links[i];
        if (currLink->getSymbol() == c) {
            return currLink;
        }
    }
    std::vector<Link*>& p2Links = players[1]->getLinks();
    for (size_t i = 0; i < p2Links.size(); i++) {
        Link* currLink = p2Links[i];
        if (currLink->getSymbol() == c) {
            return currLink;
        }
    }
    return nullptr; // not found
}

// Increments the move number
bool Game::moveLink(Link *link, int x, int y) {
    auto &grid = board->getGrid();
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    // top/bottom: download, left/right: out of bounds
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        if (x == -1 && link->getPlayer()->getPlayerNum() == 1) {
            players[1]->download(link);
            return true;
        } else if (x == rows && link->getPlayer()->getPlayerNum() == 0) {
            players[0]->download(link);
            return true;
        }

        std::cout << "Invalid move: out of bounds." << std::endl;
        return false;
    }

    Tile *targetTile = board->getTile(x, y);

    if (targetTile->getIsWalled()) {
        std::cout << "Invalid move: tile is walled." << std::endl;
        return false;
    }
    Player *player = link->getPlayer();
    if (targetTile->getFirewallPlayer() != player->getPlayerNum() && targetTile->getFirewallPlayer() != -1) {
        // player stepped on a firewall
        if (link->getType() == "virus") {
            std::cout << "firewall virus" << std::endl;
            player->download(link);
            return true;
        }
    }

    // Check if the target tile has a link belonging to the same player
    if (targetTile->getLink() &&
        targetTile->getLink()->getPlayer() == link->getPlayer()) {
        std::cout << "Invalid move: cannot attack own link." << std::endl;
        return false;
    }

    if (targetTile->getLink()) { // target tile has a link - must be opponent's
        battle(link, targetTile->getLink());
    } else if (targetTile->getIsPort()) {
        int portSideOwner = (targetTile->getX() == 0 ? 0 : 1);  // top row -> player 0, bottom row -> player 1
        int mover = link->getPlayer()->getPlayerNum();

        if (mover == portSideOwner) {
            std::cout << "Invalid move: cannot enter own server port." << std::endl;
            return false;
        } else {
            players[portSideOwner]->download(link);
            return true;
        }
    } else { // empty tile - move link
        board->moveLink(link, x, y);
    }

    return true;
}

// Executes a move command for the given player
bool Game::executeMoveCommand(char A, std::string dir, Player *player) {
    for (Link *link : player->getLinks()) {
        if (link->getSymbol() == A && link->getTile()) {
            int x = link->getTile()->getX(); // row
            int y = link->getTile()->getY(); // col
            int dist = link->getDistance();

            // up/down should change row (x), left/right change col (y)
            if (dir == "up") {
                x -= dist;
            } else if (dir == "down") {
                x += dist;
            } else if (dir == "left") {
                y -= dist;
            } else if (dir == "right") {
                y += dist;
            } else {
                std::cout << "Invalid direction." << std::endl;
                return false;
            }
            return moveLink(link, x, y);
        }
    }
    std::cout << "Link " << A << " not found." << std::endl;
    return false;
}

// Displays the abilities of the given player
void Game::executeAbilitiesCommand(Player *player) {
    std::cout << "Abilities:" << std::endl;
    for (size_t i = 0; i < player->getAbilities().size(); ++i) {
        if (!player->getAbilities()[i]->isAvailable()) {
            std::cout << i << ". " << player->getAbilities()[i]->getType() << " [used]" << std::endl;
        }
        else {
            std::cout << i << ". " << player->getAbilities()[i]->getType() << std::endl;
        }
    }
        
}

// Displays the board and player info for the given viewer
void Game::executeBoardCommand(Player *viewer) {
    // assume players[0] is Player 1, players[1] is Player 2
    Player *p1 = players[0];
    Player *p2 = players[1];

    bool viewerIsP1 = (viewer == p1);
    bool viewerIsP2 = (viewer == p2);

    // player 1 info (reveal if viewer is P1)
    Display::displayInfo(std::cout, p1, viewerIsP1);

    board->notifyObservers(); // draws board

    // player 2 info (reveal if viewer is P2)
    Display::displayInfo(std::cout, p2, viewerIsP2);
}

// Executes a sequence of commands from a file for the given starting player
bool Game::executeSequenceCommand(std::string filename, Player *startingPlayer) {
    std::ifstream file{filename};

    if (!file) { // file could not be opened
        std::cout << "Could not open file: " << filename << std::endl;
        return false;
    }

    Player *currentPlayer = startingPlayer;
    std::string line;

    while (std::getline(file, line) && !isGameOver) {
        if (line.empty()) continue;

        // execute command
        bool endTurn = executeCommand(line, currentPlayer);

        if (isGameOver) { return true; }

        // switch player
        if (endTurn) {
            int idx = currentPlayer->getPlayerNum(); // 2 players only
            currentPlayer = players[1 - idx];
            incrementMoveNumber();
        }

        // check for win/elimination
        if (currentPlayer->getIsWon() || currentPlayer->getIsEliminated()) { return true; }
    }

    return true;
}


// Quit game
void Game::executeQuitCommand() {
    isGameOver = true;
    std::cout << "Game over. Thanks for playing!" << std::endl;
}

Board *Game::getBoard() { return board; }
Player *Game::getPlayer(int playerNum) { return players[playerNum]; }
int Game::getMoveNumber() { return moveNumber; }
bool Game::getHasStarted() { return hasStarted; }
bool Game::getIsGameOver() { return isGameOver; }

// Handles a battle between two links
void Game::battle(Link *attacker, Link *defender) {
    if (!attacker || !defender) return; // safety check

    Tile *attackerTile = attacker->getTile();
    Tile *defenderTile = defender->getTile();

    if (!attackerTile || !defenderTile) { return; } // safety check

    // reveal both links to both players
    attacker->reveal();
    defender->reveal();

    bool attackerWins = (attacker->getStrength() >= defender->getStrength()); // attacker wins ties

    if (attackerWins) { // move attacker to defender's tile, download defender
        Tile *oldDefenderTile = defenderTile;
        attacker->getPlayer()->download(defender);

        if (attackerTile->getLink() == attacker) { attackerTile->setLink(nullptr); }

        attacker->setTile(oldDefenderTile);
        if (oldDefenderTile) {
            oldDefenderTile->setLink(attacker);
        }
    } else { // download attacker, defender stays in place
        Tile *oldAttackerTile = attackerTile;
        defender->getPlayer()->download(attacker);

        if (oldAttackerTile && oldAttackerTile->getLink() == attacker) {
            oldAttackerTile->setLink(nullptr);
        }
    }

    board->notifyObservers();
}

void Game::incrementMoveNumber() { moveNumber++; }

void Game::gameOver() { isGameOver = true; }

// Game owns its players and board
Game::~Game() {
    for (Player *player : players) {
        delete player;
    }
    delete board;
}
