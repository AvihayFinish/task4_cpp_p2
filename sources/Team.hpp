#pragma once
#include <iostream>
#include <limits>
#include <string.h>
#include <vector>
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"
#include "Cowboy.hpp"
using namespace std;

namespace ariel {

    class Team {
        private:
            std::vector<Character*> theTeam;
            Character* leader;
        public:
            Team (Character* leader);
            Team (Team& other);
            Team (Team&& other) noexcept;
            virtual ~Team ();
            Team& operator= (const Team& other);
            Team& operator= (Team&& other) noexcept;
            void add (Character* fre);
            virtual void attack (Team* enemy);
            virtual int stillAlive ();
            Character* getLeader();
            void setLeader(Character* leader);
            void setLeaderIfThePrevDead ();
            Character* passOverTheEnemyTeam (Team* enemy);
            virtual void print (); 
            vector<Character*>& getTheTeam ();

    };
}