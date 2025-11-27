export module Abilities;
// contains: AbilityFactory and derived ability classes 

import <vector>;
import <string>;

import Core;

export class AbilityFactory {
public:
    Ability *createAbility(Player *player, AbilityType type);
};

export class Download : public Ability {
public:
    Download(Player *player) : Ability(player) {}

    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class Firewall : public Ability {
    AbilityType type = AbilityType::Firewall;
public:
    Firewall(Player *player) : Ability(player) {}

    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class Immunity : public Ability {
    AbilityType type = AbilityType::Immunity;
public:
    Immunity(Player *player) : Ability(player) {}

    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class Upgrade : public Ability {
    AbilityType type = AbilityType::Upgrade;
public:
    Upgrade(Player *player) : Ability(player) {}

    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class LinkBoost : public Ability {
    AbilityType type = AbilityType::LinkBoost;
public:
    LinkBoost(Player *player) : Ability(player) {}

    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class Polarize : public Ability {
    AbilityType type = AbilityType::Polarize;
public:
    Polarize(Player *player) : Ability(player) {}

    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class Scan : public Ability {    
    AbilityType type = AbilityType::Scan;
public:
    Scan(Player *player) : Ability(player) {}

    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export class Wall : public Ability {
    AbilityType type = AbilityType::Wall;
public:
    Wall(Player *player) : Ability(player) {}

    void activate(AbilityParam param) override;

    AbilityType getType() override;
};

export bool generateAbilitiesForPlayer(Player *player, std::string order);
