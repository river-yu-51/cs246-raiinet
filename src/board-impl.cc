module Core;

import <vector>;

import Subject;
import Core;

Board::Board(std::vector<std::vector<Tile*>> grid) : grid{std::move(grid)} {}

Tile* Board::getTile(int x, int y) { return grid[x][y]; }

std::vector<std::vector<Tile*>> &Board::getGrid() { return grid; }

void Board::setTile(int x, int y, Tile *tile) {
    grid[x][y] = tile;
    notifyObservers();
}
