module Core;

import <string>;
import <vector>;
import <map>;

Player::Player(int playerNum, std::vector<Link*> links, std::vector<Ability*> abilities,
               std::map<Ability*, int> usage, bool isEliminated,
               int downloadedData, int downloadedViruses)
    : playerNum{playerNum}, links{links}, abilities{abilities}, usage{usage},
      isEliminated{isEliminated}, downloadedData{downloadedData},
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
    if (link->getType() == 'D' ) {
        downloadedData++;
    } else if (link->getType() == 'V') {
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
    }


    // generate links for player at start of game
}

Link *Player::getLink(int index) { return links[index]; }

int Player::getDataCount() { return downloadedData; }

int Player::getVirusCount() { return downloadedViruses; }

