#include <iostream>
#include <set>
#include <string>
#include <iterator>

// use a set to filter and order a list of words input by the user.

int main()
{
    std::set<std::string> s;

    std::istream_iterator<std::string> it { std::cin };
    std::istream_iterator<std::string> end;

    std::copy( it, end, std::inserter( s, s.end() ) );

    for( auto const& word : s )
        std::cout << word << ", ";
    std::cout << '\n';

    return 0;
}