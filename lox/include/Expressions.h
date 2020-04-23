
#ifndef LOX_EXPRESSIONS_H
#define LOX_EXPRESSIONS_H

#include "Token.h"

namespace lox
{
    template< typename... Types>
    class Visitor;

    template<typename T>
    class Visitor<T>
    {
    public:
        virtual void visit( T* ) = 0;
    };

    template< typename T, typename... Types>
    class Visitor<T, Types...> : public Visitor<Types...>
    {
    public:
        using Visitor<Types...>::visit;
        virtual void visit( T* ) = 0;
    };

    using ExpressionVisitor = Visitor<struct Binary, struct Grouping, struct Literal, struct Unary>;

    struct Expression
    {
        virtual ~Expression() = default;
        virtual void accept( ExpressionVisitor& ) = 0;
    };

    template<typename Derived>
    struct VisitableExpression : Expression
    {
        void accept( ExpressionVisitor& visitor ) override
        {
            visitor.visit( static_cast<Derived*>(this) );
        }
    };

    struct Binary : VisitableExpression<Binary>
    {
        const std::unique_ptr<Expression> left_;
        const Token operator_;
        const std::unique_ptr<Expression> right_;

        Binary( std::unique_ptr<Expression> left, Token oper, std::unique_ptr<Expression> right )
            : left_{ std::move(left) }
            , operator_{ oper }
            , right_{ std::move(right) }
        {}
    };

    struct Grouping : VisitableExpression<Grouping>
    {
        const std::unique_ptr<Expression> expression_;

        Grouping( std::unique_ptr<Expression> expression )
            : expression_{ std::move(expression) }
        {}
    };

    struct Literal : VisitableExpression<Literal>
    {
        const literal_t value_;

        Literal( literal_t value )
            : value_{ value }
        {}
    };

    struct Unary : VisitableExpression<Unary>
    {
        const Token operator_;
        const std::unique_ptr<Expression> right_;

        Unary( Token oper, std::unique_ptr<Expression> right )
            : operator_{ oper }
            , right_{ std::move(right) }
        {}
    };
} //namespace lox

#endif //LOX_EXPRESSIONS_H
