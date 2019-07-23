#pragma once

#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <optional>

template <typename T>
class trie
{
    std::map<T, trie> tries;

    void print( std::vector<T>& v ) const 
    {
        if( tries.empty() )
        {
            std::copy( std::begin( v ), std::end( v ), std::ostream_iterator<T>{ std::cout, " " } );
            std::cout << '\n';
        }
        for( auto const& p : tries )
        {
            v.push_back( p.first );
            p.second.print( v );
            v.pop_back();
        }
    }

public:
    template <typename I>
    void insert( I it, I end_it )
    {
        if( it == end_it ) return;
        tries[*it].insert( next( it ), end_it );
    }

    template <typename C>
    void insert( C const& container )
    {
        insert( std::begin( container ), std::end( container ) );
    }

    void insert( std::initializer_list<T> const& il )
    {
        insert( std::begin( il ), std::end( il ) );
    } 

    void print() const
    {
        std::vector<T> v;
        print( v );
    }

    template <typename I>
    std::optional<std::reference_wrapper<const trie>>
    subtrie( I it, I end_it ) const
    {
        if( it == end_it ) return std::ref( *this );

        auto found( tries.find( *it ) );
        if( found == std::end( tries ) ) return {};
        return found->second.subtrie( std::next( it ), end_it );
    }

    template <typename C>
    auto subtrie( C const& c )
    {
        return subtrie( std::begin( c ), std::end( c ) );
    }
};
