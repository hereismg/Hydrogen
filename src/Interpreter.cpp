//
// Created by Magnesium on 2023/7/21.
//

#include "../include/Interpreter.h"

namespace hdg {

    Interpreter::Interpreter(): m_globalEnvironment(new Environment) {
        init();
    }
    Interpreter::~Interpreter() = default;

    void Interpreter::init() {
        m_globalEnvironment->setSymbol("hydrogen", new String("Hello, Hydrogen_v0.3.0!"));
        m_globalEnvironment->setSymbol("null", new Integer(0));
        m_globalEnvironment->setSymbol("true", new Integer(1));
        m_globalEnvironment->setSymbol("false", new Integer(0));
        m_globalEnvironment->setSymbol("None", new None());
        auto fun = [this](const std::vector<Object*> &list)->Object*{
            std::string text;
            std::getline(std::cin, text);
            return new String(text);
        };
        m_globalEnvironment->setSymbol("input", new BuiltInFunction(fun));
    }

    Environment *Interpreter::thisEnvironment() {
        return m_globalEnvironment;
    }

    /* 解释程序主要分为三个过程：
     *   ------->  词法分析（Lexer）  --------->  语法分析（Parser）  ------->  解释运行（Interpreter）--------->
     *    源代码                      token列表                       语法树                          解释结果
     *
     * debug 模式会打印出中间过程的 token列表 与 语法树
     * */
    std::string Interpreter::interpret(const std::string& fPath, const std::string& code, Interpreter::Mode mode) {
        m_codeStack.emplace_back(code);
        try {
            std::vector<Token> tokens = m_lexer.run(fPath, &m_codeStack.back());     ///> 注意，这里不是直接传入 code，而是先将code压入栈中，然后取栈中的code！！！
            if (mode == Mode::debug) std::cout << tokens << std::endl;                ///> 打印 tokens 列表

            Parser parser(tokens, m_globalEnvironment);
            Node* tree = parser.run();
            if (mode == Mode::debug) {
                std::cout << tree->toString() << std::endl;                            ///> 打印语法树
                std::cout << "==================================" << std::endl;
            }

            std::string result = tree->interpret()->toString();
            return result;
        }catch(Error &error){
            return error.toString();
        }
    }

} // hdg