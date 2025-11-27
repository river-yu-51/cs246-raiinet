module Abilities;

import <vector>;
import <string>;

import Core;

Immunity::Immunity(Player *player) : Ability(player) {}

void Immunity::activate(AbilityParam param) {
    // implementation needed
}

AbilityType Immunity::getType() { return AbilityType::Immunity; }
