module Core;

Virus::Virus(char symbol, Player *player, int strength, Tile *tile,
           int distance, bool immune, bool downloaded, bool revealed)
    : Link{player, symbol, strength, tile, distance, immune, downloaded, revealed} {}

std::string Virus::getType() { return "virus"; }

void Virus::download() { getPlayer()->download(this); }