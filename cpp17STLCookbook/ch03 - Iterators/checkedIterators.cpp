
#include <iostream>
#include <vector>

// use -D_GLIBCXX_DEBUG with g++ to activate a higher level o sanity checking
// /D_ITERATOR_DEBUG_LEVEL=1 on msvc
int main()
{
    std::vector<int> v { 1, 2, 3 };
    v.shrink_to_fit();
    auto const it ( std::begin(v) );
    std::cout << *it << '\n';

    // since shrink_to_fit was used, this push_back will force a memory reallocation
    //   invalidating the previous iterator.
    v.push_back( 123 );
    // if the debug mode is on this next line will fail upon execution
    std::cout << *it << '\n';

    return 0;
}