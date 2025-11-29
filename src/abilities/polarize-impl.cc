module Abilities;

import <vector>;
import <string>;
import <iostream>;

import Core;

Polarize::Polarize(Player *player) : Ability(player) {}

bool Polarize::activate(AbilityParam param) {
    Player *caster = param.player;
    Link *link = param.primaryLink;
    if (!caster || !link) return false;

    // check if player is using polarize on an opponent link
    if (target->getPlayer() != caster) {
        std::cout << "Must use Polarize on your own link\n";
        return false;
    }

    // get old link's previous fields
    Player *owner = link->getPlayer();
    char symbol = link->getSymbol();
    int strength = link->getStrength();
    Tile *tile = link->getTile();
    int distance = link->getDistance();
    bool immune = link->isImmune();
    bool downloaded = link->isDownloaded();
    bool revealed = link->isRevealed();

    // change type based on previous link type
    Link *polarized = nullptr;
    if (link->getType() == "data") {
        polarized = new Virus{symbol, owner, strength, tile, distance, immune, downloaded, revealed};
    } else if (link->getType() == "virus") {
        polarized = new Data{symbol, owner, strength, tile, distance, immune, downloaded, revealed};
    } else {
        return false;
    }

    polarized->setTile(tile);
    tile->setLink(polarized);

    // swap old link in player's link vector with polarized link
    auto &ownerLinks = owner->getLinks();
    for (auto it = ownerLinks.begin(); it != ownerLinks.end(); ++it) {
        if (*it == link) {
            *it = polarized;
            break;
        }
    }
    // delete old link
    delete link;
    return true;
}

AbilityType Polarize::getType() { 
    return AbilityType::Polarize; 
}
