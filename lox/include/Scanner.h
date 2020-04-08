//
// Created by rafae on 22/01/2020.
//

#ifndef LOX_SCANNER_H
#define LOX_SCANNER_H

#include <Token.h>

#include <vector>
#include <string>
#include "Interpreter.h"

namespace lox
{
    class Scanner
    {
        Interpreter& interpreter_;

        std::string source_;
        std::vector<Token> tokens_;

        size_t start_   = 0;
        size_t current_ = 0;
        size_t line_    = 1;

        [[nodiscard]] bool isAtEnd() const noexcept;

        void scanToken();
        char advance();
        void addToken( TokenType type );
        void addToken( TokenType type, std::any const& literal );
        bool match( char const expected );
        char peek() const;
        char peekNext() const;

        std::string scanString();
        double scanNumber();
    public:
        Scanner( std::string source, Interpreter& interpreter )
            : interpreter_( interpreter )
            , source_( std::move(source) )
        {}

        std::vector<Token> const& scanTokens();

        void identifier();
    };
}

#endif //LOX_SCANNER_H
