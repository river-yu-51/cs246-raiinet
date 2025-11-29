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
export class Board;

// Tile class representing each cell on the board
export class Tile {
    Link *link;
    int x, y;
    int firewallPlayer;
    bool isPort;
    bool isWalled;
    char symbol;
public:
    Tile(Link *link, int x, int y, int firewallPlayer, bool isPort, bool isWalled, char symbol);

    // Getters
    Link *getLink();
    int getX();
    int getY();
    int getFirewallPlayer();
    bool getIsPort();
    bool getIsWalled();
    char getSymbol();

    // Setters
    void setSymbol(char symbol);
    void setFirewallPlayer(int firewallPlayer);
    void setIsWalled(bool isWalled);
    void setIsPort(bool isPort);
    void setLink(Link *link);
};

// Link class representing data/virus units controlled by players
export class Link {
    Player *player;
    char symbol;
    int strength;
    Tile *tile;
    int distance; // number of "moves per move"
    bool immune;
    bool downloaded;
    bool revealed;
public:
    virtual ~Link() = default;

    Link(Player *player, char symbol, int strength, Tile *tile, int distance, bool immune, bool downloaded, bool revealed);

    // Getters
    Player *getPlayer();
    char getSymbol();
    int getStrength();
    Tile *getTile();
    bool isImmune();
    bool isDownloaded();
    bool isRevealed();
    int getDistance();

    // Setters
    void setStrength(int value);
    void setTile(Tile *tile);
    void setDistance(int distance);
    void setImmune(bool immune);
    void setDownloaded(bool downloaded);
    void reveal();
    
    // Get data/virus type
    virtual std::string getType() = 0;

    // Download link
    virtual void download() = 0;
};

// Links of type data
export class Data : public Link {
public:
    Data(char symbol, Player *player, int strength, Tile *tile, int distance, bool immune, bool downloaded, bool revealed);

    // Verifies the type of link
    std::string getType() override;

    // Downloads the link
    void download() override;
};

// Links of type virus
export class Virus : public Link {
public:
    Virus(char symbol, Player *player, int strength, Tile *tile, int distance, bool immune, bool downloaded, bool revealed);

    // Verifies the type of link
    std::string getType() override;

    // Downloads the link
    void download() override;
};

// Player class representing each player in the game
export class Player {
    int playerNum;
    std::vector<Link*> links;
    std::vector<Ability*> abilities;
    bool isEliminated;
    bool isWon;
    int downloadedData;
    int downloadedViruses;
public:
    Player(int playerNum, std::vector<Link*> links, std::vector<Ability*> abilities, bool isEliminated, bool isWon, int downloadedData, int downloadedViruses);

    // this player downloads the specified link
    void download(Link* link);

    // Getters
    int getPlayerNum();
    std::vector<Link*> &getLinks();
    std::vector<Ability*> &getAbilities();
    Link *getLink(int index);
    int getDataCount();
    int getVirusCount();
    bool getIsEliminated();
    bool getIsWon();
    void checkWinLose();

    // Initializes links based on order string
    bool generateLinks(std::string order, std::ostream &os, Board *board);
    
    // Dtor also deletes links and abilities the Player owns
    ~Player();
};

// Board class representing the game board
export class Board : public Subject {
    std::vector<std::vector<Tile*>> grid; // 2D grid of tiles
public:
    Board(std::vector<std::vector<Tile*>>);

    // Getters
    Tile *getTile(int x, int y);
    std::vector<std::vector<Tile*>> &getGrid();

    // Setters
    void setTile(int x, int y, Tile *tile);

    // Move link to specified coordinates
    void moveLink(Link *link, int x, int y);

    ~Board();
};

// 8 ability types we're using
export enum class AbilityType {
    LinkBoost,
    Firewall,
    Download,
    Polarize,
    Scan,
    Upgrade,
    Immunity,
    Wall
};

// Overload << operator for AbilityType for easy printing
export std::ostream &operator<<(std::ostream &os, AbilityType type);

// Struct to hold parameters for ability activation
export struct AbilityParam {
    Player *player;
    Link *primaryLink;
    Link *secondaryLink;
    Tile *tile;
};

// Base Ability class
export class Ability {
    Player *player; // owner of the ability
    bool available = true; // whether the ability can be used
public:
    Ability(Player *player);

    virtual ~Ability() = default;

    // Getters
    Player *getPlayer();
    bool isAvailable();

    // Setters
    void setPlayer(Player *p);
    void setAvailable(bool avail);

    // Use ability (override in derived classes)
    virtual bool activate(AbilityParam param) = 0;

    // Get ability type (override in derived classes)
    virtual AbilityType getType() = 0;
};
