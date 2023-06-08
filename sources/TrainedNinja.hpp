#pragma once
#include "Ninjas.hpp"
#include <iostream>

namespace ariel {

    class TrainedNinja : public Ninjas {
        public:
            TrainedNinja (string name, Point pos);
    };
}