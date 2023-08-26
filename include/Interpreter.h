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
        ~Interpreter();

        /**
         * @brief:
         * 解释程序主要分为三个过程：
         *   ------->  词法分析（Lexer）  --------->  语法分析（Parser）  ------->  解释运行（Interpreter）--------->
         *    源代码                      token列表                       语法树                          解释结果
         *
         * debug 模式会打印出中间过程的 token列表 与 语法树
         * */
        std::string interpret(const std::string& fPath, std::string code, Mode mode = release);

    protected:
        void init();
    };

} // hdg

#endif //HDG_INTERPRETER_H
