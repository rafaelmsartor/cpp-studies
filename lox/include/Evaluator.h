
#ifndef LOX_EVALUATOR_H
#define LOX_EVALUATOR_H

#include <Expressions.h>
#include <Token.h>

namespace lox
{
    class Evaluator : public ExpressionVisitor
    {
        literal_t value_;

        void visit( lox::Literal* expression ) override;
        void visit( lox::Grouping* expression ) override;
        void visit( lox::Unary* expression ) override;
        void visit( lox::Binary* expression ) override;

        bool isTruthy( literal_t value ) const;

    public:

        literal_t evaluate( lox::Expression* expression );
    };
}


#endif