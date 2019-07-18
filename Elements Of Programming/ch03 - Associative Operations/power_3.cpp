#include <iostream>
#include <functional>

template<typename T, typename Op>
T power_accumulate_positive_0( T r, T a, int n, Op op )
{
    while( true )
    {
        if( n % 2 != 0 )
        {
            r = op( r, a );
            if( n == 1 ) return r;
        }
        
        a = op( a, a );
        n = n / 2;
    }
}


template<typename T, typename Op>
T power_3( T a, int n, Op op )
{
    while( n % 2 == 0 )
    {
        a = op( a, a );
        n = n / 2;
    }
    n = n / 2;
    if( n == 0 ) return a;
    return power_accumulate_positive_0( a, op( a, a ), n, op );
}

int main()
{
    // if op is + the result of power is a multiplication
    std::cout << power_3( 2, 3, std::plus<int>{} ) << '\n';

    // if op is * the result of power is power
    std::cout << power_3( 2, 3, std::multiplies<int>{} ) << '\n';
}
