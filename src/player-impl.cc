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

void Player::generateLinks() {
    // generate links for player at start of game
}

Link *Player::getLink(int index) { return links[index]; }

int Player::getDataCount() { return downloadedData; }

int Player::getVirusCount() { return downloadedViruses; }

