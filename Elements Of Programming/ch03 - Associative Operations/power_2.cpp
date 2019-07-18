#include <iostream>
#include <functional>


// transform power_1 in a tail recursive call
template <typename T, typename Op>
T power_accumulate_0( T r, T a, int n, Op op )
{
    if( n == 0 ) return r;
    if( n % 2 != 0 ) r = op( r, a );
    return power_accumulate_0( r, op( a, a ), n / 2, op );
}

// eliminate unecessary squaring when n goes from 0 to 1

template <typename T, typename Op>
T power_accumulate_1( T r, T a, int n, Op op )
{
    if( n == 0 ) return r;
    if( n == 1 ) return op( r, a );
    if( n % 2 != 0 ) r = op( r, a );
    return power_accumulate_1( r, op( a, a ), n / 2, op );
}

// eliminate introduced redundant call

template<typename T, typename Op>
T power_accumulate_2( T r, T a, int n, Op op )
{
    if( n % 2 != 0 )
    {
        r = op( r, a );
        if( n == 1 ) 
            return r;
    }
    else if ( n == 0 ) 
        return r;
    
    return power_accumulate_2( r, op( a, a ), n / 2, op );
}

// make it strict tail recursive

template<typename T, typename Op>
T power_accumulate_3( T r, T a, int n, Op op )
{
    if( n % 2 != 0 )
    {
        r = op( r, a );
        if( n == 1 )
            return r;
    }
    else if( n == 0 )
        return r;
    
    a = op( a, a );
    n = n / 2;
    return power_accumulate_3( r, a, n, op );
}

// transform it into an iterative procedure

template<typename T, typename Op>
T power_accumulate_4( T r, T a, int n, Op op )
{
    while( true )
    {
        if( n % 2 != 0 )
        {
            r = op( r, a );
            if( n == 1 ) return r;
        }
        else if( n == 0 ) return r;

        a = op( a, a );
        n = n / 2;
    }
}

// change pre condition no n > 0

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
T power_accumulate_5( T r, T a, int n, Op op )
{
    if( n == 0 ) return r;
    return power_accumulate_positive_0( r, a, n, op );
}

// and finally power_2

template<typename T, typename Op>
T power_2( T a, int n, Op op )
{
    return power_accumulate_5( a, a, n -1, op );
}


int main()
{
    // if op is + the result of power is a multiplication
    std::cout << power_2( 2, 3, std::plus<int>{} ) << '\n';

    // if op is * the result of power is power
    std::cout << power_2( 2, 3, std::multiplies<int>{} ) << '\n';
}
