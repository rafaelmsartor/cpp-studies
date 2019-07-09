
#include <iostream>
#include <stack>
#include <iterator>
#include <map>
#include <sstream>
#include <cassert>
#include <vector>
#include <stdexcept>
#include <cmath>

template <typename IT>
double evaluate_rpn( IT it, IT end )
{
    std::stack<double> val_stack;

    auto pop_stack( [&]()
    {
        auto r (val_stack.top());
        val_stack.pop();
        return r;
    });

    std::map<std::string, double (*) (double, double)> ops
    {
        { "+", []( double a, double b ){ return a + b; } },
        { "-", []( double a, double b ){ return a - b; } },
        { "*", []( double a, double b ){ return a * b; } },
        { "/", []( double a, double b ){ return a / b; } },
        { "^", []( double a, double b ){ return std::pow( a, b ); } },
        { "%", []( double a, double b ){ return std::fmod( a, b ); } }
    };

    for( ; it != end; ++it )
    {
        std::stringstream ss { *it };
        
        if( double val; ss >> val )
        {
            val_stack.push( val );
        }
        else
        {
            auto const r { pop_stack() };
            auto const l { pop_stack() };

            try
            {
                auto const& op ( ops.at( *it ) );
                double const result { op( l, r ) };
                val_stack.push( result );
            }
            catch( std::out_of_range const& e )
            {
                throw std::invalid_argument( *it );
            }
        }
    }
    return val_stack.top();
}

int main()
{
    try
    {
        std::cout << evaluate_rpn( std::istream_iterator<std::string>{ std::cin }, {} ) << '\n';
    }
    catch( std::invalid_argument const& e )
    {
        std::cerr << "Invalid operator: " << e.what() << '\n';
    }
    return 0;
}