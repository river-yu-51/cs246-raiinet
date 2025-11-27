module Abilities;

import <vector>;
import <string>;

import Core;

void LinkBoost::activate(AbilityParam param) {
    Link *target = param.link1;
    if (!target) return;

    target->setBoosted(true);
}

AbilityType LinkBoost::getType() { 
    return AbilityType::LinkBoost; 
}
