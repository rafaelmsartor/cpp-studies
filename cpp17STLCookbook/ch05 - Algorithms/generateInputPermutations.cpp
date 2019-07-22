
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

int main()
{
    std::vector<std::string> v { std::istream_iterator<std::string>{ std::cin }, {} };
    // container must be sorted in order to find all the permutations
    std::sort( std::begin( v ), std::end( v ) );

    do
    {
        std::copy( std::begin( v ), std::end( v ), std::ostream_iterator<std::string>{ std::cout, ", " } );
        std::cout << '\n';
    } while ( std::next_permutation( std::begin( v ), std::end( v ) ) );
}