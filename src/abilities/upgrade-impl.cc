module Abilities;

import <vector>;
import <string>;

import Core;

Upgrade::Upgrade(Player *player) : Ability(player) {}

void Upgrade::activate(AbilityParam param) {
    Link *target = param.primaryLink;
    if (!target) return;

    if (target->getStrength() == 4) return;

    target->setStrength(target->getStrength() + 1);
}

AbilityType Upgrade::getType() { return AbilityType::Upgrade; }
