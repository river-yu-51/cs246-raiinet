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
    Link *link;
    int x, y;
    int firewallPlayer;
    bool isPort;
    bool isWalled;
    char symbol;
public:
    Tile(Link *link, int x, int y, int firewallPlayer, bool isPort, bool isWalled, char symbol);

    void setSymbol(char symbol);
    void setFirewallPlayer(int firewallPlayer);
    void setIsWalled(bool isWalled);
    void setIsPort(bool isPort);
    void setLink(Link *link);
    
    Link *getLink();
    int getX();
    int getY();
    int getFirewallPlayer();
    bool getIsPort();
    bool getIsWalled();
    char getSymbol();
};

export class Link {
    Player *player;
    char symbol;
    int strength;
    Tile *tile;
    int distance; // number of "moves per move"
    bool immune;
    bool downloaded;
public:
    Link(Player *player, char symbol, int strength, Tile *tile, int distance, bool immune, bool downloaded);

    Player *getPlayer();
    char getSymbol();
    int getStrength();
    Tile *getTile();
    bool isImmune();
    bool isDownloaded();

    void setValue(int value);
    void setTile(Tile *tile);
    void setDistance(int distance);
    void setImmune(bool immune);
    void setDownloaded(bool downloaded);
    virtual std::string getType() = 0;
    virtual void download() = 0;
};

export class Data : public Link {
public:
    Data(char symbol, Player *player, int strength, Tile *tile, int distance, bool immune, bool downloaded);
    std::string getType() override;
    void download() override;
};

export class Virus : public Link {
public:
    Virus(char symbol, Player *player, int strength, Tile *tile, int distance, bool immune, bool downloaded);
    std::string getType() override;
    void download() override;
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
    Player(int playerNum, std::vector<Link*> links, std::vector<Ability*> abilities, std::map<Ability*, int> usage, bool isEliminated, bool isWon, int downloadedData, int downloadedViruses);

    void useAbility(Ability* ability);
    void moveLink(Link* link);
    void download(Link* link);

    int getPlayerNum();
    void generateLinks(std::istream &is, std::ostream &os);
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
    Board(std::vector<std::vector<Tile*>>);

    Tile *getTile(int x, int y);
    std::vector<std::vector<Tile*>> &getGrid();

    void setTile(int x, int y, Tile *tile);

    void MoveLink(Link *link, int x, int y);
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
public:
    Player *getPlayer();
    virtual void activate(AbilityParam param) = 0;

    virtual AbilityType getType() = 0;
};

export class AbilityFactory {
public:
    Ability *createAbility(Player *player, AbilityType type);
};

