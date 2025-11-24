module Core;

import Core;

Tile::Tile(Link *link, int firewallPlayer, bool isPort, bool isWalled, char symbol)
    : link{link}, firewallPlayer{firewallPlayer}, isPort{isPort}, isWalled{isWalled}, symbol{symbol} {}

void Tile::setSymbol(char sym) { symbol = sym; }

void Tile::setFirewallPlayer(int player) { firewallPlayer = player; }

void Tile::setIsWalled(bool walled) { isWalled = walled; }

void Tile::setIsPort(bool port) { isPort = port; }

void Tile::setLink(Link *l) { link = l; }

Link *Tile::getLink() { return link; }

int Tile::getFirewallPlayer() { return firewallPlayer; }

bool Tile::getIsPort() { return isPort; }

bool Tile::getIsWalled() { return isWalled; }

char Tile::getSymbol() { return symbol; }
