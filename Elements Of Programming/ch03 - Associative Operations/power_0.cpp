
#include <iostream>
#include <functional>

template <typename T, typename Op>
// requires 
T power_0( T a, int n, Op op )
{
    // Pre condition: associative( op ) ^ n > 0
    if( n == 1 ) return a;
    if( n % 2 == 0 ) 
        return power_0( op( a, a ), n / 2, op );
    return op( power_0( op( a, a ), n / 2, op ), a );
}

int main()
{
    // if op is + the result of power is a multiplication
    std::cout << power_0( 2, 3, std::plus<int>{} ) << '\n';

    // if op is * the result of power is power
    std::cout << power_0( 2, 3, std::multiplies<int>{} ) << '\n';
}
