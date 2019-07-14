
#include <iostream>

class fibit
{
    size_t i {0};
    size_t a {0};
    size_t b {1};

    explicit fibit( size_t i_ )
        : i {i_}
    {}

    friend class fib_range;
public:
    fibit() = default;

    size_t operator*() const { return b; }
    
    fibit& operator++()
    {
        size_t const old_b {b};
        b += a;
        a = old_b;
        ++i;
        return *this;
    }

    bool operator!=( fibit const& o )
    {
        return i != o.i;
    }
};

class fib_range
{
    size_t end_n;

public:
    explicit fib_range( size_t end_n_ )
        : end_n {end_n_}
    {}

    fibit begin() const { return fibit{}; }
    fibit end() const { return fibit{ end_n }; }
};


int main()
{
    for( size_t i : fib_range( 10 ) )
        std::cout << i << ", ";
    std::cout << std::endl;

    return 0;
}
