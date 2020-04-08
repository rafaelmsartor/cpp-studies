#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "../include/TokenType.h"

TEST_CASE( "TokenType strings are correct" )
{
    REQUIRE( lox::TokenTypeToString( lox::TokenType::LeftParen    ) == "LEFT PAREN"    );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::RightParen   ) == "RIGHT PAREN"   );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::LeftBrace    ) == "LEFT BRACE"    );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::RightBrace   ) == "RIGHT BRACE"   );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Comma        ) == "COMMA"         );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Dot          ) == "DOT"           );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Minus        ) == "MINUS"         );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Plus         ) == "PLUS"          );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Semicolon    ) == "SEMICOLON"     );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Slash        ) == "SLASH"         );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Star         ) == "STAR"          );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Bang         ) == "BANG"          );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::BangEqual    ) == "BANG EQUAL"    );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Equal        ) == "EQUAL"         );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::EqualEqual   ) == "EQUAL EQUAL"   );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Greater      ) == "GREATER"       );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::GreaterEqual ) == "GREATER EQUAL" );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Less         ) == "LESS"          );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::LessEqual    ) == "LESS EQUAL"    );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Identifier   ) == "IDENTIFIER"    );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::String       ) == "STRING"        );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Number       ) == "NUMBER"        );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::And          ) == "AND"           );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Class        ) == "CLASS"         );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Else         ) == "ELSE"          );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::False        ) == "FALSE"         );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Fun          ) == "FUN"           );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::For          ) == "FOR"           );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::If           ) == "IF"            );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Nil          ) == "NIL"           );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Or           ) == "OR"            );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Print        ) == "PRINT"         );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Return       ) == "RETURN"        );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Super        ) == "SUPER"         );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::This         ) == "THIS"          );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::True         ) == "TRUE"          );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Var          ) == "VAR"           );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::While        ) == "WHILE"         );
    REQUIRE( lox::TokenTypeToString( lox::TokenType::Eof          ) == "EOF"           );
}