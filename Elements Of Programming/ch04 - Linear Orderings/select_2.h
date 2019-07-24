#pragma once

template <typename T, typename R>
// requires: Relation( R )
T const& select_0_2( T const& a, T const& b, R r ) // stable min
{
    if( r( b, a ) ) return b;
    return a;
}

template <typename T, typename R>
// requires: Relation( R )
T const& select_1_2( T const& a, T const& b, R r ) // stable max
{
    if( r( b, a ) ) return a;
    return b;
}
