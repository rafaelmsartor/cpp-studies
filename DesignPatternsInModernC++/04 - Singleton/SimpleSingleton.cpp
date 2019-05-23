
#include <string>
#include <iostream>
#include <fstream>
#include <map>

class SingletonDatabase
{
    std::map<std::string, int> capitals;

    SingletonDatabase()
    {
        std::cout << "Initializing database\n";
        std::ifstream ifs( "capitals.txt" );

        std::string s, s2;
        while( std::getline( ifs, s ) )
        {
            std::getline( ifs, s2 );
            int population = std::stoi( s2 );
            capitals[s] = population;
        }
    }

public:
    SingletonDatabase( SingletonDatabase const& ) = delete;
    SingletonDatabase& operator=( SingletonDatabase const& ) = delete;

    static SingletonDatabase& get()
    {
        static SingletonDatabase db;
        return db;
    }

    int get_population( std::string const& name )
    {
        return capitals[name];
    }
};