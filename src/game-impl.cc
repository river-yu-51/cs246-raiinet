module Game;

import <sstream>;
import <fstream>;
import <iostream>;
import <vector>;
import <string>;

import Core;
import Abilities;
import Display;

Game::Game(Board *board, std::vector<Player*> players, int moveNumber,
           bool hasStarted, bool isGameOver)
    : board{board}, players{players}, moveNumber{moveNumber},
      hasStarted{hasStarted}, isGameOver{isGameOver} {}

void Game::startGame(int startingPlayer) {
    hasStarted = true;
    moveNumber = 0;
    // other stuff idk
}

bool Game::executeCommand(std::string command, Player *player) {
    if (!hasStarted || isGameOver) return false;

    std::istringstream iss{command};
    std::string action;
    iss >> action;

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
        return true;
    } else if (action == "ability") {
        int abilityIndex;
        iss >> abilityIndex;
        return executeAbilityUseCommand(abilityIndex, player, iss);
    } else if (action == "board") {
        executeBoardCommand(player);
        return true;
    } else if (action == "sequence") {
        std::string filename;
        iss >> filename;
        return executeSequenceCommand(filename, player);
    } else if (action == "quit") {
        executeQuitCommand();
        return true;
    } else {
        std::cout << "Invalid command." << std::endl;
        return false;
    }
}

void Game::moveLink(Link *link, int x, int y) {
    board->MoveLink(link, x, y);
}

void Game::useAbility(Ability *ability, const AbilityParam &param) {
    ability->activate(param);
}

bool Game::executeMoveCommand(char A, std::string dir, Player *player) {
    for (Link *link : player->getLinks()) {
        if (link->getSymbol() == A) {
            int x = link->getTile()->getX();
            int y = link->getTile()->getY();
            if (dir == "up") {
                y -= 1;
            } else if (dir == "down") {
                y += 1;
            } else if (dir == "left") {
                x -= 1;
            } else if (dir == "right") {
                x += 1;
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

    } else if (ability->getType() == AbilityType::LevelUp) {
        Link *targetLink = nullptr;
        while (!targetLink) {
            std::cout << "Specify link to level up (symbol): ";
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

    } else if (ability->getType() == AbilityType::SwapPos) {
        Link *firstLink = nullptr;
        while (!firstLink) {
            std::cout << "Specify first link to swap (symbol): ";
            char linkSymbol;
            in >> linkSymbol;
            for (Link *link : player->getLinks()) {
                if (link->getSymbol() == linkSymbol) {
                    firstLink = link;
                    break;
                }
            }
            if (!firstLink) {
                std::cout << "Link not found." << std::endl;
            }
        }
        Link *secondLink = nullptr;
        while (!secondLink) {
            std::cout << "Specify second link to swap (symbol): ";
            char linkSymbol;
            in >> linkSymbol;
            for (auto &row : board->getGrid()) {
                for (Tile *tile : row) {
                    Link *link = tile->getLink();
                    if (link && link->getSymbol() == linkSymbol) {
                        secondLink = link;
                        break;
                    }
                }
                if (secondLink) break;
            }
            if (!secondLink) {
                std::cout << "Link not found." << std::endl;
            }
        }
        AbilityParam param{player, firstLink, secondLink, nullptr};
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

void Game::executeBoardCommand(Player *player) {
    // draw board for player
}

void Game::executeQuitCommand() {
    isGameOver = true;
    std::cout << "Game has been quit." << std::endl;
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
    }
    return true;
}

Board *Game::getBoard() { return board; }

Player *Game::getPlayer(int playerNum) { return players[playerNum]; }

int Game::getMoveNumber() { return moveNumber; }

bool Game::getHasStarted() { return hasStarted; }

bool Game::getIsGameOver() { return isGameOver; }

void Game::setMoveNumber(int n) { moveNumber = n; }

void Game::gameOver(Player *winner) {
    isGameOver = true;
    std::cout << "Game Over! Player " << winner->getPlayerNum() + 1 << " won" << std::endl;
}
