
#include <iostream>
#include <algorithm>

class num_iterator
{
    int i;

public:
    explicit num_iterator( int position = 0 )
        : i { position }
    {}

    int operator*() const noexcept { return i; }
    
    num_iterator& operator++()
    {
        ++i;
        return *this;
    }

    bool operator!=( num_iterator const& other ) const noexcept
    {
        return i != other.i;
    }
    
    bool operator==( num_iterator const& other ) const noexcept
    {
        return !( *this != other );
    }
};

class num_range
{
    int a;
    int b;

public:
    num_range( int from, int to )
        : a { from }
        , b { to }
    {}
    num_iterator begin() const { return num_iterator( a ); }
    num_iterator end() const { return num_iterator( b ); }
};

// Enable forward iterator traits for the custom iterator
//   according to the book this was necessary for the code to compile on Clang 5.0.0,
//   however on GCC 7.4.0 it compiled normally
namespace std
{
    template<>
    struct iterator_traits<num_iterator>
    {
        // This traits class contains up to five different type member definitions:
        //   * difference_type: What type results from writing it1 - it2?
        //   * value_type: Of what type is the item which we access with *it (note that this is void for pure output iterators)?
        //   * pointer: Of what type must a pointer be in order to point to an item?
        //   * reference: Of what type must a reference be in order to reference an item?
        //   * iterator_category: Which category does the iterator belong to?
        using iterator_category = std::forward_iterator_tag;
        using value_type = int;
    };
}

int main()
{
    num_range r { 100, 110 };

    auto [min_it, max_it] ( std::minmax_element( std::begin( r ), std::end( r ) ) );
    std::cout << *min_it << " - " << *max_it << '\n';

    return 0;
}
