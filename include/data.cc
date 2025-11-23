export module Data;

import Link;

export class Data : public Link {
public:
    Data(Player*, int, Tile*, int, bool, bool);

    void download() override;
}