//
// Created by rafae on 22/01/2020.
//

#ifndef LOX_TOKEN_H
#define LOX_TOKEN_H

#include <TokenType.h>

#include <sstream>
#include <variant>

namespace lox
{
    typedef std::variant<std::string, double, bool, std::nullptr_t> literal_t;

    struct Token
    {
        TokenType   const type;
        std::string const lexeme;
        literal_t   const literal;
        size_t      const line;

        Token( TokenType type, std::string lexeme, literal_t literal, size_t line )
            : type( type )
            , lexeme( std::move(lexeme) )
            , literal( std::move(literal) )
            , line( line )
        {}
    };
}

std::ostream& operator<<( std::ostream& strm, lox::Token const& token );
std::ostream& operator<<( std::ostream& strm, lox::literal_t const& literal );
#endif //LOX_TOKEN_H
