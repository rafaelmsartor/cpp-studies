#pragma once

#include "select_3.h"


// select_1_4

template <typename T, typename R>
// requires: Relation( R )
T const& select_1_4_ab_cd( T const& a, T const& b, T const& c, T const& d, R r )
{
    if( r( c, a ) ) return select_0_2( a, d, r );
    return select_0_2( b, c, r );
}

template <typename T, typename R>
T const& select_1_4_ab( T const& a, T const& b, T const& c, T const& d, R r )
{
    if( r( d, c ) ) return select_1_4_ab_cd( a, b, d, c, r );
    return select_1_4_ab_cd( a, b, c, d, r );
}

template <typename T, typename R>
T const& select_1_4( T const& a, T const& b, T const& c, T const& d, R r )
{
    if( r( b, a ) ) return select_1_4_ab( b, a, c, d, r );
    return select_1_4_ab( a, b, c, d, r );
}


// select_2_4

template <typename T, typename R>
// requires: Relation( R )
T const& select_2_4_ab_cd( T const& a, T const& b, T const& c, T const& d, R r )
{
    if( r( d, b ) ) return select_1_2( a, d, r );
    return select_1_2( b, c, r );
}

template <typename T, typename R>
T const& select_2_4_ab( T const& a, T const& b, T const& c, T const& d, R r )
{
    if( r( d, c ) ) return select_2_4_ab_cd( a, b, d, c, r );
    return select_2_4_ab_cd( a, b, c, d, r );
}

template <typename T, typename R>
T const& select_2_4( T const& a, T const& b, T const& c, T const& d, R r )
{
    if( r( b, a ) ) return select_2_4_ab( b, a, c, d, r );
    return select_2_4_ab( a, b, c, d, r );
}

