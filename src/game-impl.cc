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

bool Game::executeCommand(std::string command, Player *player, std::string order) {
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
                    int x, y;
                    iss >> x >> y;
                    Tile *tile = board->getTile(x, y);
                    if (!tile) {
                        std::cout << "Invalid tile coordinates." << std::endl;
                        return false;
                    }
                    Link *link = tile->getLink();
                    if (!link) {
                        std::cout << "No link on specified tile." << std::endl;
                        return false;
                    }

                    AbilityParam param{player, link, nullptr, nullptr};
                    
                    return targetAbility->activate(param);
                }
                case AbilityType::LinkBoost: {
                    char c;
                    iss >> c;
                    std::cout << c;
                    Link *l = getLink(c);
                    if (!l) {
                        std::cout << "Invalid link symbol." << std::endl;
                        return false;
                    }
                    AbilityParam param{player, l, nullptr, nullptr};
                    targetAbility->setAvailable(false);
                    return targetAbility->activate(param);
                }
                case AbilityType::Firewall: { // not done
                    int x, y;
                    iss >> x >> y;
                    Tile *tile = board->getTile(x, y);
                    if (!tile) {
                        std::cout << "Invalid tile coordinates." << std::endl;
                        return false;
                    }

                    AbilityParam param{player, nullptr, nullptr, tile};
                    targetAbility->setAvailable(false);
                    return targetAbility->activate(param);
                }
                case AbilityType::Immunity: {
                    char c;
                    iss >> c;
                    std::cout << c;
                    Link *l = getLink(c);
                    if (!l) {
                        std::cout << "Invalid link symbol." << std::endl;
                        return false;
                    }
                    AbilityParam param{player, l, nullptr, nullptr};
                    targetAbility->setAvailable(false);
                    return targetAbility->activate(param);
                }
                case AbilityType::Polarize: { // not done
                    char c;
                    iss >> c;
                    std::cout << c;
                    Link *l = getLink(c);
                    if (!l) {
                        std::cout << "Invalid link symbol." << std::endl;
                        return false;
                    }
                    AbilityParam param{player, l, nullptr, nullptr};
                    targetAbility->setAvailable(false);
                    return targetAbility->activate(param);
                }
                case AbilityType::Scan: { 
                    char c;
                    iss >> c;
                    std::cout << c;
                    Link *l = getLink(c);
                    if (!l) {
                        std::cout << "Invalid link symbol." << std::endl;
                        return false;
                    }
                    else if (l->isImmune()) {
                        std::cout << "Link is immune." << std::endl;
                        return false;
                    }
                    AbilityParam param{player, l, nullptr, nullptr};
                    targetAbility->setAvailable(false);
                    return targetAbility->activate(param);
                }
                case AbilityType::Upgrade: {
                    char c;
                    iss >> c;
                    std::cout << c;
                    Link *l = getLink(c);
                    if (!l) {
                        std::cout << "Invalid link symbol." << std::endl;
                        return false;
                    }
                    else if (l->getStrength() == 4) {
                        std::cout << "Link is already at max strength." << std::endl;
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
                    if (tile->getIsWalled()) {
                        std::cout << "Tile is already walled." << std::endl;
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
    } else if (action == "board") {
        executeBoardCommand(player);
        return false;
    } else if (action == "sequence") {
        std::cout << "sequence";
        std::string filename;
        iss >> filename;
        executeSequenceCommand(filename, player);
        return false;
    } else if (action == "quit") {
        executeQuitCommand();
        return true;
    } else if (action == "-link1") {
        // std::string order;
        // iss >> order;
        if (!getPlayer(0)->generateLinks(order, std::cout, board)) {
            std::cout << "hello";
            std::cout << order;
            std::cout << "Invalid link order." << std::endl;
            return false;
        }
        p1Links = true;
        initL1 = true;
        return true;
    } else if (action == "-link2") {
        // std::string order;
        // iss >> order;
        if (!getPlayer(1)->generateLinks(order, std::cout, board)) {
            std::cout << "Invalid link order." << std::endl;
            return false;
        }
        p2Links = true;
        initL2 = true;
        return true;
    } else if (action == "-ability1") {
        // std::string order;
        // iss >> order;
        if (!generateAbilitiesForPlayer(getPlayer(0), order)) {
            std::cout << "Invalid ability string." << std::endl;
            return false;
        }
        p1Ability = true;
        initA1 = true;
        return true;
    } else if (action == "-ability2") {
        // std::string order;
        // iss >> order;
        if (!generateAbilitiesForPlayer(getPlayer(1), order)) {
            std::cout << "Invalid ability string." << std::endl;
            return false;
        }
        p2Ability = true;
        initA2 = true;
        return true;
    }

    else {
        std::cout << "Invalid command." << std::endl;
    }
    return false;
}

Link* Game::getLink(char c) {
    std::vector<Link*>& p1Links = players[0]->getLinks();
    for (int i = 0; i < p1Links.size(); i++) {
        Link* currLink = p1Links[i];
        if (currLink->getSymbol() == c) {
            return currLink;
        }
    }
    std::vector<Link*>& p2Links = players[1]->getLinks();
    for (int i = 0; i < p2Links.size(); i++) {
        Link* currLink = p2Links[i];
        if (currLink->getSymbol() == c) {
            return currLink;
        }
    }
    return nullptr;
}

bool Game::moveLink(Link *link, int x, int y) {
    auto &grid = board->getGrid();
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    // top/bottom: download, left/right: out of bounds
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        if (x == -1 && link->getPlayer()->getPlayerNum() == 1) {
            players[0]->download(link);
            return true;
        } else if (x == rows && link->getPlayer()->getPlayerNum() == 0) {
            players[1]->download(link);
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

    if (targetTile->getLink() &&
        targetTile->getLink()->getPlayer() == link->getPlayer()) {
        std::cout << "Invalid move: cannot attack own link." << std::endl;
        return false;
    }

    if (targetTile->getLink()) {
        battle(link, targetTile->getLink());
    } else if (targetTile->getIsPort()) {
        int portSideOwner = (targetTile->getX() == 0 ? 0 : 1);  // top row -> player 0, bottom row -> player 1
        int mover = link->getPlayer()->getPlayerNum();

        if (mover == portSideOwner) {
            std::cout << "Invalid move: cannot enter own server port." << std::endl;
            return false;
        } else {
            link->getPlayer()->download(link);
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
            return moveLink(link, x, y);
        }
    }
    std::cout << "Link " << A << " not found." << std::endl;
    return false;
}

void Game::executeAbilitiesCommand(Player *player) {
    std::cout << "Abilities:" << std::endl;
    for (size_t i = 0; i < player->getAbilities().size(); ++i) {
        if (!player->getAbilities()[i]->isAvailable()) {
            //std::cout << "not avail";
        }
        else {
            std::cout << i << ". " << player->getAbilities()[i]->getType() << std::endl;
        }
    }
        
}

bool Game::executeAbilityUseCommand(int abilityIndex, Player *player, std::istream &in) {
    if (abilityIndex < 1 || abilityIndex > static_cast<int>(player->getAbilities().size())) {
        std::cout << "Invalid ability index." << std::endl;
        return false;
    }
    Ability *ability = player->getAbilities()[abilityIndex - 1];

    if (ability->getType() == AbilityType::Download) {

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

bool Game::executeSequenceCommand(std::string filename, Player *startingPlayer) {
    std::ifstream file{filename};

    if (!file) {
        std::cout << "Could not open file: " << filename << std::endl;
        return false;
    }

    Player *currentPlayer = startingPlayer;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        bool endTurn = executeCommand(line, currentPlayer);

        if (isGameOver) { return true; }

        if (endTurn) {
            // swap to the other player
            int idx = currentPlayer->getPlayerNum();   // 0 or 1
            currentPlayer = players[1 - idx];
            incrementMoveNumber();
        }
    }

    return true;
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
    if (!attacker || !defender) return;

    Tile *attackerTile = attacker->getTile();
    Tile *defenderTile = defender->getTile();

    if (!attackerTile || !defenderTile) { return; }

    attacker->reveal();
    defender->reveal();

    bool attackerWins = (attacker->getStrength() >= defender->getStrength());

    if (attackerWins) {
        Tile *oldDefenderTile = defenderTile;
        attacker->getPlayer()->download(defender);

        if (attackerTile->getLink() == attacker) { attackerTile->setLink(nullptr); }

        attacker->setTile(oldDefenderTile);
        if (oldDefenderTile) {
            oldDefenderTile->setLink(attacker);
        }

    } else {
        Tile *oldAttackerTile = attackerTile;
        defender->getPlayer()->download(attacker);

        if (oldAttackerTile && oldAttackerTile->getLink() == attacker) {
            oldAttackerTile->setLink(nullptr);
        }
    }
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
