
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>

int main()
{
    size_t const sig_len{ 100 };
    std::vector<double> as( sig_len );
    std::vector<int> ds( sig_len );

    auto sin_gen( [n{0}]() mutable
    {
        return 5.0 * std::sin( n++ * 2.0 * M_PI / 100 );
    });

    std::generate( std::begin( as ), std::end( as ), sin_gen );
    std::copy( std::begin( as ), std::end( as ), std::begin( ds ) );

    std::copy( std::begin( as ), std::end( as ), std::ostream_iterator<double>{ std::cout, " " } );
    std::cout << '\n';
    std::copy( std::begin( as ), std::end( as ), std::ostream_iterator<double>{ std::cout, " " } );
    std::cout << '\n';

    std::cout << std::inner_product( std::begin( as ), std::end( as ), std::begin( ds ), 0.0, std::plus<double>(), 
            []( double a, double b )
            {
                return std::pow( a - b, 2 );
            } ) << '\n';
}