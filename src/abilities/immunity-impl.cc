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

    if (target->getPlayer() != caster) {
        std::cout << "Must use Immunity on your own link.\n";
        return false;
    }
    target->setImmune(true);
    return true;
}

AbilityType Immunity::getType() { return AbilityType::Immunity; }
