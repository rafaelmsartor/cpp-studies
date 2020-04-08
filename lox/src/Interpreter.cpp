//
// Created by rafael on 10/01/2020.
//

#include <Interpreter.h>
#include <Scanner.h>

#include <iostream>

void lox::Interpreter::run( std::string const& code )
{
    lox::Scanner scanner( code, *this );
    std::vector<lox::Token> tokens = scanner.scanTokens();

    for( auto token : tokens )
    {
        std::cout << token << "\n";
    }
}

void lox::Interpreter::error( size_t line, std::string const& message )
{
    report( line, "", message );
}

void lox::Interpreter::report( size_t line, std::string const& where, std::string const& message )
{
    std::cerr << "[line " << line << "] Error" << where << ": " << message << "\n";
    hadError_ = true;
}