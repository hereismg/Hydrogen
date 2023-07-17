//
// Created by Magnesium on 2023/7/14.
//

#include "Shell.h"

namespace hdg {
    void Shell::run() {
        while(true){
            std::string text;

            std::cout << "hydrogen > ";
            std::getline(std::cin, text);

            try {
                Lexer lexer(text);
                Parser parser(lexer.getTokens());

                lexer.run();

                std::cout << lexer.getTokens() << std::endl;
            }catch(Error &error){
                std::cout << error << std::endl;
                continue;
            }

        }
    }
} // hdg