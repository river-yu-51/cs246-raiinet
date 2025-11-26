module Core;
import Abilities;


import <string>;
import <vector>;
import <map>;
import <string>;
import <iostream>;
import <algorithm>;

Player::Player(int playerNum,
               std::vector<Link*> links,
               std::vector<Ability*> abilities,
               std::map<Ability*, int> usage,
               bool isEliminated, bool isWon,
               int downloadedData,
               int downloadedViruses)
    : playerNum{playerNum},
      links{links},
      abilities{abilities},
      usage{usage},
      isEliminated{isEliminated},
      downloadedData{downloadedData},
      downloadedViruses{downloadedViruses} {}

void Player::useAbility(Ability *ability) {
    // prompt player
    // check if available/valid
    ability->activate(AbilityParam{ /* STUFF HERE IDK */ });
    usage[ability]++;
}

void Player::moveLink(Link *link) { 
    // prompt player
    // get destination tile
    // move link to destination tile
}

void Player::download(Link *link) {
    if (!link) return;

    if (link->getType() == "data") {
        downloadedData++;
    } else if (link->getType() == "virus") {
        downloadedViruses++;
    }

    checkWinLose();

    delete link;
}

int Player::getPlayerNum() { return playerNum; }

std::vector<Link*> &Player::getLinks() { return links; }

std::vector<Ability*> &Player::getAbilities() { return abilities; }

Link *Player::getLink(int index) { 
    if (index < 0 || index >= static_cast<int>(links.size())) {
        return nullptr;
    }
    return links[index]; 
}

int Player::getDataCount() { return downloadedData; }

int Player::getVirusCount() { return downloadedViruses; }

bool Player::generateAbilities(std::string order, std::ostream&os) {
    if (order.size() != 5) {
        return false;
    }
    const std::map<char, AbilityType> abilityMap = {
        {'L', AbilityType::LinkBoost},
        {'F', AbilityType::Firewall},
        {'D', AbilityType::Download},
        {'P', AbilityType::Polarize},
        {'S', AbilityType::Scan},
        {'U', AbilityType::Upgrade},
        {'I', AbilityType::Immunity},
        {'W', AbilityType::Wall}
    };
    for (char c : order) {
        auto it = abilityMap.find(c);
        if (it == abilityMap.end()) {
            std::cout << "Invalid ability code: " << c << std::endl;
            return false;
        }
        AbilityFactory factory;  
        Ability* ability = factory.createAbility(this, it->second); // idk
            if (usage.find(ability) == usage.end()) {
                usage[ability] = 1;
                abilities.push_back(ability);
        } else if (usage[ability] < 2) {
            usage[ability]++;
            abilities.push_back(ability);
        } else {
            os << "Ability " << c << " already at max usage." << std::endl;
            delete ability;
            return false;
        }
    }
    // check if ability exists in usage
    // if exist, check < 2 -> add 1
    // if not exist, add and usage = 1
    return true;
    // l -> link boost
    // f -> firewall
    // d -> download
    // p -> polarize
    // s -> scan
    // u -> upgrade
    // i -> immunity
    // w -> wall
}


bool Player::generateLinks(std::string order, std::ostream &os, Board *board) {

    if (order.size() != 16) {
        return false;
    }
    const int NUM_LINKS = 8;
    links.clear();

    const std::vector<std::vector<char>> symbolSets = {
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
        {'s', 't', 'u', 'v', 'w', 'x', 'y', 'z'},
        {'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}
    };
    std::cout << playerNum;
    const auto &symbols = symbolSets[(playerNum - 1) % symbolSets.size()];
    int i = 0;
    while (i+1 < order.length()) {
        std::cout << " i " << i << std::endl;
        Link *newLink = nullptr;
        char letter = order[i];
        int strength = order[i + 1] - '0';
        std::cout << "Pair: " << letter << strength << "\n";
        char symbol = symbolSets[(playerNum - 1) % symbolSets.size()][i/2];
        std::cout << symbol << std::endl;
        if (letter == 'D') {
            newLink = new Data{symbol, this, strength, nullptr, 0, false, false};
            // data
        }
        else if (letter == 'V') {
            newLink = new Virus{symbol, this, strength, nullptr, 0, false, false};
            // virus
        }
        i += 2; // move to next pair

    // std::vector<std::string> remainingLinks = {
    //     "D1", "D2", "D3", "D4",
    //     "V1", "V2", "V3", "V4"
    // };

    // for (int i = 0; i < NUM_LINKS; ++i) {
    //     os << "Available links: ";
    //     for (const auto &linkStr : remainingLinks) {
    //         os << linkStr << " ";
    //     }
    //     os << "\nSelect link " << symbols[i] << ": ";

    //     std::string choice;
    //     is >> choice;

    //     auto it = std::find(remainingLinks.begin(), remainingLinks.end(), choice);
    //     if (it == remainingLinks.end()) {
    //         os << "Invalid choice. Try again.\n";
    //         --i; // retry
    //         continue;
    //     }

    //     char symbol = symbols[i];
    //     Link *newLink = nullptr;
    //     int strength = std::stoi(choice.substr(1));

    //     if (choice[0] == 'D') {
    //         newLink = new Data{symbol, this, strength, nullptr, 0, false, false};
    //     } else if (choice[0] == 'V') {
    //         newLink = new Virus{symbol, this, strength, nullptr, 0, false, false};
    //     }

        Tile *tileForSymbol = nullptr;
        auto &grid = board->getGrid();
        for (auto &row : grid) {
            for (Tile *t : row) {
                std::cout << t->getSymbol();
                if (t->getSymbol() == symbol) {
                    std::cout << "found symbol " << symbol << std::endl;
                    tileForSymbol = t;
                    break;
                }
            }
        }


        if (!tileForSymbol) {
            os << "Internal error: no tile for symbol " << symbol << "\n";
            delete newLink;
            i -= 2;
            continue;
        }
        std::cout<< "newlink";
        tileForSymbol->setLink(newLink);
        std::cout<< "set tile";
        newLink->setTile(tileForSymbol);
        std::cout<< "push back";
        links.push_back(newLink);
    }
    std::cout<<"done";

    return true;
}

void Player::checkWinLose() {
    if (downloadedViruses >= 4) {
        isEliminated = true;
    }
    else if (downloadedData >= 4) {
        isWon = true;
    }
}

bool Player::getIsWon() { return isWon; }
bool Player::getIsEliminated() { return isEliminated; }
