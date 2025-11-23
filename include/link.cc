export module Link;

import Player;
import Tile;

export class Link {
    Player *player;
    int strength;
    Tile *tile;
    int distance; // number of "moves per move"
    bool immune;
    bool downloaded;
public:
    Link(Player*, int, Tile*, int, bool, bool);

    int getStrength();
    Tile *getTile();
    bool isImmune();
    bool isDownloaded();
    
    void setValue(int);
    void setTile(Tile*);
    void setDistance(int);
    void setImmune(bool);
    void setDownloaded(bool);

    virtual void download();
};