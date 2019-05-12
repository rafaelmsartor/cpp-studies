
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace html
{
    class Tag
    {
    protected:
        string name;
        string text;
        vector<Tag> children;
        vector<pair<string, string>> attributes;

        explicit Tag( string const& name )
            : name( name )
        {}

        Tag( string const& name, string const& text )
            : name( name )
            , text( text )
        {}

        Tag( string const& name, vector<Tag> const& children )
            : name( name )
            , children( children )
        {}
    
    public:
        friend ostream& operator<<( ostream& os, Tag const& tag )
        {
            os << '<'<< tag.name;

            for( auto const& attribute : tag.attributes )
                os << ' ' << attribute.first << "=\"" << attribute.second << '\"';

            if( tag.children.empty() && tag.text.empty() )
                os << "/>\n";
            else
            {
                os << ">\n";

                if( !tag.text.empty() )
                    os << tag.text << '\n';

                for( auto const& child : tag.children )
                    os << child;

                os << "</" << tag.name << ">\n";
            }
            return os;
        }
    };

    
    class P : public Tag
    {
    public:
        explicit P( string const& text )
            : Tag{ "p", text }
        {}

        P( initializer_list<Tag> children )
            : Tag{ "p", children }
        {}
    };

    class IMG : public Tag
    {
    public:
        explicit IMG( string const& url )
            : Tag{ "img" }
        {
            attributes.emplace_back( make_pair( "src", url ) );
        }
    };
}


int main( )
{
    cout << 
    html::P {
        html::IMG{ "http://www.example.com/image.png" }
    }
    << endl;

    return 0;
}