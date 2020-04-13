
#include "catch.hpp"

#include "../include/Scanner.h"


SCENARIO( "Token lexers" )
{
    GIVEN( "An interpreter" )
    {
        lox::Interpreter interpreter;

        WHEN( "an variable is declared with a number assignment" )
        {
            std::string const expression( "var temp = 42;" );

            lox::Scanner scanner( expression, interpreter );
            auto const tokens = scanner.scanTokens();

            THEN( "the 'Number' token is identified after the 'Equal'" )
            {
                REQUIRE( tokens.size() == 6 );
                REQUIRE( tokens[0].type == lox::TokenType::Var        );
                REQUIRE( tokens[1].type == lox::TokenType::Identifier );
                REQUIRE( tokens[2].type == lox::TokenType::Equal      );
                REQUIRE( tokens[3].type == lox::TokenType::Number     );
                REQUIRE( tokens[4].type == lox::TokenType::Semicolon  );
                REQUIRE( tokens[5].type == lox::TokenType::Eof        );
            }
            AND_THEN( "the variable name is read" )
            {
                REQUIRE( tokens[1].lexeme == "temp" );
            }
            AND_THEN( "the value is parsed correctly" )
            {
                REQUIRE( tokens[3].literal.type() == typeid(double) );
                REQUIRE( std::any_cast<double>(tokens[3].literal) == 42.0 );
            }
        }

        WHEN( "a string is assigned to a variable" )
        {
            std::string const expression( "temp = \"test string\";" );

            lox::Scanner scanner( expression, interpreter );
            auto const tokens = scanner.scanTokens();

            THEN( "the 'String' token is recognized" )
            {
                REQUIRE( tokens.size() == 5 );
                REQUIRE( tokens[0].type == lox::TokenType::Identifier );
                REQUIRE( tokens[1].type == lox::TokenType::Equal );
                REQUIRE( tokens[2].type == lox::TokenType::String );
                REQUIRE( tokens[3].type == lox::TokenType::Semicolon );
                REQUIRE( tokens[4].type == lox::TokenType::Eof );
            }
            AND_THEN( "the value is parsed correctly" )
            {
                REQUIRE( tokens[2].literal.type() == typeid(std::string) );
                REQUIRE( std::any_cast<std::string>(tokens[2].literal) == "test string" );
            }
        }

        WHEN( "a lisit of the numeric operators is given" )
        {
            std::string const operators( "+-*/" );

            THEN( "all are recognized" )
            {
                lox::Scanner scanner( operators, interpreter );
                auto const tokens = scanner.scanTokens();

                REQUIRE( tokens.size() == 5 );
                REQUIRE( tokens[0].type == lox::TokenType::Plus );
                REQUIRE( tokens[1].type == lox::TokenType::Minus );
                REQUIRE( tokens[2].type == lox::TokenType::Star );
                REQUIRE( tokens[3].type == lox::TokenType::Slash );
                REQUIRE( tokens[4].type == lox::TokenType::Eof );
            }
        }

        WHEN( "a list of comparison operators is given" )
        {
            std::string operators( "== != ! < <= > >=" );

            THEN( "all are recognized" )
            {
                lox::Scanner scanner( operators, interpreter );
                auto const tokens = scanner.scanTokens();

                REQUIRE( tokens.size() == 8 );
                REQUIRE( tokens[0].type == lox::TokenType::EqualEqual   );
                REQUIRE( tokens[1].type == lox::TokenType::BangEqual    );
                REQUIRE( tokens[2].type == lox::TokenType::Bang         );
                REQUIRE( tokens[3].type == lox::TokenType::Less         );
                REQUIRE( tokens[4].type == lox::TokenType::LessEqual    );
                REQUIRE( tokens[5].type == lox::TokenType::Greater      );
                REQUIRE( tokens[6].type == lox::TokenType::GreaterEqual );
                REQUIRE( tokens[7].type == lox::TokenType::Eof          );
            }
        }

        WHEN( "the remaining single character tokens are given" )
        {
            std::string const remainingTokens( "{} () ," );

            THEN( "all are recognized" )
            {
                lox::Scanner scanner( remainingTokens, interpreter );
                auto const tokens = scanner.scanTokens();

                REQUIRE( tokens.size() == 6 );
                REQUIRE( tokens[0].type == lox::TokenType::LeftBrace );
                REQUIRE( tokens[1].type == lox::TokenType::RightBrace );
                REQUIRE( tokens[2].type == lox::TokenType::LeftParen );
                REQUIRE( tokens[3].type == lox::TokenType::RightParen );
                REQUIRE( tokens[4].type == lox::TokenType::Comma );
                REQUIRE( tokens[5].type == lox::TokenType::Eof );
            }
        }
            
        WHEN( "the control keywords are given" )
        {
            std::string const keywords( "for while if else" );

            THEN( "all are recognized" )
            {
                lox::Scanner scanner( keywords, interpreter );
                auto const tokens = scanner.scanTokens();

                REQUIRE( tokens.size() == 5 );
                REQUIRE( tokens[0].type == lox::TokenType::For );
                REQUIRE( tokens[1].type == lox::TokenType::While );
                REQUIRE( tokens[2].type == lox::TokenType::If );
                REQUIRE( tokens[3].type == lox::TokenType::Else );
                REQUIRE( tokens[4].type == lox::TokenType::Eof );
            }
        }

        WHEN( "the remaining keywords are given" )
        {
            std::string const keywords( "and or nil true false\n"
                                        "this super class\n"
                                        "fun return" );

            THEN( "all are recognized" )
            {
                lox::Scanner scanner( keywords, interpreter );
                auto const tokens = scanner.scanTokens();

                REQUIRE( tokens.size() == 11 );
                REQUIRE( tokens[0].type == lox::TokenType::And );
                REQUIRE( tokens[1].type == lox::TokenType::Or );
                REQUIRE( tokens[2].type == lox::TokenType::Nil );
                REQUIRE( tokens[3].type == lox::TokenType::True );
                REQUIRE( tokens[4].type == lox::TokenType::False );
                REQUIRE( tokens[5].type == lox::TokenType::This );
                REQUIRE( tokens[6].type == lox::TokenType::Super );
                REQUIRE( tokens[7].type == lox::TokenType::Class );
                REQUIRE( tokens[8].type == lox::TokenType::Fun );
                REQUIRE( tokens[9].type == lox::TokenType::Return );
            }
        }
    }
}
