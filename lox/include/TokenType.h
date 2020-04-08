//
// Created by rafae on 22/01/2020.
//

#ifndef LOX_TOKENTYPE_H
#define LOX_TOKENTYPE_H

#include <sstream>

namespace lox
{
    enum class TokenType
    {
        // single-character tokens
        LeftParen,
        RightParen,
        LeftBrace,
        RightBrace,
        Comma,
        Dot,
        Minus,
        Plus,
        Semicolon,
        Slash,
        Star,

        // one or two character tokens
        Bang,
        BangEqual,
        Equal,
        EqualEqual,
        Greater,
        GreaterEqual,
        Less,
        LessEqual,

        // literals
        Identifier,
        String,
        Number,

        // keywords
        And,
        Class,
        Else,
        False,
        Fun,
        For,
        If,
        Nil,
        Or,
        Print,
        Return,
        Super,
        This,
        True,
        Var,
        While,

        Eof
    };


    char const* TokenTypeToString( lox::TokenType type );
}

std::ostream& operator<<( std::ostream& os, lox::TokenType const& type );

#endif //LOX_TOKENTYPE_H
