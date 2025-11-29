module Abilities;

import <vector>;
import <string>;
import <iostream>;

import Core;

Polarize::Polarize(Player *player) : Ability(player) {}

bool Polarize::activate(AbilityParam param) {
    Player *caster = param.player;
    Link *target = param.primaryLink;

    if (!caster || !target) return false;

    if (target->getPlayer() != caster) {
        std::cout << "Must use Polarize on your own link\n";
        return false;
    }

    Link *link = param.primaryLink;
    if (!link) return false;
    if (link->isImmune()) return false;
    if (link->isDownloaded()) return false;

    // Link(Player *player, char symbol, int strength, Tile *tile, int distance, bool immune, bool downloaded, bool revealed);
    Player *owner = link->getPlayer();
    char symbol = link->getSymbol();
    int strength = link->getStrength();
    Tile *tile = link->getTile();
    int distance = link->getDistance();
    bool immune = link->isImmune();
    bool downloaded = link->isDownloaded();
    bool revealed = link->isRevealed();

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

    auto &ownerLinks = owner->getLinks();
    for (auto it = ownerLinks.begin(); it != ownerLinks.end(); ++it) {
        if (*it == link) {
            *it = polarized;
            break;
        }
    }

    delete link;

    return true;
}

AbilityType Polarize::getType() { 
    return AbilityType::Polarize; 
}
