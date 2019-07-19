
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <tuple>
#include <iterator>
#include <algorithm>

namespace std
{
    std::ostream& operator<<( std::ostream& os, std::pair<int, std::string> const& p )
    {
        return os << "(" << p.first << ", " << p.second << ")";
    }
}

int main()
{
    std::vector<std::pair<int, std::string>> v 
    {
        { 1, "one" },
        { 2, "two" },
        { 3, "three" },
        { 4, "four" },
        { 5, "five" }
    };
    std::map<int, std::string> m;

    // copy elements from the vector into the map, using inserter to adapt the values
    std::copy_n( std::begin(v), 3, std::inserter( m, std::begin( m )  ) );

    // create an output iterator and use copy to print the map
    auto shell_it (std::ostream_iterator<std::pair<int, std::string>> { std::cout, ", " });
    std::copy( std::begin( m ), std::end( m ), shell_it );
    std::cout << '\n';

    m.clear();
    
    // Now move the elementes from the vector, into the map
    std::move( std::begin( v ), std::end( v ), std::inserter( m, std::begin( m ) ) );
    
    std::cout << "MAP: ";
    std::copy( std::begin( m ), std::end( m ), shell_it );
    std::cout << '\n';

    std::cout << "VECTOR: ";
    std::copy( std::begin( v ), std::end( v ), shell_it );
    std::cout << '\n';
}