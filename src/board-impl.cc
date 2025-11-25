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

void Board::MoveLink(Link *link, int x, int y) {
    link->getTile()->setLink(nullptr);
    Tile *destTile = getTile(x, y);
    destTile->setLink(link);
    link->setTile(destTile);
    notifyObservers();
}
