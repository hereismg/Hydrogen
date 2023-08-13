//
// Created by Magnesium on 2023/7/14.
//

#include "../include/Shell.h"

namespace hdg {
    std::string Shell::input() {
        std::string text;

        std::cout << "hydrogen > ";
        std::getline(std::cin, text);

        return text;
    }

    void Shell::run() {
        Environment globalEnvironment("<stdin>", nullptr);
        globalEnvironment.setSymbol("hydrogen", new String("Hello, Hydrogen_v0.2.1!"));
        globalEnvironment.setSymbol({
                                            {"null",  Integer(0)},
                                            {"true",  Integer(1)},
                                            {"false", Integer(0)},
                                    });
        globalEnvironment.setSymbol("None", new None());

        while(true){
            std::string text = input();

            try {
                Lexer lexer(&text);
                lexer.run();

//                std::cout << lexer.getTokens() << std::endl;

                Parser parser(lexer.getTokens(), &globalEnvironment);
                Node* tree = parser.run();

                Interpreter interpreter(tree, &globalEnvironment);

//                std::cout << tree->toString() << std::endl;
                std::cout << interpreter.run() << std::endl;

//                delete tree;
            }catch(Error &error){
                std::cout << error.toString() << std::endl;
                continue;
            }
        }
    }

    void Shell::run(const std::string& path) {
        std::string text;
        std::ifstream stream(path, std::ios::in);

        if (!stream){
            std::cout << "file error" << std::endl;
        }

//        stream.getline(text, 40, '\n')
        while (!stream.eof()){
            std::getline(stream, text, '\n');
            std::cout << text << std::endl;
        }
    }
} // hdg