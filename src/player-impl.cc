module Core;

import <string>;
import <vector>;
import <map>;
import <string>;
import <iostream>;
import <algorithm>;

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

    if (link->getType() == "data") {
        downloadedData++;
    } else if (link->getType() == "virus") {
        downloadedViruses++;
    }
}

int Player::getPlayerNum() { return playerNum; }

std::vector<Link*> &Player::getLinks() { return links; }

std::vector<Ability*> &Player::getAbilities() { return abilities; }

Link *Player::getLink(int index) { 
    if (index < 0 || index >= links.size()) {
        return nullptr;
    }
    return links[index]; 
}

int Player::getDataCount() { return downloadedData; }

int Player::getVirusCount() { return downloadedViruses; }

void Player::generateLinks(std::istream &is, std::ostream &os) {
    const int NUM_LINKS = 8;
    links.clear();

    const std::vector<std::vector<char>> symbolSets = {
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
        {'s', 't', 'u', 'v', 'w', 'x', 'y', 'z'},
        {'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}
    };
    const auto &symbols = symbolSets[playerNum % symbolSets.size()];

    std::vector<std::string> remainingLinks = {
        "D1", "D2", "D3", "D4",
        "V1", "V2", "V3", "V4"
    };

    for (int i = 0; i < NUM_LINKS; ++i) {
        os << "Available links: ";
        for (const auto &linkStr : remainingLinks) {
            os << linkStr << " ";
        }
        os << "\nSelect link " << symbols[i] << ": ";
        std::string choice;
        is >> choice;

        auto it = std::find(remainingLinks.begin(), remainingLinks.end(), choice);
        if (it == remainingLinks.end()) {
            os << "Invalid choice. Try again.\n";
            --i; // retry
            continue;
        }

        char symbol = symbols[i];
        Link *newLink = nullptr;
        if (choice[0] == 'D') {
            int strength = std::stoi(choice.substr(1));
            newLink = new Data{symbol, this, strength, nullptr, 0, false, false};
        } else if (choice[0] == 'V') {
            int strength = std::stoi(choice.substr(1));
            newLink = new Virus{symbol, this, strength, nullptr, 0, false, false};
        }

        links.push_back(newLink);
        remainingLinks.erase(it);
    }
}

void Player::checkWinLose() {
    if (downloadedViruses >= 4) {
        isEliminated = true;
    }
    else if (downloadedData >= 4) {
        isWon = true;
    }
}

bool Player::getIsWon() { return isWon; }
bool Player::getIsEliminated() { return isEliminated; }
