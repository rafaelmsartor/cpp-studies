
#ifndef LOX_PARSER_H
#define LOX_PARSER_H

#include <vector>
#include <Token.h>

namespace lox
{
    struct Expression;
    class Interpreter;

    class Parser
    {
    public:
        Parser( std::vector<Token> tokens, Interpreter& interpreter )
            : tokens_( std::move( tokens ) )
            , interpreter_( interpreter )
        {}

        Expression* parse();

    private:
        std::vector<Token> tokens_;
        size_t current_ = 0;
        Interpreter& interpreter_;

        Expression* expression();
        Expression* equality();
        Expression* comparison();
        Expression* addition();
        Expression* multiplication();
        Expression* unary();
        Expression* primary();

        template<typename T, typename... Args>
        bool match( T type, Args... values );

        Token const& advance();
        Token const& previous() const;
        Token const& peek() const;
        Token const& consume( TokenType, std::string );

        bool check( TokenType ) const;
        bool isAtEnd() const;

        void error( Token, std::string );
        void synchronize();
    };

}

#endif // LOX_PARSER_H