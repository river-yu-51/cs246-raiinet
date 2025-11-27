module Core;

import <iostream>;

Ability::Ability(Player *p) : player{p} {}

void Ability::setPlayer(Player *p) { player = p; }

Player *Ability::getPlayer() { return player; }

std::ostream &operator<<(std::ostream &os, AbilityType type) {
    switch (type) {
        case AbilityType::LinkBoost:
            os << "LinkBoost";
            break;
        case AbilityType::Firewall:
            os << "Firewall";
            break;
        case AbilityType::Download:
            os << "Download";
            break;
        case AbilityType::Polarize:
            os << "Polarize";
            break;
        case AbilityType::Scan:
            os << "Scan";
            break;
        case AbilityType::Upgrade:
            os << "Upgrade";
            break;
        case AbilityType::SwapPos:
            os << "SwapPos";
            break;
        case AbilityType::Immunity:
            os << "Immunity";
            break;
        case AbilityType::Wall:
            os << "Wall";
            break;
    }
    return os;
}
