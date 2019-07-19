
#include "power.h"
#include <map>
#include <iostream>

template <typename I>
std::pair<I, I> fibonacci_matrix_multiply( std::pair<I, I> const& x, std::pair<I, I> const& y )
{
    return std::make_pair(
        x.first * ( y.second + y.first ) + x.second * y.first,
        x.first * y.first + x.second * y.second
    );
}

template <typename I>
I fibonacci( I n )
{
    if( n == 0 ) return 0;
    return power( std::make_pair( long(1), long(0) ), n, fibonacci_matrix_multiply<long> ).first;
}


int main()
{
    for( size_t i = 0; i < 50; ++i )
    {
        std::cout << "Fib_" << i << ": " << fibonacci( i ) << '\n';
    }
}
