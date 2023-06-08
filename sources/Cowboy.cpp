#include "Cowboy.hpp"
using namespace ariel;
using namespace std;

Cowboy::Cowboy (string name, Point pos) : Character(pos, 110, name), numBoolets(6) {

}

Cowboy::Cowboy (const Cowboy& other) : Character(other), numBoolets(other.numBoolets) {}

Cowboy::Cowboy(Cowboy&& other) noexcept : Character(move(other)), numBoolets(other.numBoolets) {}

Cowboy& Cowboy::operator= (const Cowboy& other) {
    if (this != &other) {
        Character::operator=(other);
        this->numBoolets = other.numBoolets;
    }
    return *this;
}

Cowboy& Cowboy::operator= (Cowboy&& other) noexcept {
    if (this != &other) {
        Character::operator=(move(other));
        this->numBoolets = other.numBoolets;
        other.numBoolets = 0;
    }
    return *this;
}

void Cowboy::shoot (Character* enemy) {
    if (enemy == nullptr) {
        throw invalid_argument("the enemy is null");
    }
    else if (this == enemy) {
        throw runtime_error("you cannot shoot yourself");
    }
    else if (!this->isAlive()) {
        throw runtime_error("your character is dead");
    }
    else if (!enemy->isAlive()) {
        throw runtime_error("the enemy is died");
    }
    else if (this->hasboolets()) {
        enemy->hit(10);
        numBoolets -= 1;
    }
}

bool Cowboy::hasboolets () {
    if (this->numBoolets > 0 ) {
        return true;
    }
    return false;
}

void Cowboy::reload () {
    if (!(this->isAlive())) {
        throw runtime_error("this cowboy is dead");
    }
    if (this->numBoolets != 6) {
        this->numBoolets = 6;
    }
}

string Cowboy::print () {
    if (this->isAlive()) {
        string pointsLiveStr = to_string(this->getPointsLive());
        string Xposition = to_string(this->getLocation().getX());
        string Yposition = to_string(this->getLocation().getY());
        return "C-" + this->getName() + ", pointsLive: " + pointsLiveStr + ", position: " + "(" + Xposition + ", " + Yposition + ")";
    }
    return "C-" + this->getName();
}

int Cowboy::getNum () {
    return this->numBoolets;
}

