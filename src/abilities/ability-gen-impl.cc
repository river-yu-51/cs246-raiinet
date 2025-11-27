module Abilities;

import <vector>;
import <string>;

import Core;

bool generateAbilitiesForPlayer(Player *player, std::string order) {
    if (order.size() != 5) { return false; }

    std::vector<Ability*> abilities;

    for (char c : order) {
        if (c == 'D') {
            abilities.push_back(new Download{player});
        } else if (c == 'L') {
            abilities.push_back(new LinkBoost{player});
        } else if (c == 'U') {
            abilities.push_back(new LevelUp{player});
        } else if (c == 'I') {
            abilities.push_back(new Immunity{player});
        } else if (c == 'F') {
            abilities.push_back(new Firewall{player});
        } else if (c == 'S') {
            abilities.push_back(new Scan{player});
        } else if (c == 'P') {
            abilities.push_back(new Polarize{player});
        } else if (c == 'W') {
            abilities.push_back(new Wall{player});
        } else {
            return false;
        }
    }

    player->getAbilities() = abilities;
    return true;
}