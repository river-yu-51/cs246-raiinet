module Abilities;

import <vector>;
import <string>;

import Core;

LevelUp::LevelUp(Player *player) : Ability(player) {}

void LevelUp::activate(AbilityParam param) {
    Link *target = param.primaryLink;
    if (!target) return;

    if (target->getStrength() == 4) return;

    target->setStrength(target->getStrength() + 1);
}

AbilityType LevelUp::getType() { return AbilityType::LevelUp; }
