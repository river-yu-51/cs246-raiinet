module Core;

Ability::Ability(Player *player, AbilityType type) : player{player}, type{type} {}

Player *Ability::getPlayer() { return player; }
AbilityType Ability::getType() { return type; }

std::ostream &operator<<(std::ostream &os, AbilityType type) {
    switch(type) {
        case AbilityType::Download: return os << "Download";
        case AbilityType::Firewall: return os << "Firewall";
        case AbilityType::Immunity: return os << "Immunity";
        case AbilityType::LevelUp: return os << "LevelUp";
        case AbilityType::LinkBoost: return os << "LinkBoost";
        case AbilityType::Polarize: return os << "Polarize";
        case AbilityType::Scan: return os << "Scan";
        case AbilityType::SwapPos: return os << "SwapPos";
        case AbilityType::Wall: return os << "Wall";
    }
    return os << "Unknown ability type";
}
