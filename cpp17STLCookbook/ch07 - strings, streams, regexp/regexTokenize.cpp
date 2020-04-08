
#include <iostream>
#include <iterator>
#include <regex>
#include <algorithm>
#include <iomanip>

template <typename I>
void print ( I it, I end_it )
{
    while( it != end_it )
    {
        std::string const link{ *it++ };
        if( it == end_it ) break;
        std::string const desc{ *it++ };

        std::cout << std::left << std::setw( 28 ) << desc << " : " << link << '\n';
    }
}

int main()
{
    std::cin >> std::noskipws;

    std::string const in { std::istream_iterator<char>{ std::cin }, {} };

    std::regex const link_re { "<a href=\"([^\"]*)\"[^<]*>([^<]*)</a>" };

    std::sregex_token_iterator it { std::begin( in ), std::end( in ), link_re, { 1, 2 } };

    print( it, {} );
}