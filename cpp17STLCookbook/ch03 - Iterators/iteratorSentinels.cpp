
#include <iostream>

class c_string_iterator_sentinel {};

class c_string_iterator
{
    char const* s { nullptr };

public:
    explicit c_string_iterator( char const* str )
        : s{ str }
    {}

    char operator*() const { return *s; }

    c_string_iterator& operator++()
    {
        ++s;
        return *this;
    }

    bool operator!=( c_string_iterator_sentinel const ) const
    {
        return s != nullptr && *s != '\0';
    }
};

class c_string_range
{
    char const* s { nullptr };

public:
    c_string_range( char const* str )
        : s{ str }
    {}

    c_string_iterator begin() const
    {
        return c_string_iterator{ s };
    }

    c_string_iterator_sentinel end() const
    {
        return {};
    }
};

int main( int argc, char* argv[] )
{
    if( argc < 2 )
    {
        std::cout << "Please provide one parameter.\n";
        return 1;
    }

    for( char c : c_string_range( argv[1] ) )
    {
        std::cout << c;
    }
    std:: cout << std::endl;

    return 0;
}
