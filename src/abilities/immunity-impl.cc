module Abilities;

import <vector>;
import <string>;

import Core;

Immunity::Immunity(Player *player) : Ability(player) {}

bool Immunity::activate(AbilityParam param) {
    // implementation needed

    return true;
}

AbilityType Immunity::getType() { return AbilityType::Immunity; }
