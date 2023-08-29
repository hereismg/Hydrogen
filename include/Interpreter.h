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
    class Interpreter {
    public:
        enum Mode{
            debug,
            release,
        };

    protected:
        Environment* m_globalEnvironment;
        std::vector<std::string> m_codeStack;

        Lexer m_lexer;          ///> 词法分析器

    public:
        Interpreter();
        ~Interpreter();

        Environment* thisEnvironment();

        std::string interpret(const std::string& fPath, const std::string& code, Mode mode = release);

    protected:
        void init();
    };

} // hdg

#endif //HDG_INTERPRETER_H
