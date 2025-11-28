module Abilities;

import <vector>;
import <string>;

import Core;

LinkBoost::LinkBoost(Player *player) : Ability(player) {}

bool LinkBoost::activate(AbilityParam param) {
    Link *target = param.primaryLink;
    if (!target) return false;

    target->setDistance(target->getDistance() + 1);

    return true;
}

AbilityType LinkBoost::getType() { 
    return AbilityType::LinkBoost; 
}
