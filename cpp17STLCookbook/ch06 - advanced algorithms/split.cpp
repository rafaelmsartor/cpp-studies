#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <list>

template <typename InIt, typename OutIt, typename T, typename F>
InIt split( InIt it, InIt end_it, OutIt out_it, T split_val, F bin_func )
{
    while( it != end_it )
    {
        auto slice_end( std::find( it, end_it, split_val ) );
        *out_it++ = bin_func( it, slice_end );

        if( slice_end == end_it )
            return end_it;

        it = std::next( slice_end );
    }
    return it;
}

int main()
{
    std::string const s { "a-b-c-d-e-f-g" };

    auto binfunc( [] ( auto it_a, auto it_b )
    {
        return std::string( it_a, it_b );
    } );

    std::list<std::string> l;
    split( std::begin( s ), std::end( s ), std::back_inserter( l ), '-', binfunc );
    std::copy( std::begin( l ), std::end( l ), std::ostream_iterator<std::string>( std::cout, "\n" ) );
}
