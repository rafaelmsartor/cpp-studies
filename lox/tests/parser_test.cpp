
#include "catch.hpp"

#include <Parser.h>
#include <Scanner.h>
#include <Expressions.h>

#include <AstPrinter.h>

SCENARIO( "Valid single expression parser" )
{
    lox::Interpreter interpreter;

    GIVEN( "Literal sentences" )
    {
        std::string const true_str{ "true" };
        
        WHEN( "a 'true' constant is scanned" )
        {
            lox::Scanner scanner( true_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a boolean true value is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Literal* literal_ = dynamic_cast<lox::Literal*>(expression.get());
                
                REQUIRE( literal_ != nullptr );
                REQUIRE( std::get<bool>(literal_->value_) == true );
            }
        }

        
        std::string const false_str{ "false" };
        
        WHEN( "a 'false' constant is scanned" )
        {
            lox::Scanner scanner( false_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a boolean false value is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Literal* literal_ = dynamic_cast<lox::Literal*>(expression.get());

                REQUIRE( literal_ != nullptr );
                REQUIRE( std::get<bool>( literal_->value_ ) == false );
            }
        }

        
        std::string const nil_str{ "nil" };
        
        WHEN( "a 'nil' constant is scanned" )
        {
            lox::Scanner scanner( nil_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a nil value is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Literal* literal_ = dynamic_cast<lox::Literal*>(expression.get());

                REQUIRE( literal_ != nullptr );
                REQUIRE( std::get<std::nullptr_t>( literal_->value_ ) == nullptr );
            }
        }

        
        std::string const number_str{ "123456" };
        
        WHEN( "a number constant is scanned" )
        {
            lox::Scanner scanner( number_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a number value is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Literal* literal_ = dynamic_cast<lox::Literal*>(expression.get());

                REQUIRE( literal_ != nullptr );
                REQUIRE( std::get<double>( literal_->value_ ) == 123456 );
            }
        }

        std::string const literal_str{ "\"abcdef\"" };
        
        WHEN( "a string constant is scanned" )
        {
            lox::Scanner scanner( literal_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a string value is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Literal* literal_ = dynamic_cast<lox::Literal*>(expression.get());

                REQUIRE( literal_ != nullptr );
                REQUIRE( std::get<std::string>( literal_->value_ ) == "abcdef" );
            }
        }
    }

    GIVEN( "Unary expressions" )
    {
        std::string const negation_str{ "! true" };
        
        WHEN( "the negation is scanned " )
        {
            lox::Scanner scanner( negation_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a unary negation expression is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Unary* unary = dynamic_cast<lox::Unary*>(expression.get());

                REQUIRE( unary != nullptr );
                REQUIRE( unary->operator_.type == lox::TokenType::Bang );
                
                std::string const ast = AstPrinter().print( expression.get() );

                REQUIRE( ast == "(! true)" );
            }
        }

        
        std::string const negative_str{ "-123456" };
        
        WHEN( "the negative is scanned " )
        {
            lox::Scanner scanner( negative_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a unary negative number is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Unary* unary = dynamic_cast<lox::Unary*>(expression.get());

                REQUIRE( unary != nullptr );
                REQUIRE( unary->operator_.type == lox::TokenType::Minus );

                std::string const ast = AstPrinter().print( expression.get() );

                REQUIRE( ast == "(- 123456)" );
            }
        }
    }

    GIVEN( "multiplication expressions" )
    {
        std::string const multiplication_str{ "7 * 6" };
        
        WHEN( "the multiplication is scanned" )
        {
            lox::Scanner scanner( multiplication_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a multiplication binary expression is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());
                
                REQUIRE( binary != nullptr );
                REQUIRE( binary->operator_.type == lox::TokenType::Star );

                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(* 7 6)" );
            }
        }

        
        std::string const division_str{ "126 / 3" };
        
        WHEN( "the division is scanned" )
        {
            lox::Scanner scanner( division_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a division binary expression is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());

                REQUIRE( binary != nullptr );
                REQUIRE( binary->operator_.type == lox::TokenType::Slash );

                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(/ 126 3)" );
            }
        }

        
        std::string const sequence_str{ "3 * (5/6 ) *    37" };
        
        WHEN( "the sequence is scanned" )
        {
            lox::Scanner scanner( sequence_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a binary expression is parsed, and precedence is respected" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());

                REQUIRE( binary != nullptr );
                
                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(* (* 3 (grouping (/ 5 6))) 37)" );
            }
        }
    }

    GIVEN( "addition expressions" )
    {
        std::string const addition_str{ "7 + 6" };
        
        WHEN( "the addition is scanned" )
        {
            lox::Scanner scanner( addition_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "an addition binary expression is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());

                REQUIRE( binary != nullptr );
                REQUIRE( binary->operator_.type == lox::TokenType::Plus );

                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(+ 7 6)" );
            }
        }

        
        std::string const subtraction_str{ "126 - 3" };
        
        WHEN( "the subtraction is scanned" )
        {
            lox::Scanner scanner( subtraction_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a subtraction binary expression is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());

                REQUIRE( binary != nullptr );
                REQUIRE( binary->operator_.type == lox::TokenType::Minus );

                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(- 126 3)" );
            }
        }

        std::string const sequence_str{ "1 + 2 * 3 - ( 4 + 5 )" };

        WHEN( "the sequence is scanned" )
        {
            lox::Scanner scanner( sequence_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a binary expression is parsed, and precedence is respected" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());

                REQUIRE( binary != nullptr );

                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(- (+ 1 (* 2 3)) (grouping (+ 4 5)))" );
            }
        }
    }

    GIVEN( "comparison expressions" )
    {
        std::string const less_str{ "7 < 6" };
        
        WHEN( "the less comparison is scanned" )
        {
            lox::Scanner scanner( less_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a binary expression is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());

                REQUIRE( binary != nullptr );
                REQUIRE( binary->operator_.type == lox::TokenType::Less );

                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(< 7 6)" );
            }
        }

        
        std::string const less_equal_str{ "7 <= 6" };
        
        WHEN( "the less equal comparison is scanned" )
        {
            lox::Scanner scanner( less_equal_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a binary expression is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());

                REQUIRE( binary != nullptr );
                REQUIRE( binary->operator_.type == lox::TokenType::LessEqual );

                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(<= 7 6)" );
            }
        }

        
        std::string const greater_str{ "126 > 3" };
        
        WHEN( "the greater comparison is scanned" )
        {
            lox::Scanner scanner( greater_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a binary expression is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());

                REQUIRE( binary != nullptr );
                REQUIRE( binary->operator_.type == lox::TokenType::Greater );

                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(> 126 3)" );
            }
        }

        
        std::string const greater_equal_str{ "126 >= 3" };
        
        WHEN( "the greater equal comparison is scanned" )
        {
            lox::Scanner scanner( greater_equal_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a binary expression is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());

                REQUIRE( binary != nullptr );
                REQUIRE( binary->operator_.type == lox::TokenType::GreaterEqual );

                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(>= 126 3)" );
            }
        }

        
        std::string const sequence_str{ "3 > 4-5 < 6" };

        WHEN( "the sequence is scanned" )
        {
            lox::Scanner scanner( sequence_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a binary expression is parsed, and precedence is respected" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());

                REQUIRE( binary != nullptr );

                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(< (> 3 (- 4 5)) 6)" );
            }
        }
    }
    

    GIVEN( "equality expressions" )
    {
        std::string const equals_str{ "true == false" };

        WHEN( "the eqeuals comparison is scanned" )
        {
            lox::Scanner scanner( equals_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "an binary expression is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());

                REQUIRE( binary != nullptr );
                REQUIRE( binary->operator_.type == lox::TokenType::EqualEqual );

                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(== true false)" );
            }
        }


        std::string const different_str{ "\"abc\" != nil" };

        WHEN( "the difference is scanned" )
        {
            lox::Scanner scanner( different_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a binary expression is parsed" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());

                REQUIRE( binary != nullptr );
                REQUIRE( binary->operator_.type == lox::TokenType::BangEqual );

                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(!= abc nil)" );
            }
        }


        std::string const sequence_str{ "true == 1 < 2 + 3" };

        WHEN( "the sequence is scanned" )
        {
            lox::Scanner scanner( sequence_str, interpreter );
            auto tokens = scanner.scanTokens();

            THEN( "a binary expression is parsed, and precedence is respected" )
            {
                lox::Parser parser( tokens, interpreter );
                std::unique_ptr<lox::Expression> expression( parser.parse() );

                lox::Binary* binary = dynamic_cast<lox::Binary*>(expression.get());

                REQUIRE( binary != nullptr );

                std::string const ast = AstPrinter().print( expression.get() );
                REQUIRE( ast == "(== true (< 1 (+ 2 3)))" );
            }
        }
    }
}