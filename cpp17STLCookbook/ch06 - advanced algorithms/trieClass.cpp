#include <iostream>
#include <algorithm>
#include <string>

#include "trie.hpp" 

int main()
{
    trie<std::string> t;
    t.insert({"hi", "how", "are", "you"});
    t.insert({"hi", "i", "am", "great", "thanks"});
    t.insert({"what", "are", "you", "doing"});
    t.insert({"i", "am", "watching", "a", "movie"});

    std::cout << "Recorded sentences:\n";
    t.print();

    std::cout << "\nPossible suggestions after \"hi\":\n";
    if( auto st ( t.subtrie( std::initializer_list<std::string>{ "hi" } ) ); st )
    {
        st->get().print();
    }
}
