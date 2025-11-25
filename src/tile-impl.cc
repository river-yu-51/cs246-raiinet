module Core;

Tile::Tile(int x, int y, char symbol, bool isPort, bool isWalled, Link *link, int firewallPlayer)
    : x{x}, y{y}, symbol{symbol}, isPort{isPort}, isWalled{isWalled},
      link{link}, firewallPlayer{firewallPlayer} {}

void Tile::setSymbol(char sym) { symbol = sym; }

void Tile::setFirewallPlayer(int player) { firewallPlayer = player; }

void Tile::setIsWalled(bool walled) { isWalled = walled; }

void Tile::setIsPort(bool port) { isPort = port; }

void Tile::setLink(Link *l) { link = l; }

int Tile::getX() { return x; }
int Tile::getY() { return y; }

Link *Tile::getLink() { return link; }

int Tile::getFirewallPlayer() { return firewallPlayer; }

bool Tile::getIsPort() { return isPort; }

bool Tile::getIsWalled() { return isWalled; }

char Tile::getSymbol() { return symbol; }
