export module AbilityFactory;

import AbilityType;
import Ability;
import Player;

export class AbilityFactory {
public:
    Ability *createAbility(Player*, AbilityType);
};