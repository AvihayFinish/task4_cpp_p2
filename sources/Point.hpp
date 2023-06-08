#pragma once

namespace ariel {

    class Point
    {
    private:
        double xPos;
        double yPos;
    public:
        Point (double xPos, double yPos);
        double getX () const;
        double getY () const;
        void setX (double xPos);
        void setY (double yPos);
        double distance (Point pos) const;
        void print ();
        bool operator== (Point other);
        // Point& operator= (const Point other);
        static Point moveTowards (Point source, Point target, double dis);
    }; 
}