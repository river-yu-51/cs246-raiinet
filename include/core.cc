export module Core;
// contains: Tile, Link, Data, Virus, Player, Board

import <vector>;
import <string>;
import <map>;

import Subject;

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

    virtual void download() = 0;
};

export class Data : public Link {
public:
    Data(Player*, int, Tile*, int, bool, bool);

    void download() override;
};

export class Virus : public Link {
public:
    Virus(Player*, int, Tile*, int, bool, bool);

    void download() override;
};

export class Player {
    int playerNum;
    std::vector<Link*> links;
    std::vector<Ability*> abilities;
    std::map<Ability*, int> usage;
    bool isEliminated;
    int downloadedData;
    int downloadedViruses;
public:
    Player(int, std::vector<Link*>, std::vector<Ability*>, std::map<Ability*, int>, bool, int, int);

    void useAbility(Ability*);
    void moveLink(Link*);
    void download(Link*);

    int getPlayerNum();
    void generateLinks();
    Link *getLink(int);
    int getDataCount();
    int getVirusCount();
};

export class Board : public Subject {
    std::vector<std::vector<Tile*>> grid;
public:
    Board(std::vector<std::vector<Tile*>>);

    Tile *getTile(int, int);
    std::vector<std::vector<Tile*>> &getGrid();

    void setTile(int, int, Tile*);
};
