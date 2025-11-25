module Core;

Data::Data(char symbol, Player *player, int strength, Tile *tile, int distance, bool immune, bool downloaded)
    : Link{symbol, player, strength, tile, distance, immune, downloaded} {}

void Data::getType() { return "data"; }

void Data::download() { getPlayer()->download(this); }
