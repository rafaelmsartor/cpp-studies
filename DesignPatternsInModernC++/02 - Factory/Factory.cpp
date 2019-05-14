
#include <cmath>
#include <iostream>

class Point
{
    Point( double x, double y )
        : x( x )
        , y( y )
    {}

public:
    double x, y;

    friend class PointFactory;
};

class PointFactory
{
    static Point NewCartesian( double x, double y )
    {
        return Point{ x, y };
    }

    static Point NewPolar( double r, double theta )
    {
        return Point{ r * cos(theta), r * sin(theta) };
    }
};
