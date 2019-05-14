
#include <cmath>
#include <iostream>

class Point
{
    Point( double x, double y )
        : x( x )
        , y( y )
    {}

    class PointFactory
    {
    public:
        static Point NewCartesian( double x, double y )
        {
            return Point{ x, y };
        }

        static Point NewPolar( double r, double theta )
        {
            return Point{ r * cos(theta), r * sin(theta) };
        }
    };
public:
    double x, y;

    static PointFactory Factory;

    friend std::ostream& operator<<( std::ostream& os, Point const& obj )
    {
        return os << "x: " << obj.x << " y: " << obj.y;
    }
};

int main()
{
    auto p = Point::Factory.NewPolar( 5, M_PI_4 );
    std::cout << p << std::endl;
    return 0;
}

