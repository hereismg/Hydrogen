//
// Created by Magnesium on 2023/7/21.
//


#ifndef HDG_INTERPRETER_H
#define HDG_INTERPRETER_H

#include <string>
#include "Parser.h"
#include "Lexer.h"
#include "node/Node.h"
#include "basic/Environment.h"

namespace hdg {
    enum Mode{
        debug,
        release,
    };

    class Interpreter {
    protected:
        Environment* m_globalEnvironment;

    public:
        Interpreter();
        explicit Interpreter(std::string name);
        ~Interpreter();

        std::string interpret(std::string code, Mode mode = release);

    protected:
        void init();
    };

} // hdg

#endif //HDG_INTERPRETER_H
