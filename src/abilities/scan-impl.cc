module Abilities;

import <vector>;
import <string>;
import <iostream>;

import Core;

Scan::Scan(Player *player) : Ability(player) {}

bool Scan::activate(AbilityParam param) {
    Link *target = param.primaryLink;
    if (!target) return false;
    target->reveal();
    return true;
}

AbilityType Scan::getType() { 
    return AbilityType::Scan; 
}
