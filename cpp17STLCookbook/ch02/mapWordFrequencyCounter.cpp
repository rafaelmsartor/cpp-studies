
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

std::string filter_punctuation( std::string const& s )
{
    char const* forbidden { ".,:; " };
    auto const idx_start ( s.find_first_not_of( forbidden ) );
    auto const idx_end ( s.find_last_not_of( forbidden ) );
    return s.substr( idx_start, idx_end - idx_start + 1 );
}

int main()
{
    std::map<std::string, size_t> words;
    int max_word_len { 0 };
    std::string s;

    while( std::cin >> s )
    {
        auto filtered ( filter_punctuation( s ) );
        max_word_len = std::max<int>( max_word_len, filtered.length() );
        ++words[filtered];
    }

    std::vector<std::pair<std::string, size_t>> word_counts;
    word_counts.reserve( words.size() );
    std::move( std::begin( words ), std::end( words ), std::back_inserter( word_counts ) );

    std::sort( std::begin( word_counts ), std::end( word_counts ), []( auto const& a, auto const& b ) 
    {
        return a.second > b.second;
    });

    std::cout << "# " << std::setw( max_word_len ) << "<WORD>" << " #<COUNT>\n";
    for( auto const& [word, count] : word_counts )
    {
        std::cout << std::setw( max_word_len + 2 ) << word << " #" << count << '\n';
    }
    return 0;
}
