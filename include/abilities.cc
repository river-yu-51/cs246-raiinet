export module Abilities;
// contains: AbilityType, AbilityParam, Ability, AbilityFactory, and all derived Ability classes

import <vector>;
import <string>;

import Core;

export enum class AbilityType {
    LinkBoost,
    Firewall,
    Download,
    Polarize,
    Scan,
    LevelUp,
    SwapPos,
    Immunity,
    Wall
};

export struct AbilityParam {
    Player *player;
    Link *primaryLink;
    Link *secondaryLink;
    Tile *targetTile;
};

export class Ability {
    Player *player;
public:
    Player *getPlayer();
    virtual void activate(AbilityParam) = 0;
};

export class AbilityFactory {
public:
    Ability *createAbility(Player*, AbilityType);
};


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
