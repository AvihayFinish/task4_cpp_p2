#pragma once
#include <iostream>
#include "Character.hpp"

namespace ariel {

    class Ninjas : public Character {
        private:
            int speed;
        public:
            Ninjas (string name, Point pos, int speed, int pointsLive);
            void move (Character* enemy);
            void slash (Character* enemy);
            int getSpeed ();
            string print () override;
            
    };
}