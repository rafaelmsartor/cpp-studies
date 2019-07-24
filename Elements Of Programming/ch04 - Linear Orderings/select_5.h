#pragma once

template <bool strict, typename R>
struct compare_strict_or_reflexive;

template <typename R>
struct compare_strict_or_reflexive<true, R>
{
    template <typename T>
    bool operator()( T const& a, T const& b, R r )
    {
        return r( a, b );
    }
};

template <typename R>
struct compare_strict_or_reflexive<false, R>
{
    template <typename T>
    bool operator()( T const& a, T const& b, R r )
    {
        return !r( b, a );
    }
};

template <int ia, int ib, typename T, typename R>
T const& select_0_2( T const& a, T const& b, R r )
{
    compare_strict_or_reflexive<( ia < ib ), R> cmp;
    if( cmp( b, a, r ) ) return b;
    return a;
}


template <int ia, int ib, int ic, int id, typename T, typename R>
T const& select_1_4_ab_cd( T const& a, T const& b, T const& c, T const& d, R r )
{
    compare_strict_or_reflexive<(ia < ic), R> cmp;
    if( cmp( c, a, r ) ) return select_0_2<ia, id>( a, d, r );
    return select_0_2<ib, ic>( b, c, r );
}

template <int ia, int ib, int ic, int id, typename T, typename R>
T const& select_1_4_ab( T const& a, T const& b, T const& c, T const& d, R r )
{
    compare_strict_or_reflexive<(ic < id), R> cmp;
    if( cmp( d, c, r ) ) return select_1_4_ab_cd<ia, ib, id, ic>( a, b, d, c, r );
    return select_1_4_ab_cd<ia, ib, ic, id>( a, b, c, d, r );
}

template <int ia, int ib, int ic, int id, typename T, typename R>
T const& select_1_4( T const& a, T const& b, T const& c, T const& d, R r )
{
    compare_strict_or_reflexive<(ia < ib), R> cmp;
    if( cmp( b, a, r ) ) return select_1_4_ab<ib, ia, ic, id>( b, a, c, d, r );
    return select_1_4_ab<ia, ib, ic, id>( a, b, c, d, r );
}


template <int ia, int ib, int ic, int id, int ie, typename T, typename R>
T const& select_2_5_ab_cd( T const& a, T const& b, T const& c, T const& d, T const& e, R r )
{
    compare_strict_or_reflexive<(ia < ic), R> cmp;
    if( cmp( c, a, r ) ) return select_1_4_ab<ia, ib, id, ie>( a, b, d, e, r );
    return select_1_4_ab<ic, id, ib, ie>( c, d, b, e, r );
}

template <int ia, int ib, int ic, int id, int ie, typename T, typename R>
T const& select_2_5_ab( T const& a, T const& b, T const& c, T const& d, T const& e, R r )
{
    compare_strict_or_reflexive<(ic < id), R> cmp;
    if( cmp( d, c, r ) ) return select_2_5_ab_cd<ia, ib, id, ic, ie>( a, b, d, c, e, r );
    return select_2_5_ab_cd<ia, ib, ic, id, ie>( a, b, c, d, e, r );
}

template <int ia, int ib, int ic, int id, int ie, typename T, typename R>
T const& select_2_5( T const& a, T const& b, T const& c, T const& d, T const& e, R r )
{
    compare_strict_or_reflexive<(ia < ib), R> cmp;
    if( cmp( b, a, r ) ) return select_2_5_ab<ib, ia, ic, id, ie>( b, a, c, d, e, r );
    return select_2_5_ab<ia, ib, ic, id, ie>( a, b, c, d, e, r );
}
