module Core;

import <vector>;

import Subject;

Board::Board(std::vector<std::vector<Tile*>> grid) : grid{std::move(grid)} {}

Tile* Board::getTile(int x, int y) { return grid[x][y]; }

std::vector<std::vector<Tile*>> &Board::getGrid() { return grid; }

void Board::setTile(int x, int y, Tile *tile) {
    grid[x][y] = tile;
    notifyObservers();
}

void Board::moveLink(Link *link, int x, int y) {
    link->getTile()->setLink(nullptr);
    Tile *dest = getTile(x, y);
    dest->setLink(link);
    link->setTile(dest);
    notifyObservers();
}
