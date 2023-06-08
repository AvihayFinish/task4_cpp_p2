#include "Character.hpp"
using namespace ariel;

Character::Character (Point pos, int pointsLive, string name) : name(name), pos(pos), pointsLive(pointsLive), isInTeam(false) {
    if (name == "") {
        throw runtime_error("the character must have a name");
    }
}

Character::Character (const Character& other) : pos(other.pos), pointsLive(other.pointsLive), name(other.name), isInTeam(other.isInTeam) {}

Character::Character (Character&& other) noexcept: pos(other.pos), pointsLive(other.pointsLive), name(move(other.name)) {
    other.pointsLive = 0;
}

Character& Character::operator= (const Character& other) {
    if (this != &other) {
        this->name = other.name;
        this->pointsLive = other.pointsLive;
    }
    return *this;
}

Character& Character::operator= (Character&& other) noexcept {
    if (this != &other) {
        this->name = move(other.name);
        this->pointsLive = other.pointsLive;
        other.pointsLive = 0;
    }
    return *this;
}

bool Character::isAlive () {
    if (this->pointsLive > 0) {
        return true;
    }
    return false;
}

double Character::distance (Character* other) const {
    if (other == nullptr) {
        throw invalid_argument("the other character is null");
    }
    return this->pos.distance(other->pos); // distance of point class
}

void Character::hit (int num) {
    if (num < 0) {
        throw invalid_argument("hit must be positive number");
    }
    if (this->getPointsLive() > 0) {
        this->pointsLive -= num;
    }
    if (this->getPointsLive() < 0) {
        this->pointsLive = 0;
    }
}

string Character::getName () {
    return this->name;
}

Point Character::getLocation () {
    return this->pos;
}

int Character::getPointsLive () {
    return this->pointsLive;
}

bool Character::getIsInTeam () {
    return this->isInTeam;
}

void Character::setIsInTeam (bool isOrNot) {
    this->isInTeam = isOrNot;
}

void Character::setLocation (Point newLoc) {
    this->pos.setX(newLoc.getX());
    this->pos.setY(newLoc.getY());
}

string Character::print () {
    return "";
}

bool Character::operator== (Character other) {
    if (this->getName() == other.getName()) {
        return true;
    }
    return false;
}