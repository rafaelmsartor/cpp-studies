
#include <iostream>
#include <map>

// Prior to C++17, we had to remove the items of which we need to change the key value from
// the tree, in order to reinsert them. The downside of this approach is that this always
// needlessly reallocates some memory, which sounds bad in terms of performance.
// Since C++17, we can remove and reinsert map nodes without any reallocation of memory.
// We will see how that works in this recipe.

template <typename M>
void print( M const& m )
{
    std::cout << "Race placement:\n";
    for( auto const& [placement, driver] : m )
    {
        std::cout << placement << ": " << driver << '\n';
    }
}

int main()
{
    std::map<int, std::string> race_placement
    {
        {1, "Mario"}, {2, "Luigi"}, {3, "Bowser"},
        {4, "Peach"}, {5, "Yoshi"}, {6, "Koopa"},
        {7, "Toad"}, {8, "Donkey Kong Jr."}
    };

    print( race_placement );

    {
        auto a ( race_placement.extract( 3 ) );
        auto b ( race_placement.extract( 8 ) );

        std::swap( a.key(), b.key() );

        race_placement.insert( std::move( a ) );
        race_placement.insert( std::move( b ) );
    }

    print( race_placement );

    return 0;
}
