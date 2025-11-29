export module Abilities;
// contains: AbilityFactory and derived ability classes 

import <vector>;
import <string>;

import Core;

// Factory class to create abilities
export class AbilityFactory {
public:
    // Creates an ability of the specified type for the given player
    Ability *createAbility(Player *player, AbilityType type);
};

// Download ability - can download an opponent's link
export class Download : public Ability {
public:
    Download(Player *player) : Ability(player) {}

    bool activate(AbilityParam param) override;

    AbilityType getType() override;
};

// Firewall ability - can place a firewall on an empty tile to reveal information and download viruses
export class Firewall : public Ability {
    AbilityType type = AbilityType::Firewall;
public:
    Firewall(Player *player) : Ability(player) {}

    bool activate(AbilityParam param) override;

    AbilityType getType() override;
};

// Immunity ability - can grant immunity to a link from external effects
export class Immunity : public Ability {
    AbilityType type = AbilityType::Immunity;
public:
    Immunity(Player *player) : Ability(player) {}

    bool activate(AbilityParam param) override;

    AbilityType getType() override;
};

// Upgrade ability - can upgrade a link's strength by 1 (unusable on strength 4 links)
export class Upgrade : public Ability {
    AbilityType type = AbilityType::Upgrade;
public:
    Upgrade(Player *player) : Ability(player) {}

    bool activate(AbilityParam param) override;

    AbilityType getType() override;
};

// LinkBoost ability - can increase a link's movement distance by 1
export class LinkBoost : public Ability {
    AbilityType type = AbilityType::LinkBoost;
public:
    LinkBoost(Player *player) : Ability(player) {}

    bool activate(AbilityParam param) override;

    AbilityType getType() override;
};

// Polarize ability - swaps data/virus type of a link
export class Polarize : public Ability {
    AbilityType type = AbilityType::Polarize;
public:
    Polarize(Player *player) : Ability(player) {}

    bool activate(AbilityParam param) override;

    AbilityType getType() override;
};

// Scan ability - reveals information about a link
export class Scan : public Ability {    
    AbilityType type = AbilityType::Scan;
public:
    Scan(Player *player) : Ability(player) {}

    bool activate(AbilityParam param) override;

    AbilityType getType() override;
};

// Wall ability - places a wall on an empty tile that obstructs all movement
export class Wall : public Ability {
    AbilityType type = AbilityType::Wall;
public:
    Wall(Player *player) : Ability(player) {}

    bool activate(AbilityParam param) override;

    AbilityType getType() override;
};

export bool generateAbilitiesForPlayer(Player *player, std::string order);
