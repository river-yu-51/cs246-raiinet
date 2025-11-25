export module Core;
// contains: Tile, Link, Data, Virus, Player, Board

import <vector>;
import <string>;
import <map>;

import Subject;

export class Link;
export class Player;
export class Ability;

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
    char type;
    int strength;
    Tile *tile;
    int distance; // number of "moves per move"
    bool immune;
    bool downloaded;
public:
    Link(Player*, char, int, Tile*, int, bool, bool);

    Player *getPlayer();
    char getType();
    int getStrength();
    Tile *getTile();
    bool isImmune();
    bool isDownloaded();
    
    void setValue(int);
    void setTile(Tile*);
    void setDistance(int);
    void setImmune(bool);
    void setDownloaded(bool);

<<<<<<< HEAD
    void setValue(int value);
    void setTile(Tile *tile);
    void setDistance(int distance);
    void setImmune(bool immune);
    void setDownloaded(bool downloaded);

    virtual void download() = 0;
};

export class Data : public Link {
public:
    Data(char symbol, Player *player, int strength, Tile *tile, int distance, bool immune, bool downloaded);

    void download() override;
};

export class Virus : public Link {
public:
    Virus(char symbol, Player *player, int strength, Tile *tile, int distance, bool immune, bool downloaded);

    void download() override;
=======
    void download();
>>>>>>> parent of f52e0e4 (added iswon/iseliminated function)
};

export class Player {
    int playerNum;
    std::vector<Link*> links;
    std::vector<Ability*> abilities;
    std::map<Ability*, int> usage;
    bool isEliminated;
    bool isWon;
    int downloadedData;
    int downloadedViruses;
public:
<<<<<<< HEAD
    Player(int playerNum, std::vector<Link*> links, std::vector<Ability*> abilities, std::map<Ability*, int> usage, bool isEliminated, int downloadedData, int downloadedViruses);
=======
    Player(int, std::vector<Link*>, std::vector<Ability*>, std::map<Ability*, int>, bool, bool, int, int);
>>>>>>> parent of f52e0e4 (added iswon/iseliminated function)

    void useAbility(Ability*);
    void moveLink(Link*);
    void download(Link*);

    int getPlayerNum();
    void generateLinks(int);
    Link *getLink(int);
    int getDataCount();
    int getVirusCount();
    bool getIsEliminated();
    bool getIsWon();
    void checkWinLose();
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

export struct AbilityParam {
    Player *player;
    Link *primaryLink;
    Link *secondaryLink;
    Tile *targetTile;
};

export class Ability {
    Player *player;
public:
    Player *getPlayer();
    virtual void activate(AbilityParam) = 0;
};

export class AbilityFactory {
public:
    Ability *createAbility(Player*, AbilityType);
};

