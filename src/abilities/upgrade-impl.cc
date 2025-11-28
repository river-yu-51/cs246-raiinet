module Abilities;

import <vector>;
import <string>;
import <iostream>;

import Core;

Upgrade::Upgrade(Player *player) : Ability(player) {}

bool Upgrade::activate(AbilityParam param) {
    Link *target = param.primaryLink;
    if (!target) return false;

    target->setStrength(target->getStrength() + 1);

    return true;
}

AbilityType Upgrade::getType() { return AbilityType::Upgrade; }
