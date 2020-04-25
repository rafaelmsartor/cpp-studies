
#include <Parser.h>

#include <Expressions.h>
#include <Interpreter.h>

lox::Expression* lox::Parser::parse()
{
    try
    {
        return expression();
    }
    catch( std::exception& )
    {
        return nullptr;
    }
}

lox::Expression* lox::Parser::expression()
{
    return equality();
}

lox::Expression* lox::Parser::equality()
{
    Expression* expr = comparison();

    while( match( TokenType::EqualEqual, TokenType::BangEqual ) )
    {
        Token oper = previous();
        Expression* right = comparison();
        expr = new Binary{ expr, oper, right };
    }

    return expr;
}

lox::Expression* lox::Parser::comparison()
{
    Expression* expr = addition();

    while( match( TokenType::Greater, TokenType::GreaterEqual
                , TokenType::Less, TokenType::LessEqual ) )
    {
        Token oper = previous();
        Expression* right = addition();
        expr = new Binary{ expr, oper, right };
    }
    return expr;
}

lox::Expression* lox::Parser::addition()
{
    Expression* expr = multiplication();

    while( match( TokenType::Plus, TokenType::Minus ) )
    {
        Token oper = previous();
        Expression* right = multiplication();
        expr = new Binary{ expr, oper, right };
    }
    return expr;
}

lox::Expression* lox::Parser::multiplication()
{
    Expression* expr = unary();

    while( match( TokenType::Star, TokenType::Slash ) )
    {
        Token oper = previous();
        Expression* right = unary();
        expr = new Binary{ expr, oper, right };
    }
    return expr;
}

lox::Expression* lox::Parser::unary()
{
    if( match( TokenType::Bang, TokenType::Minus ) )
    {
        Token oper = previous();
        Expression* right = unary();
        return new Unary{ oper, right };
    }
    return primary();
}

lox::Expression* lox::Parser::primary()
{
    if( match( TokenType::True  ) ) return new Literal{ true    };
    if( match( TokenType::False ) ) return new Literal{ false   };
    if( match( TokenType::Nil   ) ) return new Literal{ nullptr };

    if( match( TokenType::Number, TokenType::String ) )
    {
        return new Literal( previous().literal );
    }

    if( match( TokenType::LeftParen ) )
    {
        Expression* expr = expression();
        consume( TokenType::RightParen, "')' expected after expresssion." );
        return new Grouping( expr );
    }

    error( peek(), "Expected an expression" );
    throw std::runtime_error( "Expected and expression" );
}

template<typename T, typename... Args>
bool lox::Parser::match( T type, Args... types )
{
    if constexpr( sizeof...(types) > 0 )
    {
        if( !match( types... ) && check( type ) )
        {
            advance();
            return true;
        }
    }
    else
    {
        if( check( type ) )
        {
            advance();
            return true;
        }
    }
    return false;
}

bool lox::Parser::check( lox::TokenType type ) const
{
    if( isAtEnd() ) return false;

    return peek().type == type;
}

bool lox::Parser::isAtEnd() const
{
    return peek().type == TokenType::Eof;
}

lox::Token const& lox::Parser::advance()
{
    if( !isAtEnd() ) ++current_;
    return previous();
}

lox::Token const& lox::Parser::previous() const
{
    return tokens_[current_ - 1];
}

lox::Token const& lox::Parser::peek() const
{
    return tokens_[current_];
}

lox::Token const& lox::Parser::consume( lox::TokenType type, std::string message )
{
    if( check( type ) ) return advance();

    error( peek(), message );
    throw std::runtime_error( message );
}

void lox::Parser::error( lox::Token token, std::string message )
{
    interpreter_.error( token, message );
}

void lox::Parser::synchronize()
{
    advance();

    while( !isAtEnd() )
    {
        if( previous().type == TokenType::Semicolon )
            return;

        switch( peek().type )
        {
        case TokenType::Class:
        case TokenType::Fun:
        case TokenType::Var:
        case TokenType::For:
        case TokenType::If:
        case TokenType::While:
        case TokenType::Print:
        case TokenType::Return:
            return;

        default: break;
        }

        advance();
    }
}
