module Abilities;

import <vector>;
import <string>;
import <map>;

import Core;

bool generateAbilitiesForPlayer(Player *player, std::string order) {
    if (order.size() != 5) { return false; }

    const std::map<char, AbilityType> abilityMap = {
        {'L', AbilityType::LinkBoost},
        {'F', AbilityType::Firewall},
        {'D', AbilityType::Download},
        {'P', AbilityType::Polarize},
        {'S', AbilityType::Scan},
        {'U', AbilityType::Upgrade},
        {'I', AbilityType::Immunity},
        {'W', AbilityType::Wall}
    };

    // keep track of how many times each letter appears
    std::map<char, int> counts;
    std::vector<Ability*> abilities;
    abilities.reserve(order.size());

    AbilityFactory factory;

    for (char c : order) {
        auto it = abilityMap.find(c);
        if (it == abilityMap.end()) {
            // invalid letter, clean up any abilities we've already allocated
            for (Ability *a : abilities) { delete a; }
            return false;
        }

        counts[c]++;
        if (counts[c] > 2) {
            // more than 2 of the same ability
            for (Ability *a : abilities) { delete a; }
            return false;
        }
        
        Ability *ability = factory.createAbility(player, it->second);
        abilities.push_back(ability);
    }

    // in case the command is called twice - probably not needed
    auto &existingAbilities = player->getAbilities();
    for (Ability *a : existingAbilities) {
        delete a;
    }

    // if we get here, the order is valid; assign to the player
    player->getAbilities() = abilities;
    return true;
}
