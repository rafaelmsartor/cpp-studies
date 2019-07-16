#include <iostream>
#include <functional>

template <typename T, typename ...Ts>
auto concat( T t, Ts ...ts )
{
    if constexpr ( sizeof...( ts ) > 0 )
    {
        return [=] ( auto ...parameters )
        {
            return t( concat( ts ... )( parameters... ) );
        };
    }
    else
    {
        return t;
    }
    
}

int main()
{
    auto twice ( [] ( int i ) { return 2 * i; } );
    auto trice ( [] ( int i ) { return 3 * i; } );

    auto combined( concat( twice, trice, std::plus<int>{} ) );

    std::cout << combined( 2, 3 ) << '\n';
}