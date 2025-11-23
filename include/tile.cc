export module Tile;

import Link;

export class Tile {
    Link *link;
    int firewallPlayer;
    bool isPort;
    bool isWalled;
    char symbol;
public:
    Tile(Link*, int, bool, bool, char);

    void setSymbol(char);
    void setFirewallPlayer(int);
    void setIsWalled(bool);
    void setIsPort(bool);
    void setLink(Link*);
    
    Link *getLink();
    int getFirewallPlayer();
    bool getIsPort();
    bool getIsWalled();
    char getSymbol();
};