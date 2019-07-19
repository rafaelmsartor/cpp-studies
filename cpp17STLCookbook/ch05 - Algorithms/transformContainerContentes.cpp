
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<int> v { 1, 2, 3, 4, 5 };
    std::transform( std::begin( v ), std::end( v ), std::ostream_iterator<int>{ std::cout, ", " }, []( int i ){ return i * i; } );
    std::cout << '\n';


    auto int_to_string( []( int i )
    {
        std::stringstream ss;
        ss << i << "^2 = " << i * i;
        return ss.str();
    });

    std::vector<std::string> vs;
    std::transform( std::begin( v ), std::end( v ), std::back_inserter( vs ), int_to_string );
    std::copy( std::begin( vs ), std::end( vs ), std::ostream_iterator<std::string>{ std::cout, "\n" } );
}