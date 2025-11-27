module Abilities;

import <vector>;
import <string>;
import <iostream>;

import Core;

void Scan::activate(AbilityParam param) {
    Link *target = param.primaryLink;
    if (!target) return;

    std::cout << "Scan: Link " << target->getSymbol()
              << " is a " << target->getType()
              << " with strength " << target->getStrength()
              << std::endl;
}

AbilityType Scan::getType() { 
    return AbilityType::Scan; 
}
