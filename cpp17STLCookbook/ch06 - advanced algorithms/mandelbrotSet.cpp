#include <iostream>
#include <algorithm>
#include <iterator>
#include <complex>
#include <numeric>
#include <vector>

using cmplx = std::complex<double>;

static auto scaler( int min_from, int max_from, double min_to, double max_to )
{
    int    const w_from   { max_from - min_from };
    double const w_to     { max_to - min_to };
    int    const mid_from { w_from / 2 + min_from };
    double const mid_to   { w_to / 2.0 + min_to };

    return [=]( int from )
    {
        return double( from - mid_from ) / w_from * w_to + mid_to;
    };
}

template <typename A, typename B>
static auto scaled_cmplx( A scaler_x, B scaler_y )
{
    return [scaler_x, scaler_y] ( int x, int y )
    {
        return cmplx{ scaler_x( x ), scaler_y( y ) };
    }; 
}

static size_t mandelbrot_iterations( cmplx c )
{
    cmplx z {};
    size_t iterations { 0 };
    size_t const max_iterations { 1000 };

    while( std::abs( z ) < 2 && iterations < max_iterations )
    {
        ++iterations;
        z = std::pow( z, 2 ) + c;
    }
    return iterations;
}

int main( )
{
    size_t const w { 150 };
    size_t const h { 60 };

    auto scale( scaled_cmplx(
        scaler( 0, w, -2.0, 1.0 ),
        scaler( 0, h, -1.0, 1.0 )
    ) );

    auto i_to_xy( [w, scale]( int i ) { return scale( i % w, i / w ); } );

    auto to_iteration_count( [i_to_xy]( int i ) 
    {
        return mandelbrot_iterations( i_to_xy( i ) );
    });

    std::vector<int> v ( w * h );
    std::iota( std::begin( v ), std::end( v ), 0 );
    std::transform( std::begin( v ), std::end( v ), std::begin( v ), to_iteration_count );

    auto binfunc( [w, n{0}] (auto output_it, int x ) mutable 
    {
        *++output_it = ( x > 50 ? '*' : ' ' );
        if( ++n % w == 0 ) ++output_it = '\n';
        return output_it;
    } );

    std::accumulate( std::begin( v ), std::end( v ), std::ostream_iterator<char>{ std::cout }, binfunc );
}