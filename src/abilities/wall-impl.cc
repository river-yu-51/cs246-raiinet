module Abilities;

import <vector>;
import <string>;

import Core;

Wall::Wall(Player *player) : Ability(player) {}

bool Wall::activate(AbilityParam param) {
    Tile *t = param.tile;
    if (!t) return false;
    // set tile to be walled
    t->setIsWalled(true);
    
    // set symbol of tile based on the player who cast the wall
    int owner = param.player->getPlayerNum();
    if (owner == 0){
        t->setSymbol('M');
    } 
    else{
        t->setSymbol('W');
    }        

    return true;
}

AbilityType Wall::getType() { 
    return AbilityType::Wall; 
}
