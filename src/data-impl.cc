module Core;

Data::Data(char symbol, Player *player, int strength, Tile *tile,
           int distance, bool immune, bool downloaded)
    : Link{player, symbol, strength, tile, distance, immune, downloaded} {}

std::string Data::getType() { return "data"; }

void Data::download() { getPlayer()->download(this); }
