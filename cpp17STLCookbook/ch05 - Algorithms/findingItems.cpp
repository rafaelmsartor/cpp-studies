
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

struct city
{
    std::string name;
    unsigned population;
};

bool operator==( city const& a, city const& b )
{
    return a.name == b.name && a.population == b.population;
}

std::ostream& operator<<( std::ostream& os, city const& c )
{
    return os << "{" << c.name << ", " << c.population << "}";
}

template<typename C>
static auto opt_print( C const& container )
{
    return [end_it( std::end( container ) )] ( auto const& item )
    {
        if( item != end_it )
        {
            std::cout << *item << '\n';
        }
        else
        {
            std::cout << "<end>\n";
        }
    };
}

int main()
{
    std::vector<city> const c 
    {
        { "Aachen"      ,  246000 },
        { "Berlin"      , 3502000 },
        { "Braunschweig",  251000 },
        { "Cologne"     , 1060000 }
    };

    auto print_city( opt_print( c ) );

    {
        auto found_cologne = std::find_if( std::begin( c ), std::end( c ), []( auto const& item )
        {
            return item.name == "Cologne";
        });
        print_city( found_cologne );
    }

    {
        auto population_more_than = [] (unsigned i )
        {
            return [i] ( city const& item )
            {
                return item.population > i;
            };
        };

        auto found_large( std::find_if( std::begin( c ), std::end( c ), population_more_than( 2000000 ) ) );
        print_city( found_large );
    }

    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto print_int( opt_print( v ) );

    bool contains_7 { std::binary_search( std::begin( v ), std::end( v ), 7 ) };
    std::cout << contains_7 << '\n';

    auto [lower_it, upper_it] ( std::equal_range( std::begin( v ), std::end( v ), 7  ) );
    print_int( lower_it );
    print_int( upper_it );

    print_int( std::lower_bound( std::begin( v ), std::end( v ), 7 ) );
    print_int( std::upper_bound( std::begin( v ), std::end( v ), 7 ) );
}