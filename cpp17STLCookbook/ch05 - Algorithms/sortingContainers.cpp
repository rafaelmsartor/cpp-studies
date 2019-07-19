
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <random>
#include <numeric>

constexpr int item_count = 10;

static void print( std::vector<int> const& v )
{
    std::copy( std::begin( v ), std::end( v ), std::ostream_iterator<int>{ std::cout, ", " } );
    std::cout << '\n';
}

int main()
{
    std::vector<int> v( item_count );
    std::iota( std::begin( v ), std::end( v ), 1 );

    std::random_device rd;
    std::mt19937 g { rd() };

    print( v );
    std::cout << "Sorted: " << std::is_sorted( std::begin( v ), std::end( v ) ) << '\n';

    std::shuffle( std::begin( v ), std::end( v ), g );
    print( v );
    std::cout << "Sorted: " << std::is_sorted( std::begin( v ), std::end( v ) ) << '\n';

    std::sort( std::begin( v ), std::end( v ) );
    print( v );
    std::cout << "Sorted: " << std::is_sorted( std::begin( v ), std::end( v ) ) << '\n';


    std::cout << "Partition (x < 5):\n";
    std::shuffle( std::begin( v ), std::end( v ), g );
    print( v );
    std::partition( std::begin( v ), std::end( v ), []( int i ){ return i < 5; } );
    print( v );


    std::cout << "Partial sort:\n";
    std::shuffle( std::begin( v ), std::end( v ), g );
    print( v );
    auto middle ( std::next( std::begin( v ), int( v.size() / 2 ) ) );    
    std::partial_sort( std::begin( v ), middle, std::end( v ) );
    print( v );


    struct my_struct
    {
        int a;
        int b;
    };
    std::vector<my_struct> mv 
    {
        {5, 100}, 
        {1, 50}, 
        {-123, 1000},
        {3, 70}, 
        {-10, 20}
    };

    std::sort( std::begin( mv ), std::end( mv ), []( my_struct const& lhs, my_struct const& rhs )
    {
        return lhs.b < rhs.b;
    });

    for( auto const& [a, b] : mv )
    {
        std::cout << "{" << a << ", " << b << "} ";
    }
    std::cout << '\n';
}
