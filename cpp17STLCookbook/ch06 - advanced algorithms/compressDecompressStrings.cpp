
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <tuple>


template <typename It>
std::tuple<It, char, size_t> occurrences( It it, It end_it )
{
    if( it == end_it ) return { it, '?', 0 };
    char const c { *it };
    auto const diff( std::find_if( it, end_it, [c]( char x ) 
    { 
        return c != x; 
    } ) );

    return { diff, c, std::distance( it, diff ) };
}

std::string compress( std::string const& s )
{
    auto const end_it( std::end( s ) );
    std::stringstream r ;

    for( auto it( std::begin( s ) ); it != end_it; )
    {
        auto const [next_diff, c, n]( occurrences( it, end_it ) );
        r << c << n;
        it = next_diff;
    }
    return r.str();
}

std::string decompress( std::string const& s )
{
    std::stringstream ss{ s };
    std::stringstream r;
    char c;
    size_t n;

    while ( ss >> c >> n ) r << std::string( n, c );
    return r.str();
}

int main()
{
    std::string s { "aaaaaaaaabbbbbbbbbccccccccccc" };
    std::cout << compress( s ) << '\n';
    std::cout << decompress( compress( s ) ) << '\n';    
}
