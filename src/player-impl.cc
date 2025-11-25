module Core;

import <string>;
import <vector>;
import <map>;
import <string>;
import <iostream>;

Player::Player(int playerNum,
               std::vector<Link*> links,
               std::vector<Ability*> abilities,
               std::map<Ability*, int> usage,
               bool isEliminated,
               int downloadedData,
               int downloadedViruses)
    : playerNum{playerNum},
      links{links},
      abilities{abilities},
      usage{usage},
      isEliminated{isEliminated},
      downloadedData{downloadedData},
      downloadedViruses{downloadedViruses} {}

void Player::useAbility(Ability *ability) {
    // prompt player
    // check if available/valid
    ability->activate(AbilityParam{ /* STUFF HERE IDK */ });
    usage[ability]++;
}

void Player::moveLink(Link *link) {
    // prompt player
    // get destination tile
    // move link to destination tile
}

void Player::download(Link *link) {
    if (!link) return;

    if (dynamic_cast<Data*>(link)) {
        downloadedData++;
    } else if (dynamic_cast<Virus*>(link)) {
        downloadedViruses++;
    }
}

int Player::getPlayerNum() { return playerNum; }

void Player::generateLinks(int playerNum) {
    const int NUM_LINKS = 8;
    const int 
    // letters for 2 players only for now 
    std::vector<char> letters{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 
                                'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    for (int i = 0; i < NUM_LINKS; i++) {
        if (playerNum == 1) {
            char type = types[i];
        }
        else if (playerNum == 2) {
            char type = types[i + NUM_LINKS];
        }
        int strength = (i  % 4) + 1;
        links.emplace_back(new Link(this, type, strength, nullptr, 1, false, false));
        // tile set to nullptr for now idk
        // maybe also do the tile set link here 
    }
}

Link *Player::getLink(int index) { return links[index]; }

int Player::getDataCount() { return downloadedData; }

int Player::getVirusCount() { return downloadedViruses; }
bool Player::getIsEliminated() { return isEliminated; }

bool Player::getIsWon() {
    return downloadedData >= 4;
}

void Player::generateLinks(int boardSize) {
    const int NUM_LINKS = 8;
    links.clear();

    // Symbol sets — player 1 uses lowercase, player 2 uses uppercase
    const std::vector<char> p0Symbols{'a','b','c','d','e','f','g','h'};
    const std::vector<char> p1Symbols{'A','B','C','D','E','F','G','H'};

    const std::vector<char> &symbols = ((playerNum == 0) ? p0Symbols : p1Symbols);

    for (int i = 0; i < NUM_LINKS; i++) {
        char sym = symbols[i];
        int strength = (i % 4) + 1;

        if (i < 4) {
            links.emplace_back(
                new Data(sym, this, strength, nullptr, 1, false, false)
            );
        } else {
            links.emplace_back(
                new Virus(sym, this, strength, nullptr, 1, false, false)
            );
        }
    }
}

void Player::checkWinLose() {
    if (downloadedViruses >= 4) {
        isEliminated = true;
    }
}
