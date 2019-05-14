#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

enum class PointType
{
    Cartesian,
    Polar
};

class Point 
{
    Point( double const x, double const y )
        : x( x )
        , y( y )
    {}

public:
    double x, y;

    friend std::ostream& operator<<( std::ostream& os, Point const& obj )
    {
        return os << "x: " << obj.x << " y: " << obj.y;
    }

    static Point NewCartesian( double x, double y )
    {
        return { x, y };
    }

    static Point NewPolar( double r, double theta )
    {
        return { r * cos(theta), r * sin(theta) };
    }
};

int main()
{
    auto p = Point::NewPolar( 5, M_PI_4 );
    std::cout << p << std::endl;

    return 0;
}