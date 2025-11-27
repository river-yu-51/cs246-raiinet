module Abilities;

import <vector>;
import <string>;

import Core;

Firewall::Firewall(Player *player) : Ability(player) {}

bool Firewall::activate(AbilityParam param) {
    Tile *tile = param.tile;
    if (!tile) return false;

    tile->setFirewallPlayer(param.player->getPlayerNum());
    tile->setSymbol(param.player->getPlayerNum() == 0 ? 'm' : 'w');
    return true;
}

AbilityType Firewall::getType() { 
    return AbilityType::Firewall; 
}
