//
// Created by rafael on 10/01/2020.
//

#include <Interpreter.h>
#include <Scanner.h>
#include <Parser.h>

#include <AstPrinter.h>

#include <iostream>

void lox::Interpreter::run( std::string const& code )
{
    lox::Scanner scanner( code, *this );
    std::vector<lox::Token> tokens = scanner.scanTokens();

    lox::Parser parser( tokens, *this );
    std::unique_ptr<Expression> expression{ parser.parse() };

    if( hadError() ) return;

    std::cout << AstPrinter().print( expression.get() ) << "\n";
}

void lox::Interpreter::error( size_t line, std::string const& message )
{
    report( line, "", message );
}

void lox::Interpreter::error( lox::Token const& token, std::string const& message )
{
    if( token.type == TokenType::Eof )
    {
        report( token.line, "at end", message );
    }
    else
    {
        report( token.line, "at '" + token.lexeme + "'", message );
    }
}

void lox::Interpreter::report( size_t line, std::string const& where, std::string const& message )
{
    std::cerr << "[line " << line << "] Error " << where << ": " << message << "\n";
    hadError_ = true;
}