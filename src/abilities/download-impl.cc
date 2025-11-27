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

    if (target->getPlayer() == caster) {
        std::cout << "Cannot download your own link with Download ability.\n";
        return false;
    }

    // 1. Detach link from its tile
    Tile *tile = target->getTile();
    if (tile) {
        tile->setLink(nullptr);
        target->setTile(nullptr);
    }

    // 2. Remove link from its owner's links vector
    Player *owner = target->getPlayer();
    auto &ownerLinks = owner->getLinks();
    for (auto it = ownerLinks.begin(); it != ownerLinks.end(); ++it) {
        if (*it == target) {
            ownerLinks.erase(it);
            break;
        }
    }

    caster->download(target);

    return true;
}

AbilityType Download::getType() { return AbilityType::Download; }

