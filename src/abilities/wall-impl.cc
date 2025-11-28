module Abilities;

import <vector>;
import <string>;

import Core;

Wall::Wall(Player *player) : Ability(player) {}

void Wall::activate(AbilityParam param) {
    Tile *t = param.tile;
    if (!t) return;

    t->setIsWalled(true);

    // choose a symbol for a wall

    int owner = param.player->getPlayerNum();
    if (owner == 0){
        t->setSymbol('M');
    } 
    else{
         t->setSymbol('W');
    }        
}

AbilityType Wall::getType() { 
    return AbilityType::Wall; 
}
