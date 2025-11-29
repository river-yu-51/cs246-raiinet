module Abilities;

import <vector>;
import <string>;
import <iostream>;

import Core;

Download::Download(Player *player) : Ability(player) {}

bool Download::activate(AbilityParam param) {
    Player *caster = param.player;
    Link *target = param.primaryLink;
    if (!caster || !target) return false;

    // check if the player is trying to download their own link
    if (target->getPlayer() == caster) {
        std::cout << "Cannot download your own link with Download ability.\n";
        return false;
    }
    // otherwise, download the opponents link
    caster->download(target);
    return true;
}

AbilityType Download::getType() { return AbilityType::Download; }

