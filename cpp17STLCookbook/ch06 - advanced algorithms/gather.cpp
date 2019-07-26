
#include <iostream>
#include <algorithm>
#include <string>
#include <functional>

template <typename It, typename F>
std::pair<It, It> gather( It first, It last, It gather_pos, F predicate )
{
    return { std::stable_partition( first, gather_pos, std::not_fn( predicate ) ),
             std::stable_partition( gather_pos, last, predicate ) 
           };
    // stable_partition returns the iterator pointing to the first element of the second group
    //  since the predicate is negated on the first call the partition will put the elements that
    //  interests us on the last positions, closer to the gather point. 
}

template <typename It, typename F>
void gather_sort( It first, It last, It gather_pos, F comp_func )
{
    auto inv_comp_func( [&]( auto const& ...ps )
    {
        return !comp_func( ps... );
    } );

    std::stable_sort( first, gather_pos, inv_comp_func );
    std::stable_sort( gather_pos, last, comp_func );
}

int main()
{
    auto is_a( [] ( char c ){ return c == 'a'; } );
    std::string a { "a_a_a_a_a_a_a_a_a_a_a_a_a" };

    auto middle( std::begin( a ) + a.size() / 2 );
    gather( std::begin( a ), std::end( a ), middle, is_a );
    std::cout << a << '\n';

    gather( std::begin( a ), std::end( a ), std::begin( a ), is_a );
    std::cout << a << '\n';

    gather( std::begin( a ), std::end( a ), std::end( a ), is_a );
    std::cout << a << '\n';

    gather( std::begin( a ), std::end( a ), middle, is_a );
    std::cout << a << '\n';


    std::string b { "_9_2_4_7_3_8_1_6_5_0_" };
    gather_sort( std::begin( b ), std::end( b ), std::begin( b ) + b.size() / 2, std::less<char>{} );
    std::cout << b << '\n';
}
