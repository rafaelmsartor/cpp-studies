
#include <iostream>
#include <deque>
#include <list>
#include <vector>
#include <functional>

static auto consumer ( auto& container )
{
    return [&] ( auto value )
    {
        container.push_back( value );
    };
}

void print( auto const& container )
{
    for( auto const& val : container )
        std::cout << val << ", ";
    std::cout << '\n';
}

int main()
{
    std::deque<int> d;
    std::list<int> l;
    std::vector<int> v;

    const std::vector<std::function<void(int)>> consumers
    {
        consumer( d ),
        consumer( l ),
        consumer( v )
    };

    for( size_t i {0}; i < 10; ++i )
    {
        for( auto&& consume : consumers )
            consume( i );
    }

    print( d );
    print( l );
    print( v );
}
