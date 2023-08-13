//
// Created by Magnesium on 2023/7/14.
//

#include "../include/Shell.h"

namespace hdg {
    Shell::Shell(): mode(release) {}

    [[noreturn]] void Shell::exe(int argc, char* argv[]) {
        int pos = 1;
        for (int i=1; i<argc; i++){
            if (std::string(argv[i]) == "-debug"){
                mode = debug;
            }
            else if(std::string(argv[i]) == "-release") {
                mode = release;
            }
            else{
                path = argv[i];
            }
        }

        Interpreter interpreter;
        std::string code;
        if (path.empty()){
            while(true){
                code = input();
                std::cout << interpreter.interpret(code, mode) << std::endl;
            }
        }
        else{
            code = input(path);
            interpreter.interpret(code, mode);
        }
    }

    std::string Shell::input() {
        std::string text;

        std::cout << "hydrogen > ";
        std::getline(std::cin, text);

        return text;
    }

    std::string Shell::input(const std::string& path){
        std::ifstream file(path);
        if (!file) std::cout << "file error: " << path << std::endl;

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
} // hdg