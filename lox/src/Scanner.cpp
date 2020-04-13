//
// Created by rafae on 22/01/2020.
//

#include <Scanner.h>
#include <TokenType.h>
#include <Interpreter.h>
#include <stdexcept>
#include <map>

const std::map<std::string, lox::TokenType> keywords =
{
        { "and"   , lox::TokenType::And    },
        { "class" , lox::TokenType::Class  },
        { "else"  , lox::TokenType::Else   },
        { "false" , lox::TokenType::False  },
        { "for"   , lox::TokenType::For    },
        { "fun"   , lox::TokenType::Fun    },
        { "if"    , lox::TokenType::If     },
        { "nil"   , lox::TokenType::Nil    },
        { "or"    , lox::TokenType::Or     },
        { "print" , lox::TokenType::Print  },
        { "return", lox::TokenType::Return },
        { "super" , lox::TokenType::Super  },
        { "this"  , lox::TokenType::This   },
        { "true"  , lox::TokenType::True   },
        { "var"   , lox::TokenType::Var    },
        { "while" , lox::TokenType::While  }
};


bool lox::Scanner::isAtEnd() const noexcept
{
    return current_ >= source_.length();
}

std::vector<lox::Token> const& lox::Scanner::scanTokens()
{
    while( !isAtEnd() )
    {
        start_ = current_;
        scanToken();
    }

    tokens_.push_back( Token{ TokenType::Eof, "", nullptr, line_ } );
    return tokens_;
}

void lox::Scanner::scanToken()
{
    char const c = advance();
    switch( c )
    {
    case '(': addToken( TokenType::LeftParen  ); break;
    case ')': addToken( TokenType::RightParen ); break;
    case '{': addToken( TokenType::LeftBrace  ); break;
    case '}': addToken( TokenType::RightBrace ); break;
    case ',': addToken( TokenType::Comma       ); break;
    case '.': addToken( TokenType::Dot         ); break;
    case '-': addToken( TokenType::Minus       ); break;
    case '+': addToken( TokenType::Plus        ); break;
    case ';': addToken( TokenType::Semicolon   ); break;
    case '*': addToken( TokenType::Star        ); break;

    case '!': addToken( match( '=' ) ? TokenType::BangEqual    : TokenType::Bang    ); break;
    case '=': addToken( match( '=' ) ? TokenType::EqualEqual   : TokenType::Equal   ); break;
    case '<': addToken( match( '=' ) ? TokenType::LessEqual    : TokenType::Less    ); break;
    case '>': addToken( match( '=' ) ? TokenType::GreaterEqual : TokenType::Greater ); break;

    case '/':
    {
        if( match( '/' ) )
        {
            while( peek() != '\n' && !isAtEnd() ) advance();
        }
        else
        {
            addToken( TokenType::Slash );
        }
    }
    break;

    case '"':
        try
        {
            addToken( TokenType::String, scanString() );
        }
        catch( std::out_of_range& e )
        {
            interpreter_.error( line_, e.what() );
        }
        break;

    case ' ':
    case '\r':
    case '\t':
        break;

    case '\n':
        ++line_;
        break;

    default:
        if( std::isdigit( c ) )
        {
            try
            {
                addToken( TokenType::Number, scanNumber() );
            }
            catch( std::invalid_argument& e )
            {
                interpreter_.error( line_, "Error parsing number." );
            }
        }
        else if( std::isalpha( c ) )
        {
            identifier();
        }
        else
        {
            interpreter_.error( line_, "Unexpected character on scan" );
        }
        break;
    }
}

char lox::Scanner::advance()
{
    ++current_;
    return source_[current_ - 1];
}

void lox::Scanner::addToken( lox::TokenType type )
{
    addToken( type, nullptr );
}

void lox::Scanner::addToken( lox::TokenType type, std::any const& literal )
{
    std::string text = source_.substr( start_, current_ - start_ );
    tokens_.push_back( Token{ type, text, literal, line_ } );
}

bool lox::Scanner::match( char const expected )
{
    if( isAtEnd() ) return false;
    if( source_.at( current_ ) != expected ) return false;

    ++current_;
    return true;
}

