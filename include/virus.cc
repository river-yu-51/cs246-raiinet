export module Virus;

import Link;

export class Virus : public Link {
public:
    Virus(Player*, int, Tile*, int, bool, bool);

    void download() override;
}