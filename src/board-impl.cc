module Board;

import <vector>;

import Tile;

Board::Board(std::vector<std::vector<Tile*>> grid) : grid{grid} {}

Tile* Board::getTile(int x, int y) { return grid[x][y]; }

std::vector<std::vector<Tile*>> Board::getGrid() { return grid; }

void Board::setTile(int x, int y, Tile* tile) { grid[x][y] = tile; }
