
#include <iostream>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <algorithm>

using namespace std;

std::string word_num( int i )
{
    static std::unordered_map<int, std::string> const m
    {
        { 1, "one"   },
        { 2, "two"   },
        { 3, "three" },
        { 4, "four"  },
        { 5, "five"  },
        { 6, "six"   },
        { 7, "seven" },
        { 8, "eight" },
        { 9, "nine"  }
    };

    auto const match( m.find( i ) );
    if( match == std::end( m ) )
        return "unknown";
    return match->second;
}

struct bork
{
    int borks;
    bork( int i )
        : borks{ i }
    {}

    void print( std::ostream& os ) const 
    {
        std::fill_n( std::ostream_iterator<std::string>{ os }, borks, "bork!"s );
    }
};

std::ostream& operator<<( std::ostream& os, bork const& b )
{
    b.print( os );
    return os;
}

int main()
{
    std::vector<int> const v { 1, 2 ,3 ,4 ,5 };

    std::ostream_iterator<int> oit{ std::cout };
    std::copy( std::begin( v ), std::end( v ), oit );
    std::cout << '\n';

    std::ostream_iterator<int> oit_comma{ std::cout , ", " };
    std::copy( std::begin( v ), std::end( v ), oit_comma );
    std::cout << '\n';

    std::ostream_iterator<std::string> oit_space{ std::cout, " " };
    std::transform( std::begin( v ), std::end( v ), oit_space, word_num );
    std::cout << '\n';

    std::copy( std::begin( v ), std::end( v ), std::ostream_iterator<bork>{ std::cout, "\n" } );
}
