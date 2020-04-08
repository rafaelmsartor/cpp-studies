//
// Created by rafae on 22/01/2020.
//

#ifndef LOX_TOKEN_H
#define LOX_TOKEN_H

#include <TokenType.h>

#include <any>
#include <sstream>

namespace lox
{
    struct Token
    {
        TokenType   const type;
        std::string const lexeme;
        std::any    const literal;
        size_t      const line;

        Token( TokenType type, std::string lexeme, std::any literal, size_t line )
            : type( type )
            , lexeme( std::move(lexeme) )
            , literal( std::move(literal) )
            , line( line )
        {}
    };
}

std::ostream& operator<<( std::ostream& strm, lox::Token const& token );
#endif //LOX_TOKEN_H
