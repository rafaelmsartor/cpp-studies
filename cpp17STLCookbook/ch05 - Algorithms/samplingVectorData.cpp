
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <map>
#include <iomanip>

int main()
{
    size_t const data_points { 100000 };
    size_t const sample_points { 1000 };

    int const mean { 10 };
    size_t const dev { 3 };

    std::random_device rd;
    std::mt19937 gen { rd() };
    std::normal_distribution<> d { mean, dev };

    std::vector<int> v;
    v.reserve( data_points );

    std::generate_n( std::back_inserter( v ), data_points, [&] { return d( gen ); } );

    std::vector<int> samples;
    v.reserve( sample_points );

    std::sample( std::begin( v ), std::end( v ), std::back_inserter( samples ),
                 sample_points, std::mt19937{ std::random_device{}() } );

    std::map<int, size_t> hist;
    for( int i : samples ) { ++hist[i]; }

    for( auto const& [value, count] : hist )
    {
        std::cout << std::setw(2) << value << " " << std::string( count, '*' ) << '\n';
    }
}