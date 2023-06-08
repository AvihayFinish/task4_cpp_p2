#include "Point.hpp"
#include <cmath>
#include <iostream>
using namespace ariel;
using namespace std;

Point::Point (double xPos, double yPos) : xPos(xPos), yPos(yPos) {

}

double Point::getX () const {
    return this->xPos;
}

double Point::getY () const {
    return this->yPos;
}

void Point::setX (double xPos) {
    this->xPos = xPos;
}

void Point::setY (double yPos) {
    this->yPos = yPos;
}

double Point::distance (Point pos) const {
    double xSub = (this->getX() - pos.getX());
    double ySub = (this->getY() - pos.getY());
    double xPow = pow(xSub, 2);
    double yPow = pow(ySub, 2);
    return sqrt(xPow + yPow);
}

Point Point::moveTowards (Point source, Point target, double dis) {
    if (dis <= 0) {
        throw invalid_argument("the distance must be positive");
    }
    double disBetweenThePoints = source.distance(target);
    double dx = target.getX() - source.getX();
    double dy = target.getY() - source.getY();
    double normalDx = dx / disBetweenThePoints;
    double normalDy = dy / disBetweenThePoints;
    double howFarX = normalDx * dis;
    double howFarY = normalDy * dis;
    double xNew = source.getX() + howFarX;
    double yNew = source.getY() + howFarY;
    return Point(xNew, yNew);
}

void Point::print () {
    cout << "(" << this->getX() << ", " << this->getY() << ")" << endl;
}

bool Point::operator== (Point other) {
    if (this->getX() == other.getX() && this->getY() == other.getY()) {
        return true;
    }
    return false;
}

// Point& Point::operator= (const Point other) {
//     this->setX(other.xPos);
//     this->setY(other.yPos);
//     return *this;
// }