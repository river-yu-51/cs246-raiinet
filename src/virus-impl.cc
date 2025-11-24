module Core;

Virus::Virus(Player *player, int strength, Tile *tile, int distance, bool immune, bool downloaded)
    : Link{player, strength, tile, distance, immune, downloaded} {}

void Virus::download() {
    getPlayer()->download(this);
}
