export module AbilityParam;

import Game;
import Player;
import Link;
import Tile;

export struct AbilityParam {
    Game *game;
    Player *player;
    Link *primaryLink;
    Link *secondaryLink;
    Tile *targetTile;
};