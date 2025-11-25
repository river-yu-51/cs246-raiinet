module Core;

import <vector>;
import <map>;
import <string>;
import <iostream>;

Player::Player(int playerNum,
               std::vector<Link*> links,
               std::vector<Ability*> abilities,
               std::map<Ability*, int> usage,
               bool isEliminated, bool isWon,
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
    if (link->getType() == "data") {
        downloadedData++;
    } else if (link->getType() == "virus") {
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

void Player::checkWinLose() { 
    if (getVirusCount() == 4) {
        isEliminated = true;
    }
    if (downloadedData >= 4) {
        isWon = true;
    }
}

bool Player::getIsEliminated() { return isEliminated; }
bool Player::getIsWon() { return isWon; } 
