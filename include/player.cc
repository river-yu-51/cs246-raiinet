export module Player;

import <string>;
import <vector>;
import <map>;

import Link;

class Ability;

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
