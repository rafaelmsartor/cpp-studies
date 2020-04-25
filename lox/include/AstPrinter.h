
#ifndef LOX_ASTPRINTER_H
#define LOX_ASTPRINTER_H

#include <sstream>

#include <Expressions.h>

class AstPrinter : public lox::ExpressionVisitor
{
    std::stringstream text;

    void parenthesize( std::string const& name, lox::Expression* left, lox::Expression* right )
    {
        text << "(" << name << " ";
        left->accept( *this );
        text << " ";
        right->accept( *this );
        text << ")";
    }
    void parenthesize( std::string const& name, lox::Expression* right )
    {
        text << "(" << name << " ";
        right->accept( *this );
        text << ")";
    }

public:
    std::string print( lox::Expression* expr )
    {
        expr->accept( *this );
        return text.str();
    }

    void visit( lox::Binary* expr ) override
    {
        parenthesize( expr->operator_.lexeme
            , expr->left_.get()
            , expr->right_.get() );
    }

    void visit( lox::Grouping* expr ) override
    {
        parenthesize( "grouping"
            , expr->expression_.get() );
    }

    void visit( lox::Literal* expr ) override
    {
        text << expr->value_;
    }

    void visit( lox::Unary* expr ) override
    {
        parenthesize( expr->operator_.lexeme
            , expr->right_.get() );
    }
};

#endif
