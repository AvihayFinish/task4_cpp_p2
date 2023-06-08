#pragma once
#include <iostream>
#include <string.h>
#include "Point.hpp"
using namespace std;

namespace ariel {

    class Character {
        private:
            Point pos;
            int pointsLive;
            string name;
            bool isInTeam;
        public:
            Character (Point pos, int pointsLive, string name);
            Character (const Character& other);
            Character (Character&& other) noexcept;
            virtual ~Character () {}
            Character& operator= (const Character& other);
            Character& operator= (Character&& other) noexcept;
            bool isAlive ();
            double distance (Character* other) const;
            void hit (int num);
            string getName ();
            Point getLocation ();
            int getPointsLive ();
            bool getIsInTeam();
            void setIsInTeam(bool isOrNot);
            void setLocation (Point newLoc);
            virtual string print ();
            bool operator== (Character other);
    };
}