char lox::Scanner::peek() const
{
    if( isAtEnd() ) return '\0';
    return source_.at( current_ );
}

char lox::Scanner::peekNext() const
{
    if( current_ + 1 >= source_.length() ) return '\0';
    return source_.at( current_ + 1 );
}

std::string lox::Scanner::scanString()
{
    while( peek() != '"' && !isAtEnd() )
    {
        if( peek() == '\n' ) ++line_;

        advance();
    }

    if( isAtEnd() )
    {
        throw std::out_of_range( "Unterminated string" );
    }

    advance();

    std::string value = source_.substr( start_ + 1, current_ - start_ - 2 );
    return value;
 }

 double lox::Scanner::scanNumber()
 {
    while( std::isdigit( peek() ) ) advance();

    if( peek() == '.' && std::isdigit( peekNext() ) )
    {
        advance();
        while( std::isdigit( peek() ) ) advance();
    }

    return std::stod( source_.substr( start_, current_ - start_ ) );
 }

void lox::Scanner::identifier()
{
    while( std::isalnum( peek() ) ) advance();

    std::string lexeme = source_.substr( start_, current_ - start_ );

    TokenType type = TokenType::Identifier;

    auto keyword = keywords.find( lexeme );
    if( keyword != keywords.end() )
        type = keyword->second;

    addToken( type );
}

std::ostream& operator<<( std::ostream& strm, lox::Token const& token )
{
    strm << token.type << " " << token.lexeme;

    if(  !token.literal.has_value()
       || token.literal.type() == typeid( nullptr ) )
    {
        return strm;
    }

    if( token.literal.type() == typeid( std::string ) )
    {
        return strm << " " << std::any_cast<std::string>( token.literal );
    }

    if( token.literal.type() == typeid( double ) )
    {
        return strm << " " << std::any_cast<double>( token.literal );
    }

    return strm << " UNKNOWN TYPE: " << token.literal.type().name();
}

std::ostream& operator<<( std::ostream& os, lox::TokenType const& type )
{
    return os << lox::TokenTypeToString( type );
}

std::string lox::TokenTypeToString( lox::TokenType type )
{
    switch( type )
    {
    case TokenType::LeftParen   : return "LEFT PAREN";
    case TokenType::RightParen  : return "RIGHT PAREN";
    case TokenType::LeftBrace   : return "LEFT BRACE";
    case TokenType::RightBrace  : return "RIGHT BRACE";
    case TokenType::Comma       : return "COMMA";
    case TokenType::Dot         : return "DOT";
    case TokenType::Minus       : return "MINUS";
    case TokenType::Plus        : return "PLUS";
    case TokenType::Semicolon   : return "SEMICOLON";
    case TokenType::Slash       : return "SLASH";
    case TokenType::Star        : return "STAR";
    case TokenType::Bang        : return "BANG";
    case TokenType::BangEqual   : return "BANG EQUAL";
    case TokenType::Equal       : return "EQUAL";
    case TokenType::EqualEqual  : return "EQUAL EQUAL";
    case TokenType::Greater     : return "GREATER";
    case TokenType::GreaterEqual: return "GREATER EQUAL";
    case TokenType::Less        : return "LESS";
    case TokenType::LessEqual   : return "LESS EQUAL";
    case TokenType::Identifier  : return "IDENTIFIER";
    case TokenType::String      : return "STRING";
    case TokenType::Number      : return "NUMBER";
    case TokenType::And         : return "AND";
    case TokenType::Class       : return "CLASS";
    case TokenType::Else        : return "ELSE";
    case TokenType::False       : return "FALSE";
    case TokenType::Fun         : return "FUN";
    case TokenType::For         : return "FOR";
    case TokenType::If          : return "IF";
    case TokenType::Nil         : return "NIL";
    case TokenType::Or          : return "OR";
    case TokenType::Print       : return "PRINT";
    case TokenType::Return      : return "RETURN";
    case TokenType::Super       : return "SUPER";
    case TokenType::This        : return "THIS";
    case TokenType::True        : return "TRUE";
    case TokenType::Var         : return "VAR";
    case TokenType::While       : return "WHILE";
    case TokenType::Eof         : return "EOF";

    default: return "UNKNOWN";
    }
}