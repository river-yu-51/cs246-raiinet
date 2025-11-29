module Abilities;

import <vector>;
import <string>;
import <iostream>;

import Core;

LinkBoost::LinkBoost(Player *player) : Ability(player) {}

bool LinkBoost::activate(AbilityParam param) {
    Player *caster = param.player;
    Link *target = param.primaryLink;
    if (!target) return false;


    if (!caster || !target) return false;

    if (target->getPlayer() != caster) {
        std::cout << "Must cast Link Boost on your own link.\n";
        return false;
    }
    target->setDistance(target->getDistance() + 1);
    return true;
}

AbilityType LinkBoost::getType() { 
    return AbilityType::LinkBoost; 
}
