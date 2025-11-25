module Core;

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

void Player::download(Link *link) {
    if (!link) return;

    if (dynamic_cast<Data*>(link)) {
        downloadedData++;
    } else if (dynamic_cast<Virus*>(link)) {
        downloadedViruses++;
    }
}

std::vector<Link*> &Player::getLinks() { return links; }
std::vector<Ability*> &Player::getAbilities() { return abilities; }
int Player::getPlayerNum() { return playerNum; }

Link *Player::getLink(int index) {
    if (index < 0 || index >= (int)links.size()) return nullptr;
    return links[index];
}

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
