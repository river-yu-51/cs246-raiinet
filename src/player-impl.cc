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
               bool isEliminated, bool isWon,
               int downloadedData,
               int downloadedViruses):
    playerNum{playerNum},
    links{links},
    abilities{abilities},
    isEliminated{isEliminated},
    isWon{isWon},
    downloadedData{downloadedData},
    downloadedViruses{downloadedViruses} {}

void Player::download(Link *link) {
    if (!link) return;
    if (link->isDownloaded()) { return; }
    // reveal link type and strength to opponent once downloaded
    link->reveal();

    // detach from board if still on a tile
    Tile *tile = link->getTile();
    if (tile && tile->getLink() == link) {
        tile->setLink(nullptr);
    }
    link->setTile(nullptr);

    // add to counter based on type of link
    if (link->getType() == "data") {
        downloadedData++;
    } else if (link->getType() == "virus") {
        downloadedViruses++;
    }

    link->setDownloaded(true);
    checkWinLose();
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

bool isValidLinkOrder(const std::string &order) {
    if (order.size() != 16) { return false; }

    std::vector<std::string> playerLinks;

    // every 2 characters = 1 link
    for (int i = 0; i < 16; i += 2) { playerLinks.push_back(order.substr(i, 2)); }
    std::sort(playerLinks.begin(), playerLinks.end());

    // check all 8 link types were included in string
    if (playerLinks != std::vector<std::string>{
            "D1", "D2", "D3", "D4",
            "V1", "V2", "V3", "V4"}) {
        return false;
    }
    return true;
}

bool Player::generateLinks(std::string order, std::ostream &os, Board *board) {
    // check if link order is valid
    if (!isValidLinkOrder(order)) { return false; }

    const int NUM_LINKS = 8;
    links.clear();

    const std::vector<std::vector<char>> symbolSets = {
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}
    };

    const auto &symbols = symbolSets[playerNum];

    // go through string by every 2 characters
    for (int i = 0; i < 2*NUM_LINKS; i += 2) {
        char letter = order[i];
        int strength = order[i + 1] - '0';
        // check for invalid numbers/letters
        if ((letter != 'D' && letter != 'V') || strength < 1 || strength > 4) {
            return false;
        }
        
        // create new link based on letter type
        if (letter == 'D') {
            Link *newLink = new Data{symbols[i/2], this, strength, nullptr, 1, false, false, false};
            links.push_back(newLink);
        }
        else if (letter == 'V') {
            Link *newLink = new Virus{symbols[i/2], this, strength, nullptr, 1, false, false, false};
            links.push_back(newLink);
        }

        Tile *tileForSymbol = nullptr;
        auto &grid = board->getGrid();
        for (auto &row : grid) {
            for (Tile *t : row) {
                // get tile the link is on
                if (t->getSymbol() == symbols[i/2]) {
                    tileForSymbol = t;
                    break;
                }
            }
            if (tileForSymbol) {
                break;
            }
        }

        if (!tileForSymbol) {
            os << "Internal error: no tile for symbol " << symbols[i/2] << "\n";
            return false;
        }
        // add tile to link
        links.back()->setTile(tileForSymbol);
        // add link to tile
        tileForSymbol->setLink(links.back());

        if (!tileForSymbol->getIsPort() && !tileForSymbol->getIsWalled()) {
            tileForSymbol->setSymbol('.'); // clear temp marker
        }

        std::cout << "Placed link " << links.back()->getSymbol() << " of type "
             << (letter == 'D' ? "Data" : "Virus") << " with strength "
             << strength << " at (" << tileForSymbol->getX() << ", "
             << tileForSymbol->getY() << ")\n";
    }

    return true;
}

void Player::checkWinLose() {
    if (downloadedViruses >= 4) { isEliminated = true; }
    else if (downloadedData >= 4) { isWon = true; }
}

bool Player::getIsWon() { return isWon; }
bool Player::getIsEliminated() { return isEliminated; }

Player::~Player() {
    for (Link *link : links) {
        delete link;
    }
    for (Ability *ability : abilities) {
        delete ability;
    }
}
