
#include <iostream>
#include <string>
#include <algorithm>

template <typename It>
It remove_multi_whitespace( It it, It it_end )
{
    return std::unique( it, it_end, []( auto const& a, auto const& b )
    {
        return std::isspace( a ) && std::isspace( b );
    } );
}

int main( )
{
    std::string s { "fooooo           bar        \t           baz" };
    std::cout << s << '\n';

    s.erase( remove_multi_whitespace( std::begin( s ), std::end ( s ) ), std::end( s ) );
    std::cout << s << '\n';
}