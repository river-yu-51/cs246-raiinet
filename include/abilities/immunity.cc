export module Immunity;

import Ability;

export class Immunity : public Ability {
public:
    void activate(AbilityParam) override;
};