module Abilities;

import <vector>;
import <string>;
import <iostream>;

import Core;

Scan::Scan(Player *player) : Ability(player) {}

void Scan::activate(AbilityParam param) {
    Link *target = param.primaryLink;
    if (!target) return false;
    // check if immune, do nothing


    std::cout << "Scan: Link " << target->getSymbol()
              << " is a " << target->getType()
              << " with strength " << target->getStrength()
              << std::endl;
}

AbilityType Scan::getType() { 
    return AbilityType::Scan; 
}
