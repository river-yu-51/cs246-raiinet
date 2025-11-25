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
    Tile(int x, int y, char symbol, bool isPort, bool isWalled, Link *link, int firewallPlayer);

    void setSymbol(char symbol);
    void setFirewallPlayer(int firewallPlayer);
    void setIsWalled(bool isWalled);
    void setIsPort(bool isPort);
    void setLink(Link* link);

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
    Link(char symbol, Player *player, int strength, Tile *tile, int distance, bool immune, bool downloaded);

    Player *getPlayer();
    int getStrength();
    Tile *getTile();
    bool isImmune();
    bool isDownloaded();
    char getSymbol();

    void setValue(int value);
    void setTile(Tile *tile);
    void setDistance(int distance);
    void setImmune(bool immune);
    void setDownloaded(bool downloaded);
    virtual string getType = 0;
    virtual void download() = 0;
};

export class Data : public Link {
public:
    Data(char symbol, Player *player, int strength, Tile *tile, int distance, bool immune, bool downloaded);

    string getType() override;
    void download() override;
};

export class Virus : public Link {
public:
    Virus(char symbol, Player *player, int strength, Tile *tile, int distance, bool immune, bool downloaded);
    string getType() override;
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
    Player(int playerNum, std::vector<Link*> links, std::vector<Ability*> abilities, std::map<Ability*, int> usage, bool isEliminated, bool isWon, int downloadedData, int downloadedViruses);

    // void useAbility(Ability*);
    // void moveLink(Link*);
    void download(Link* link);

    int getPlayerNum();
    void generateLinks(int boardSize);
    std::vector<Link*> &getLinks();
    std::vector<Ability*> &getAbilities();
    Link *getLink(int index);
    int getDataCount();
    int getVirusCount();

    bool getIsEliminated();
    bool getIsWon();
    void checkWinLose();
};

export class Board : public Subject {
    std::vector<std::vector<Tile*>> grid;
public:
    Board(std::vector<std::vector<Tile*>> grid);

    Tile *getTile(int x, int y);
    std::vector<std::vector<Tile*>> &getGrid();

    void MoveLink(Link *link, int x, int y);

    void setTile(int x, int y, Tile* tile);
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

export std::ostream &operator<<(std::ostream &os, AbilityType type);

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
    Ability(Player *player, AbilityType type);

    Player *getPlayer();
    AbilityType getType();
    virtual void activate(AbilityParam param) = 0;
};

