
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "../include/Interpreter.h"

void runFile( std::string const& );
void runPrompt();

int main( int argc, char** argv )
{
    if( argc > 2 )
    {
        std::cout << "Usage: cpplox [source_file]\n";
        return 64;
    }

    if( argc == 2 )
    {
        runFile( argv[1] );
    }
    else
    {
        runPrompt();
    }

    return 0;
}

void runFile( std::string const& filename )
{
    std::ifstream sourceFile( filename, std::ios::ate );

    if( sourceFile.bad() )
    {
        throw std::invalid_argument( "Error opening file: " + filename );
    }

    size_t fileSize = sourceFile.tellg();
    sourceFile.seekg( 0 );
    std::string contents( fileSize, '\0' );

    if( !sourceFile.read( &contents[0], fileSize ) )
    {
        throw std::runtime_error( "Error reading file contents: " + filename );
    }

    lox::Interpreter interpreter;
    interpreter.run( contents );

    if( interpreter.hadError() )
        exit( 65 );
}

void runPrompt()
{
    lox::Interpreter interpreter;
    while( true )
    {
        std::cout << "> " << std::flush;
        std::string line;
        std::cin >> line;

        interpreter.run( line );
    }
}
