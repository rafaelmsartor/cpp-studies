
#include <iostream>
#include <iomanip>
#include <chrono>

std::ostream& operator<<( std::ostream& os, std::chrono::time_point<std::chrono::system_clock> const& t )
{
    auto const tt( std::chrono::system_clock::to_time_t( t ) );
    auto const loct( std::localtime( &tt ) );
    return os << std::put_time( loct, "%c" );
}

using days = std::chrono::duration<std::chrono::hours::rep, std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>>;

constexpr days operator ""_days( unsigned long long h )
{
    return days{ h };
}

int main()
{
    auto now( std::chrono::system_clock::now() );
    std::cout << "The current date and time is: " << now << '\n';

    std::chrono::hours chrono_12h{ 12 };
    std::cout << "In 12 hours, it will be " << ( now + chrono_12h ) << '\n';

    using namespace std::chrono_literals;
    std::cout << "12 hours and 15 minutes ago, it was " << ( now - 12h - 15min ) << '\n'
              << "1 week ago, it was " << ( now - 7_days ) << '\n';
}