
#include <iostream>
#include <algorithm>
#include <string>

static constexpr char tolow( char c )
{
    switch( c )
    {
        case 'A'...'Z': return c - 'A' + 'a';
        default: return c;
    }
}

class lc_traits : public std::char_traits<char>
{
public:
    static constexpr void assign( char_type& r, char_type const& a )
    {
        r = tolow( a );
    }

    static char_type* copy( char_type* dest, char_type const* src, size_t count )
    {
        std::transform( src, src + count, dest, tolow );
        return dest;
    }
};

class ci_traits : public std::char_traits<char>
{
public:
    static constexpr bool eq( char_type a, char_type b )
    {
        return tolow( a ) == tolow( b );
    }

    static constexpr bool lt( char_type a, char_type b )
    {
        return tolow( a ) < tolow( b );
    }

    static constexpr int compare( char_type const* s1, char_type const* s2, size_t count )
    {
        for( ; count; ++s1, ++s2, --count )
        {
            char_type const diff( tolow( *s1 ) - tolow( *s2 ) );
            if( diff < 0 )
                return -1;
            else if( diff > 0 )
                return 1;
        }
        return 0;
    }

    static constexpr char_type const* find( char_type const* p, size_t count, char_type const& ch )
    {
        char_type const find_c{ tolow( ch ) };
        for( ; count != 0; --count, ++p )
        {
            if( find_c == tolow( *p ) )
                return p;
        }
        return nullptr;
    }
};

using lc_string = std::basic_string<char, lc_traits>;
using ci_string = std::basic_string<char, ci_traits>;

std::ostream& operator<<( std::ostream& os, lc_string const& str )
{
    return os.write( str.data(), str.size() );
}

std::ostream& operator<<( std::ostream& os, ci_string const& str )
{
    return os.write( str.data(), str.size() );
}

int main()
{
    std::cout << "   string: " << std::string( "Foo Bar Baz" ) << '\n';
    std::cout << "lc_string: " << lc_string( "Foo Bar Baz" ) << '\n';
    std::cout << "ci_string: " << ci_string( "Foo Bar Baz" ) << '\n';

    ci_string user_input {"MaGiC PaSsWoRd!"};
    ci_string password {"magic password!"};

    if (user_input == password) 
    {
        std::cout << "Passwords match: \"" << user_input << "\" == \"" << password << "\"\n";
    }
}
