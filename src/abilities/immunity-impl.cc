module Abilities;

import <vector>;
import <string>;
import <iostream>;

import Core;

Immunity::Immunity(Player *player) : Ability(player) {}

bool Immunity::activate(AbilityParam param) {
    Player *caster = param.player;
    Link *target = param.primaryLink;
    if (!caster || !target) return false;
    
    // check if player is trying to use ability on opponent link
    if (target->getPlayer() != caster) {
        std::cout << "Must use Immunity on your own link.\n";
        return false;
    }
    // otherwise, set player's link to be immune
    target->setImmune(true);
    return true;
}

AbilityType Immunity::getType() { return AbilityType::Immunity; }
