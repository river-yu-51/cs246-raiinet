export module Board;

import <vector>;
import Tile;

export class Board {
    std::vector<std::vector<Tile*>> grid;
public:
    Board(std::vector<std::vector<Tile*>>);

    Tile* getTile(int, int);
    std::vector<std::vector<Tile*>> getGrid();
};