export module Wall;

import Ability;

export class Wall : public Ability {
public:
    void activate(AbilityParam) override;
};