module Abilities;

import <vector>;
import <string>;

import Core;

Upgrade::Upgrade(Player *player) : Ability(player) {}

bool Upgrade::activate(AbilityParam param) {
    Link *target = param.primaryLink;
    if (!target) return false;

    if (target->getStrength() == 4) return false;

    target->setStrength(target->getStrength() + 1);

    return true;
}

AbilityType Upgrade::getType() { return AbilityType::Upgrade; }
