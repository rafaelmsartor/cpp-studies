#pragma once


#include "integral_operations.h"
#include "power.h"

template <typename T, typename I, typename Op>
// requires: Integer( I ) && BinaryOperation( Op )
T power_accumulate_positive( T r, T a, I n, Op op )
{
    while( true )
    {
        if( int_op::odd( n ) )
        {
            r = op( r, a );
            if( int_op::one( n ) ) return r;
        }
        a = op( a, a );
        n = int_op::half_nonnegative( n );
    }
}

template <typename T, typename I, typename Op>
// requires: Integer( I ) && BinaryOperation( Op )
T power_accumulate( T r, T a, I n, Op op )
{
    if( int_op::zero( n ) ) return r;
    return power_accumulate_positive( r, a, n , op );
}

template <typename T, typename I, typename Op>
// requires: Integer( I ) && BinaryOperation( Op )
T power( T a, I n, Op op )
{
    while( int_op::even( n ) )
    {
        a = op( a, a );
        n = int_op::half_nonnegative( n );
    }

    n = int_op::half_nonnegative( n );
    if( int_op::zero( n ) ) return a;
    return power_accumulate_positive( a, op( a, a ), n, op );
}

template< typename T, typename I, typename Op>
// requires: Integer( I ) && BinaryOperation( Op )
T power( T a, I n, Op op, T id )
{
    if( int_op::zero( n ) ) return id;
    return power( a, n, op );
}

