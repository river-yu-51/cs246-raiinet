export module Core;
// contains: Tile, Link, Data, Virus, Player, Board

import <vector>;
import <string>;
import <map>;
import <iostream>;

import Subject;

export class Link;
export class Player;
export class Ability;

export class Tile {
    int x, y;
    char symbol;
    bool isPort;
    bool isWalled;
    Link *link;
    int firewallPlayer;
public:
    Tile(int, int, char, bool, bool, Link*, int);

    void setSymbol(char);
    void setFirewallPlayer(int);
    void setIsWalled(bool);
    void setIsPort(bool);
    void setLink(Link*);

    int getX();
    int getY();
    Link *getLink();
    int getFirewallPlayer();
    bool getIsPort();
    bool getIsWalled();
    char getSymbol();
};

export class Link {
    char symbol;
    Player *player;
    int strength;
    Tile *tile;
    int distance; // number of "moves per move"
    bool immune;
    bool downloaded;
public:
    Link(char, Player*, int, Tile*, int, bool, bool);

    Player *getPlayer();
    int getStrength();
    Tile *getTile();
    bool isImmune();
    bool isDownloaded();
    char getSymbol();

    void setValue(int);
    void setTile(Tile*);
    void setDistance(int);
    void setImmune(bool);
    void setDownloaded(bool);

    virtual void download() = 0;
};

export class Data : public Link {
public:
    Data(char, Player*, int, Tile*, int, bool, bool);

    void download() override;
};

export class Virus : public Link {
public:
    Virus(char, Player*, int, Tile*, int, bool, bool);

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
    std::vector<Link*> &getLinks();
    std::vector<Ability*> &getAbilities();
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

export enum class AbilityType {
    LinkBoost,
    Firewall,
    Download,
    Polarize,
    Scan,
    LevelUp,
    SwapPos,
    Immunity,
    Wall
};

export std::ostream &operator<<(std::ostream&, AbilityType);

export struct AbilityParam {
    Player *player;
    Link *primaryLink;
    Link *secondaryLink;
    Tile *targetTile;
};

export class Ability {
    Player *player;
    AbilityType type;
public:
    Ability(Player*, AbilityType);

    Player *getPlayer();
    AbilityType getType();
    virtual void activate(AbilityParam) = 0;
};

