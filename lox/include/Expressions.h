
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

        Binary( Expression* left, Token oper, Expression* right )
            : left_{ left }
            , operator_{ oper }
            , right_{ right }
        {}
    };

    struct Grouping : VisitableExpression<Grouping>
    {
        const std::unique_ptr<Expression> expression_;

        Grouping( Expression* expression )
            : expression_{ expression }
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

        Unary( Token oper, Expression* right )
            : operator_{ oper }
            , right_{ right }
        {}
    };
} //namespace lox

#endif //LOX_EXPRESSIONS_H
