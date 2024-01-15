//
// Created by Magnesium on 2023/7/21.
//


#ifndef HDG_INTERPRETER_H
#define HDG_INTERPRETER_H

#include <string>
#include <list>
#include <cmath>
#include "Parser.h"
#include "Lexer.h"
#include "node/Node.h"
#include "basic/Environment.h"
#include "object/function/BuiltInFunction.h"
#include "object/Float.h"

namespace hdg {
    class Interpreter {
    public:
        enum Mode{
            debug,
            release,
        };

    protected:
        Environment* m_globalEnvironment;
        std::list<std::string> m_codeStack;

        Lexer m_lexer;          ///> 词法分析器

    public:
        Interpreter();
        ~Interpreter();

        Environment* thisEnvironment();

        /**
         * 传入 hdg 代码，解释器对其解释并运行，返回一个字符串
         * @param fPath 代码的原文件
         * */
        std::string interpret(const std::string& fPath, const std::string& code, Interpreter::Mode mode = release);

    protected:
        void init();
    };

} // hdg

#endif //HDG_INTERPRETER_H
