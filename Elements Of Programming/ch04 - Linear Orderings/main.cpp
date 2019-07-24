
#include "select_4.h"
#include "select_5.h"

#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>

template <typename T>
std::ostream& operator<<( std::ostream& os, std::vector<T> const& v )
{
    for( auto val : v ) os << val << ' ';
    return os;
}


void test_select_2_4()
{
    std::vector<int> v( 4 );
    std::iota( std::begin( v ), std::end( v ), 1 );

    int const val_2 = v[2];

    do
    {
        int a = v[0];
        int b = v[1];
        int c = v[2];
        int d = v[3];

        std::cout << v << ": " << (select_2_4( a, b, c, d, std::less<int>() ) == val_2) << '\n';
    } while ( std::next_permutation( std::begin( v ), std::end( v ) ) );
}

int main()
{
    std::cout << select_2_5<1, 2, 3, 4, 5>( 1, 2, 4, 5, 3, std::less<int>() ) << '\n';
}