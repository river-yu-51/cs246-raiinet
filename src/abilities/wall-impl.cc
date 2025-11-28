module Abilities;

import <vector>;
import <string>;

import Core;

Wall::Wall(Player *player) : Ability(player) {}

bool Wall::activate(AbilityParam param) {
    Tile *t = param.tile;
    if (!t) return false;

    t->setIsWalled(true);

    int owner = param.player->getPlayerNum();
    if (owner == 0){
        t->setSymbol('m');
    } 
    else{
         t->setSymbol('w');
    }        

    return true;
}

AbilityType Wall::getType() { 
    return AbilityType::Wall; 
}
