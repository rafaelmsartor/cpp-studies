
#include <Evaluator.h>

lox::literal_t lox::Evaluator::evaluate( lox::Expression* expression )
{
    expression->accept( *this );

    return value_;
}

bool lox::Evaluator::isTruthy( literal_t value ) const
{
    bool truthy = false;
    std::visit( [&truthy]( auto& arg )
        {
            using T = std::decay_t<decltype(arg)>;

            if constexpr( std::is_same_v<T, std::string> )
            {
                truthy = !arg.empty();
            }
            else if constexpr( std::is_same_v<T, double> )
            {
                truthy = arg != 0;
            }
            else if constexpr( std::is_same_v<T, bool> )
            {
                truthy = arg;
            }
        }, value );
    return truthy;
}

void lox::Evaluator::visit( lox::Literal* expression )
{
    value_ = expression->value_;
}

void lox::Evaluator::visit( lox::Grouping* expression )
{
    value_ = Evaluator().evaluate( expression->expression_.get() );
}

void lox::Evaluator::visit( lox::Unary* expression )
{
    literal_t value = Evaluator().evaluate( expression );

    switch( expression->operator_.type )
    {
    case lox::TokenType::Minus:
        value_ = -(std::get<double>( value ));
        break;

    case lox::TokenType::Bang:
        value_ = !(isTruthy( value ));
        break;

    default:
        break;
    }
}

void lox::Evaluator::visit( lox::Binary* expression )
{
    literal_t left = Evaluator().evaluate( expression->left_.get() );
    literal_t right = Evaluator().evaluate( expression->right_.get() );

    switch( expression->operator_.type )
    {
    case lox::TokenType::Plus:
        std::visit( [this, &right]( auto& arg )
            {
                using T = std::decay_t<decltype(arg)>;
                if constexpr( std::is_same_v<T, double>
                    || std::is_same_v<T, std::string> )
                {
                    if( std::holds_alternative<T>( right ) )
                    {
                        value_ = arg + std::get<T>( right );
                    }
                }
            }, left );
        break;
    
    case lox::TokenType::Minus:
        value_ = std::get<double>( left ) - std::get<double>( right );
        break;

    case lox::TokenType::Slash:
        value_ = std::get<double>( left ) / std::get<double>( right );
        break;

    case lox::TokenType::Star:
        value_ = std::get<double>( left ) * std::get<double>( right );
        break;

    case lox::TokenType::Greater:
        value_ = std::get<double>( left ) > std::get<double>( right );
        break;

    case lox::TokenType::GreaterEqual:
        value_ = std::get<double>( left ) >= std::get<double>( right );
        break;

    case lox::TokenType::Less:
        value_ = std::get<double>( left ) < std::get<double>( right );
        break;

    case lox::TokenType::LessEqual:
        value_ = std::get<double>( left ) <= std::get<double>( right );
        break;

    case lox::TokenType::BangEqual:
        value_ = left != right;
        break;

    case lox::TokenType::EqualEqual:
        value_ = left == right;
        break;

    default:
        break;
    }
}
