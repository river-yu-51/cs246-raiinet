module Abilities;

import <vector>;
import <string>;

import Core;

Firewall::Firewall(Player *player) : Ability(player) {}

void Firewall::activate(AbilityParam param) {
    Tile *t = param.tile;
    if (!t) return;

    int owner = param.player->getPlayerNum();

    
    t->setIsWalled(true);
    t->setFirewallPlayer(owner);

    
    if (owner == 0) t->setSymbol('m');
    else t->setSymbol('w');
}

AbilityType Firewall::getType() { 
    return AbilityType::Firewall; 
}
