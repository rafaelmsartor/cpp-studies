
#include <iostream>
#include <functional>

// reduce power_0 code size by eliminating the redundant recursive call


template <typename T, typename Op>
// requires
T power_1( T a, int n, Op op )
{
    // Pre-condition: associative( op ) ^ n > 0
    if( n == 1 ) return a;
    T r = power_1( op( a, a ), n / 2, op );
    
    if( n % 2 != 0 )
        r = op( r, a );
    return r;
}

int main()
{
    // if op is + the result of power is a multiplication
    std::cout << power_1( 2, 3, std::plus<int>{} ) << '\n';

    // if op is * the result of power is power
    std::cout << power_1( 2, 3, std::multiplies<int>{} ) << '\n';
}
