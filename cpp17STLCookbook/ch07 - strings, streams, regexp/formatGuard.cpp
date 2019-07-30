
#include <iostream>
#include <iomanip>

class format_guard
{
    decltype( std::cout.flags() ) f{ std::cout.flags() };
public:
    ~format_guard(){ std::cout.flags( f ); }
};

template <typename T>
struct scientific_type
{
    T value;
    explicit scientific_type( T val )
        : value{ val }
    {}
};

template <typename T>
std::ostream& operator<<( std::ostream& os, scientific_type<T> const& w )
{
    format_guard _;
    os << std::scientific << std::uppercase << std::showpos;
    return os << w.value;
}

int main( )
{
    {
        format_guard _;
        std::cout << std::hex << std::scientific << std::showbase << std::uppercase;
        std::cout << "Numbers with special formatting:\n";
        std::cout << 0x123abc << '\n';
        std::cout << 0.123456789 << '\n';
    }

    std::cout << "Same numbers but with normal formatting:\n";
    std::cout << 0x123abc << '\n';
    std::cout << 0.123456789 << '\n';


    std::cout << "Mixed formatting: " << 123.0 << " " << scientific_type{ 123.0 } << " " << 123.456 << '\n';
}