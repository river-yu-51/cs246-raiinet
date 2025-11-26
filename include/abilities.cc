export module Abilities;
// contains: derived ability classes 

import <vector>;
import <string>;

import Core;

export class Download : public Ability {
    AbilityType type = AbilityType::Download;
public:
    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class Firewall : public Ability {
    AbilityType type = AbilityType::Firewall;
public:
    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class Immunity : public Ability {
    AbilityType type = AbilityType::Immunity;
public:
    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class LevelUp : public Ability {
    AbilityType type = AbilityType::LevelUp;
public:
    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class LinkBoost : public Ability {
    AbilityType type = AbilityType::LinkBoost;
public:
    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class Polarize : public Ability {
    AbilityType type = AbilityType::Polarize;
public:
    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class Scan : public Ability {
    AbilityType type = AbilityType::Scan;
public:
    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class SwapPos : public Ability {
    AbilityType type = AbilityType::SwapPos;
public:
    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class Wall : public Ability {
    AbilityType type = AbilityType::Wall;
public:
    void activate(AbilityParam param) override;

    AbilityType getType() override;
};
