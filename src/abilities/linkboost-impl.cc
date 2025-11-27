module Abilities;

import <vector>;
import <string>;

import Core;

void LinkBoost::activate(AbilityParam param) {
    Link *target = param.primaryLink;
    if (!target) return;

    target->setDistance(target->getDistance() + 1);
}

AbilityType LinkBoost::getType() { 
    return AbilityType::LinkBoost; 
}
