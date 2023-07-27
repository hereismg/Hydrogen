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

            try {
                Lexer lexer(text);
                lexer.run();

                Parser parser(lexer.getTokens());
                Node* tree = parser.run();

                Interpreter interpreter(tree);

//                std::cout << tree->toString() << std::endl;
                std::cout << interpreter.run() << std::endl;

                delete tree;
            }catch(Error &error){
                std::cout << error << std::endl;
                continue;
            }

        }
    }
} // hdg