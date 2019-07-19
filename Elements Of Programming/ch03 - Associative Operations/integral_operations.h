#pragma once

namespace int_op
{
    template <typename T>
    inline
    T successor( T x )
    {
        return x + 1;
    }

    template <typename T>
    inline
    T predecessor( T x )
    {
        return x - 1;
    }

    template <typename T>
    inline
    T twice( T x )
    {
        return x * 2;
    }

    template <typename T>
    inline
    T half_nonnegative( T x )
    {
        return x / 2;
    }

    template <typename T>
    inline
    T binary_scale_down_nonnegative( T x, T const& k )
    {
         return x >> k;
    }

    template <typename T>
    inline
    T binary_scale_up_nonnegative( T x, T const& k )
    {
        return x << k;
    }

    template <typename T>
    inline
    bool positive( T x )
    {
        return x > 0;
    }

    template <typename T>
    inline
    bool negative( T x )
    {
        return x < 0;
    }

    template <typename T>
    inline
    bool zero( T x )
    {
        return x == 0;
    }

    template <typename T>
    inline
    bool one( T x )
    {
        return x == 1;
    }

    template <typename T>
    inline
    bool even( T x )
    {
        return x % 2 == 0;
    }

    template <typename T>
    inline
    bool odd( T x )
    {
        return x % 2 != 0;
    }
}