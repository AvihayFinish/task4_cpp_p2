#pragma once
#include <iostream>
#include "Character.hpp"
using namespace std;

namespace ariel {

    class Cowboy : public Character {
        private:
            int numBoolets;
        public:
            Cowboy (string name, Point pos);
            Cowboy (const Cowboy& other);
            Cowboy(Cowboy&& other) noexcept;
            ~Cowboy () override {}
            Cowboy& operator= (const Cowboy& other);
            Cowboy& operator=(Cowboy&& other) noexcept;
            void shoot (Character* enemy);
            bool hasboolets ();
            void reload ();
            string print () override;
            int getNum ();
    };
}

