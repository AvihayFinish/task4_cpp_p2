#pragma once
#include <iostream>
#include "Ninjas.hpp"

namespace ariel {

    class OldNinja : public Ninjas {
        public:
            OldNinja (string name, Point pos);
    };
}