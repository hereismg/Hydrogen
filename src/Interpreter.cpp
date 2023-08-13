//
// Created by Magnesium on 2023/7/21.
//

#include "../include/Interpreter.h"

namespace hdg {

    Interpreter::Interpreter(): m_globalEnvironment(new Environment("<stdin>", nullptr)) {
        init();
    }
    Interpreter::Interpreter(std::string name): m_globalEnvironment(new Environment(std::move(name), nullptr)) {
        init();
    }
    Interpreter::~Interpreter() = default;

    void Interpreter::init() {
        m_globalEnvironment->setSymbol("hydrogen", new String("Hello, Hydrogen_v0.2.1!"));
        m_globalEnvironment->setSymbol({
                                            {"null",  Integer(0)},
                                            {"true",  Integer(1)},
                                            {"false", Integer(0)},
                                    });
        m_globalEnvironment->setSymbol("None", new None());
    }

    /* 解释程序主要分为三个过程：
     *   ------->  词法分析（Lexer）  --------->  语法分析（Parser）  ------->  解释运行（Interpreter）--------->
     *    源代码                      token列表                       语法树                          解释结果
     *
     * debug 模式会打印出中间过程的 token列表 与 语法树
     * */
    std::string Interpreter::interpret(std::string code, Mode mode) {
        try {
            Lexer lexer(&code);
            lexer.run();
            if (mode == debug) std::cout << lexer.getTokens() << std::endl;

            Parser parser(lexer.getTokens(), m_globalEnvironment);
            Node* tree = parser.run();
            if (mode == debug) std::cout << tree->toString() << std::endl;

            std::string result = tree->interpret()->toString();
            return result;
        }catch(Error &error){
            return error.toString();
        }
    }

} // hdg