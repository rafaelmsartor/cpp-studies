
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

void print( std::vector<int> const& v )
{
    std:copy( std::begin( v ), std::end( v ), std::ostream_iterator<int>{ std::cout, ", " } );
    std::cout << '\n';
}

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
    print( v );

    {
        auto const new_end ( std::remove( std::begin( v ), std::end( v ), 2 ) );
        v.erase( new_end, std::end( v ) );
    }
    print( v );

    auto odd_number( []( int i ) { return i % 2 != 0; } );
    auto even_number( []( int i ) { return i % 2 == 0; } );
    {
        auto const new_end( std::remove_if( std::begin( v ), std::end( v ), odd_number ) );
        v.erase( new_end, std::end( v ) );
    }
    print( v );

    std::replace( std::begin( v ), std::end( v ), 4, 123 );
    print( v );

    v.resize( 10 );
    std::iota( std::begin( v ), std::end( v ), 1 );
    std::vector<int> v2, v3;

    // remove_copy_if copies to the out_iterator everything that does not match the predicate, leaves the source unchanged
    std::remove_copy_if( std::begin( v ), std::end( v ), std::back_inserter( v2 ), odd_number );
    std::copy_if( std::begin( v ), std::end( v ), std::back_inserter( v3 ), even_number );
    print( v2 );
    print( v3 );
}