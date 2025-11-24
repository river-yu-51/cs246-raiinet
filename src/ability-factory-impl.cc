module Abilities;

//import Abilities;

Ability *AbilityFactory::createAbility(Player *player, AbilityType type) {
    switch (type) {
        case AbilityType::Download:
            return new Download{player};
        case AbilityType::Firewall:
            return new Firewall{player};
        case AbilityType::Immunity:
            return new Immunity{player};
        case AbilityType::LevelUp:
            return new LevelUp{player};
        case AbilityType::LinkBoost:
            return new LinkBoost{player};
        case AbilityType::Polarize:
            return new Polarize{player};
        case AbilityType::Scan:
            return new Scan{player};
        case AbilityType::SwapPos:
            return new SwapPos{player};
        case AbilityType::Wall:
            return new Wall{player};
    }
    return nullptr;
}
