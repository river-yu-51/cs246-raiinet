export module Board;

import <vector>;

import Subject;
import Tile;

export class Board : public Subject {
    std::vector<std::vector<Tile*>> grid;
public:
    Board(std::vector<std::vector<Tile*>>);

    Tile* getTile(int, int);
    std::vector<std::vector<Tile*>> getGrid();

    void setTile(int, int, Tile*);
};