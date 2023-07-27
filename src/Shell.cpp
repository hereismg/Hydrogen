//
// Created by Magnesium on 2023/7/14.
//

#include "../include/Shell.h"

namespace hdg {
    void Shell::run() {
        while(true){
            std::string text;

            std::cout << "hydrogen > ";
            std::getline(std::cin, text);

            Environment globalEnvironment("<stdin>", nullptr);
            globalEnvironment.setSymbol({
                                                {"null", Integer(0)},
                                                {"true", Integer(1)},
                                                {"false", Integer(0)}
            });

            try {
                Lexer lexer(text);
                lexer.run();

                std::cout << lexer.getTokens() << std::endl;

                Parser parser(lexer.getTokens(), &globalEnvironment);
                Node* tree = parser.run();

                Interpreter interpreter(tree, &globalEnvironment);

//                std::cout << tree->toString() << std::endl;
                std::cout << interpreter.run() << std::endl;

//                delete tree;
            }catch(Error &error){
                std::cout << error << std::endl;
                continue;
            }
        }
    }
} // hdg