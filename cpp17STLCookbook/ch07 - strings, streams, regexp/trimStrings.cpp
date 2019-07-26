
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

std::string trim_whitespace( std::string const& s )
{
    char const whitespace[] { " \t\n" };
    size_t const first( s.find_first_not_of( whitespace ) );
    if( std::string::npos == first ) return {};

    size_t const last( s.find_last_not_of( whitespace ) );
    return s.substr( first, (last - first + 1) );
}

int main()
{
    std::string s { " \t\n string surrounded by ugly whitespace \t\n " };

    std::cout << '{' << s << "}\n";
    std::cout << '{' << trim_whitespace( s ) << "}\n";
}