module Abilities;

import <vector>;
import <string>;

import Core;

Immunity::Immunity(Player *player) : Ability(player) {}

bool Immunity::activate(AbilityParam param) {
    Link *target = param.primaryLink;
    if (!target) return false;
    target->setImmune(true);
    return true;
}

AbilityType Immunity::getType() { return AbilityType::Immunity; }
