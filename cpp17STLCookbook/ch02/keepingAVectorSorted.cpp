
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>

template <typename T>
std::ostream& operator<<( std::ostream& os, std::vector<T> const& vec )
{
    for( auto const& value : vec ) os << value << ' ';
    return os;
}

template <typename T>
void insert_sorted( std::vector<T>& v, T value )
{
    std::assert( std::is_sorted( v ) );
    // if the collection is sorted, lower_bound will return an iterator to the first element
    //    that is not less than the value passsed
    auto const insert_pos = std::lower_bound( std::begin(v), std::end(v), value );
    v.insert( insert_pos, value );
}

int main()
{
    std::vector<std::string> v { "some", "random", "words", "without", "order", "aaa", "yyy" };

    std::sort( std::begin(v), std::end(v) );

    std::cout << v << '\n';

    insert_sorted( v, std::string("foobar") );
    std::cout << v << '\n';
    insert_sorted( v, std::string("zzz") );
    std::cout << v << '\n';
    
    return 0;
}
