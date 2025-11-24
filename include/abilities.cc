export module Abilities;
// contains: derived ability classes 

import <vector>;
import <string>;

import Core;

export class AbilityFactory {
public:
    Ability *createAbility(Player*, AbilityType);
};

export class Download : public Ability {
public:
    Download(Player* player) : Ability{player, AbilityType::Download} {}
    void activate(AbilityParam) override;
};

export class Firewall : public Ability {
public:
    Firewall(Player* player) : Ability{player, AbilityType::Firewall} {}
    void activate(AbilityParam) override;
};

export class Immunity : public Ability {
public:
    Immunity(Player* player) : Ability{player, AbilityType::Immunity} {}
    void activate(AbilityParam) override;
};

export class LevelUp : public Ability {
public:
    LevelUp(Player* player) : Ability{player, AbilityType::LevelUp} {}
    void activate(AbilityParam) override;
};

export class LinkBoost : public Ability {
public:
    LinkBoost(Player* player) : Ability{player, AbilityType::LinkBoost} {}
    void activate(AbilityParam) override;
};

export class Polarize : public Ability {
public:
    Polarize(Player* player) : Ability{player, AbilityType::Polarize} {}
    void activate(AbilityParam) override;
};

export class Scan : public Ability {
public:
    Scan(Player* player) : Ability{player, AbilityType::Scan} {}
    void activate(AbilityParam) override;
};

export class SwapPos : public Ability {
public:
    SwapPos(Player* player) : Ability{player, AbilityType::SwapPos} {}
    void activate(AbilityParam) override;
};

export class Wall : public Ability {
public:
    Wall(Player* player) : Ability{player, AbilityType::Wall} {}
    void activate(AbilityParam) override;
};
