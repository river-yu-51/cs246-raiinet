module Core;

Link::Link(Player *player, char symbol, int strength, Tile *tile, int distance, bool immune, bool downloaded)
    : player{player}, symbol{symbol}, strength{strength}, tile{tile}, distance{distance}, immune{immune}, downloaded{downloaded} {}

Player *Link::getPlayer() { return player; }

char Link::getSymbol() { return symbol; }

int Link::getStrength() { return strength; }

Tile *Link::getTile() { return tile; }

bool Link::isImmune() { return immune; }

bool Link::isDownloaded() { return downloaded; }

void Link::setValue(int val) { strength = val; }

void Link::setTile(Tile *t) { tile = t; }

void Link::setDistance(int dist) { distance = dist; }

void Link::setImmune(bool im) { immune = im; }

void Link::setDownloaded(bool dl) { downloaded = dl; }
