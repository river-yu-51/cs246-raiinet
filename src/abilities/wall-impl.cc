module Abilities;

import <vector>;
import <string>;

import Core;

Wall::Wall(Player *player) : Ability(player) {}

bool Wall::activate(AbilityParam param) {
    Tile *t = param.tile;
    if (!t) return false;

    t->setIsWalled(true);

    // choose a symbol for a wall

    int owner = param.player->getPlayerNum();
    if (owner == 0){
        t->setSymbol('#');
    } 
    else{
         t->setSymbol('@');
    }        

    return true;
}

AbilityType Wall::getType() { 
    return AbilityType::Wall; 
}
