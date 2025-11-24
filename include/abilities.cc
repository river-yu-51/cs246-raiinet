export module Abilities;
// contains: derived ability classes 

import <vector>;
import <string>;

import Core;

export class Download : public Ability {
public:
    void activate(AbilityParam) override;
};

export class Firewall : public Ability {
public:
    void activate(AbilityParam) override;
};

export class Immunity : public Ability {
public:
    void activate(AbilityParam) override;
};

export class LevelUp : public Ability {
public:
    void activate(AbilityParam) override;
};

export class LinkBoost : public Ability {
public:
    void activate(AbilityParam) override;
};

export class Polarize : public Ability {
public:
    void activate(AbilityParam) override;
};

export class Scan : public Ability {
public:
    void activate(AbilityParam) override;
};

export class SwapPos : public Ability {
public:
    void activate(AbilityParam) override;
};

export class Wall : public Ability {
public:
    void activate(AbilityParam) override;
};
