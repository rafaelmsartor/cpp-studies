
#include <iostream>
#include <chrono>
#include <ratio>
#include <cmath>
#include <iomanip>
#include <optional>

using      seconds = std::chrono::duration<double>;
using milliseconds = std::chrono::duration<double, std::ratio_multiply<seconds::period, std::milli>>;
using microseconds = std::chrono::duration<double, std::ratio_multiply<seconds::period, std::micro>>;

static std::pair<std::string, seconds> get_input()
{
    std::string s;
    // clock possibilities:
    //  * system_clock: system-wide real-time clock. Used to obtain local time
    //  * steady_clock: monotonic
    //  * high_resolution_clock: most fine grained clock tick possible
    auto const tick( std::chrono::steady_clock::now() );

    if( !( std::cin >> s ) )
    {
        return { {}, {} };
    }
    
    auto const tock( std::chrono::steady_clock::now() );
    return { s, tock - tick };
}

int main()
{
    while( true )
    {
        std::cout << "Please type the word \"C++17\" as fast as you can.\n> ";
        auto const [user_input, diff] = get_input();
        
        if( user_input.empty() ) break;

        if( user_input == "C++17" )
        {
            std::cout << "Bravo. You did it in:\n" << std::fixed << std::setprecision( 2 ) << std::setw( 12 )
                                                   << diff.count() << " seconds.\n"
                                                   << std::setw( 12 )
                                                   << milliseconds( diff ).count() << " milliseconds.\n"
                                                   << std::setw( 12 )
                                                   << microseconds( diff ).count() << " microseconds.\n";
        }
        else
        {
            std::cout << "Sorry, your input does not match. You may try again.\n";
        }
    }
}