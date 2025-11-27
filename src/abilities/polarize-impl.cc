module Abilities;

import <vector>;
import <string>;

import Core;

Polarize::Polarize(Player *player) : Ability(player) {}

bool Polarize::activate(AbilityParam param) {
    // Link *target = param.primaryLink;
    // if (!target) return;

    // Player *owner = target->getPlayer();
    // Tile *tile = target->getTile();
    // char symbol = target->getSymbol();
    // int strength = target->getStrength();

    // if (tile) tile->setLink(nullptr);

    // auto &links = owner->getLinks();
    // for (size_t i = 0; i < links.size(); ++i) {
    //     if (links[i] == target) {
    //         links.erase(links.begin() + i);
    //         break;
    //     }
    // }

    // Link *replacement = nullptr;
    // if (target->getType() == "data") {
    //     replacement = new Virus{owner, strength, symbol};
    // } else {
    //     replacement = new Data{owner, strength, symbol};
    // }

    // if (tile) {
    //     replacement->setTile(tile);
    //     tile->setLink(replacement);
    // }

    // owner->addLink(replacement);

    return true;
}

AbilityType Polarize::getType() { 
    return AbilityType::Polarize; 
}
