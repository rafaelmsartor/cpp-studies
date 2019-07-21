#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>

template <typename I>
static void print( I it, size_t chars )
{
    std::copy_n( it, chars, std::ostream_iterator<char>{ std::cout } );
    std::cout << '\n';
}

int main()
{
    std::string const long_string { "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod" };
    std::string const needle { "elitr" };

    {
        auto match (std::search( std::begin( long_string ), std::end( long_string ),
                                 std::begin( needle )     , std::end( needle ) ) );
        print( match, 5 );
    }

    {
        auto match( std::search( std::begin( long_string ), std::end( long_string ),
                                 std::default_searcher( std::begin( needle ), std::end( needle ) ) ) );
        
        print( match, 5 );
    }

    {
        auto match( std::search( std::begin( long_string ), std::end( long_string ),
                                 std::boyer_moore_searcher( std::begin( needle ), std::end( needle ) ) ) );
        print( match, 5 );
    }

    {
        auto match( std::search( std::begin( long_string ), std::end( long_string ),
                                 std::boyer_moore_horspool_searcher( std::begin( needle ), std::end( needle ) ) ) );
        print( match, 5 );
    }
}