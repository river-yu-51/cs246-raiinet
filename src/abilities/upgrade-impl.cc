module Abilities;

import <vector>;
import <string>;
import <iostream>;

import Core;

Upgrade::Upgrade(Player *player) : Ability(player) {}

bool Upgrade::activate(AbilityParam param) {
    Player *caster = param.player;
    Link *target = param.primaryLink;
    if (!caster || !target) return false;

    // check if player is trying to upgrade opponent link or link at max strength
    if (target->getPlayer() != caster) {
        std::cout << "Must use Upgrade on your own link.\n";
        return false;
    }
    else if (target->getStrength() == 4) {
        std::cout << "Link is already at max strength.\n";
        return false;
    }
    // otherwise, increment strength by 1
    target->setStrength(target->getStrength() + 1);

    return true;
}

AbilityType Upgrade::getType() { return AbilityType::Upgrade; }
