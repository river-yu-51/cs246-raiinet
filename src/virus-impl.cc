module Core;

Virus::Virus(char symbol, Player *player, int strength, Tile *tile, int distance, bool immune, bool downloaded)
    : Link{symbol, player, strength, tile, distance, immune, downloaded} {}

void Virus::download() { getPlayer()->download(this); }