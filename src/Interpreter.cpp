//
// Created by Magnesium on 2023/7/21.
//

#include "../include/Interpreter.h"

namespace hdg {

    Interpreter::Interpreter(): m_globalEnvironment(new Environment("<main>", nullptr)) {
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

    std::string Interpreter::interpret(const std::string& fPath, std::string code, Mode mode) {
        try {
            Lexer lexer(fPath, &code);
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