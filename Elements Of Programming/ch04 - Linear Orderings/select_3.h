#pragma once

#include "select_2.h"

template <typename T, typename R>
// requires: Relation( R )
T const& select_0_3( T const& a, T const& b, T const& c, R r )
{
    return select_0_2( select_0_2( a, b, r ), c, r );
}

template <typename T, typename R>
// requires: Relation( R )
T const& select_2_3( T const& a, T const& b, T const& c, R r )
{
    return select_1_2( select_1_2( a, b, r ), c, r );
}

template <typename T, typename R>
// requires: Relation( R )
T const& select_1_3_ab( T const& a, T const& b, T const& c, R r )
{
    if( !r( c, b ) ) return b;
    return select_1_2( a, c, r );
}

template <typename T, typename R>
// requires: Relation( R )
T const& select_1_3( T const& a, T const& b, T const& c, R r )
{
    if( r( b, a ) ) return select_1_3_ab( b, a, c, r );
    return select_1_3_ab( a, b, c, r );
}
