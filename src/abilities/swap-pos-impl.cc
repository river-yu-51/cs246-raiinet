module Abilities;

import <vector>;
import <string>;

import Core;

SwapPos::SwapPos(Player *player) : Ability(player) {}

void SwapPos::activate(AbilityParam param) {
    Link *a = param.primaryLink;
    Link *b = param.secondaryLink;

    if (!a || !b) return;

    Tile *tileA = a->getTile();
    Tile *tileB = b->getTile();

    if (!tileA || !tileB) return;

    // remove from tiles
    tileA->setLink(nullptr);
    tileB->setLink(nullptr);

    // swap tiles
    a->setTile(tileB);
    b->setTile(tileA);

    //place back onto board
    tileB->setLink(a);
    tileA->setLink(b);
}

AbilityType SwapPos::getType() {
    return AbilityType::SwapPos;
}
