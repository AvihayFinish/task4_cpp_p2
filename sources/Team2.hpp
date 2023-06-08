#pragma once
#include "Team.hpp"

namespace ariel {
    class Team2 : public Team {
        public:
            Team2 (Character* leader);
            void attack (Team* enemy) override;
            int stillAlive () override;
            void print () override;
    };
}