#pragma once
#include "Team.hpp"

namespace ariel {
    class SmartTeam : public Team {
        public:
            SmartTeam (Character* leader) : Team(leader) {}
            void attack (Team* enemy) override;
            void print () override;
            Character* findEnemyForNinja (Team* enemy, Character* theNinja);
    };
}