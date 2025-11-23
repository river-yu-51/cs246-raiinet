export module Ability;

import Player;
import AbilityParam;

export class Ability {
    Player *player;
public:
    Player *getPlayer();
    virtual void activate(AbilityParam) = 0;
};
