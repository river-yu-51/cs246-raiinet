module Abilities;

import <vector>;
import <string>;

import Core;

Download::Download(Player *player) : Ability(player) {}

void Download::activate(AbilityParam param) {
    Link *target = param.primaryLink;
    if (!target) return;

    Tile *tile = target->getTile();
    if (tile) {
        tile->setLink(nullptr);
    }

    target->download();
}

AbilityType Download::getType() { return AbilityType::Download; }

