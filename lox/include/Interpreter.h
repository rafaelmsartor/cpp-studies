//
// Created by rafael on 10/01/2020.
//

#ifndef LOX_INTERPRETER_H
#define LOX_INTERPRETER_H

#include <string>

namespace lox
{
    struct Token;

    class Interpreter
    {
        bool hadError_{ false };

    public:
        void run( std::string const& );

        void error( size_t, std::string const& );
        void error( Token const&, std::string const& );
        [[nodiscard]]bool hadError() const { return hadError_; }
        void report( size_t, std::string const&, std::string const& );
    };
}

#endif //LOX_INTERPRETER_H
