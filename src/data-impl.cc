module Core;

import Core;

Data::Data(Player *player, int strength, Tile *tile, int distance, bool immune, bool downloaded)
    : Link{player, strength, tile, distance, immune, downloaded} {}

void Data::download() {
    player->download(this);
}
