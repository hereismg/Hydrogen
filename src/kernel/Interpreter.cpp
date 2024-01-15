//
// Created by Magnesium on 2023/7/21.
//

#include "../../include/Interpreter.h"
#include "../../include/object/List.h"

namespace hdg {

    Interpreter::Interpreter(): m_globalEnvironment(new Environment) {
        init();
    }
    Interpreter::~Interpreter() = default;

    void Interpreter::init() {
        m_globalEnvironment->setSymbol("hydrogen", new String("Hello, Hydrogen_v0.3.0!"));
        m_globalEnvironment->setSymbol("whania", new String("Whania, the dragon wolf, is here!"));
        m_globalEnvironment->setSymbol("null", new Integer(0));
        m_globalEnvironment->setSymbol("true", new Integer(1));
        m_globalEnvironment->setSymbol("false", new Integer(0));
        m_globalEnvironment->setSymbol("None", new None());

        m_globalEnvironment->setSymbol("input", new BuiltInFunction(
                [this](const std::vector<Object*> &args)->Object*{
                        std::string text;
                        std::getline(std::cin, text);
                        return new String(text);
                }, "input"));

        m_globalEnvironment->setSymbol("print", new BuiltInFunction(
                [this](const std::vector<Object*> &args)->Object*{
                    std::cout << args[0]->toString();
                    return new None;
                }, "print", {"object"}));

        m_globalEnvironment->setSymbol("println", new BuiltInFunction(
                [this](const std::vector<Object*> &args)->Object*{
                    std::cout << args[0]->toString() << std::endl;
                    return new None;
                }, "println", {"object"}));

        m_globalEnvironment->setSymbol("parseInt", new BuiltInFunction(
                [this](const std::vector<Object*> &args)->Object*{
                    char * success;
                    std::string arg = args[0]->toString();
//                    if(args[0]->getClass() == "String") arg = arg.substr(1, arg.length() - 2);
                    return new Integer(std::strtoll(arg.c_str(), &success, 10));
                }, "parseInt",{"number"}));

        m_globalEnvironment->setSymbol("type", new BuiltInFunction(
                [this](const std::vector<Object*> &args)->Object*{
                    return new String(args[0]->getClass());
                }, "type", {"object"}));

        m_globalEnvironment->setSymbol("rand", new BuiltInFunction(
                [this](const std::vector<Object*> &args)->Object*{
                    return new Integer(rand() % 1000);
                }, "rand"));

        m_globalEnvironment->setSymbol("len", new BuiltInFunction(
                [this](const std::vector<Object*> &args)->Object*{
                    if (args[0]->getClass() == "List"){
                        return new Integer(((List*)args[0])->getValue().size());
                    }
                    return nullptr;
                }, "len", {"list"}));

        m_globalEnvironment->setSymbol("list", new BuiltInFunction(
                [this](const std::vector<Object*> &args)->Object*{
                    return new List;
                }, "list"));

        m_globalEnvironment->setSymbol("gcd", new BuiltInFunction(
                [this](const std::vector<Object*> &args)->Object*{
                    long long x1 = ((Integer*)args[0])->getValue(), x2 = ((Integer*)args[1])->getValue();
                    while(x2) {
                        long long temp = x2;
                        x2 = x1 % x2;
                        x1 = temp;
                    }
                    return new Integer(x1);
                }, "gcd", {"x1", "x2"}));
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