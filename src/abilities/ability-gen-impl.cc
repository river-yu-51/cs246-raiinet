module Abilities;

import <vector>;
import <string>;
import <map>;

import Core;

bool isValidAbilityOrder(const std::string &order) {
    if (order.size() != 5) {
        return false;
    }

    std::vector<char> abilityChars = {'D', 'F', 'I', 'L', 'P', 'S', 'U', 'W'};
    std::map<char, int> counts;
    for (char c : abilityChars) {
        counts[c] = 0;
    }

    for (char c : order) {
        if (counts.find(c) == counts.end()) { return false; }
        counts[c]++;
        if (counts[c] > 2) { return false; }
    }

    return true;
}

bool generateAbilitiesForPlayer(Player *player, std::string order) {
    if (!isValidAbilityOrder(order)) { return false; }

    std::vector<Ability*> abilities;

    for (char c : order) {
        if (c == 'D') {
            abilities.push_back(new Download{player});
        } else if (c == 'L') {
            abilities.push_back(new LinkBoost{player});
        } else if (c == 'U') {
            abilities.push_back(new Upgrade{player});
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