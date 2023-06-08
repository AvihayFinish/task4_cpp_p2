#include "Ninjas.hpp"
using namespace std;
using namespace ariel;

Ninjas::Ninjas (string name, Point pos, int speed, int pointsLive) : Character(pos, pointsLive, name), speed(speed) {

}

void Ninjas::move (Character* enemy) {
    if (enemy == nullptr) {
        throw invalid_argument("the enemy is null");
    }
    else if (this == enemy) {
        throw runtime_error("you cannot move to yourself");
    }
    else if (!this->isAlive()) {
        throw runtime_error("you cannot move died character");
    }
    double dis = this->distance(enemy);
    if (dis < this->getSpeed()) {
        this->setLocation(enemy->getLocation());
    }
    else {
        Point newPos = Point::moveTowards(this->getLocation(), enemy->getLocation(), this->getSpeed());
        this->setLocation(newPos);
    }
}

void Ninjas::slash (Character* enemy) {
    if (enemy == nullptr) {
        throw invalid_argument("the character is null");
    }
    else if (this == enemy) {
        throw runtime_error("you cannot slash yourself");
    }
    else if (!this->isAlive()) {
        throw runtime_error("your nin is dead");
    }
    else if (!enemy->isAlive()) {
        throw runtime_error("the enemy is died");
    }
    else if (this->distance(enemy) <= 1) {
        enemy->hit(40);
    }
}

int Ninjas::getSpeed () {
    return this->speed;
}

string Ninjas::print () {
    if (this->isAlive()) {
        string pointsLiveStr = to_string(this->getPointsLive());
        string Xposition = to_string(this->getLocation().getX());
        string Yposition = to_string(this->getLocation().getY());
        return "N-" + this->getName() + ", pointsLive: " + pointsLiveStr + ", position: " + "(" + Xposition + ", " + Yposition + ")";
    }
    return "N-" + this->getName();
}
