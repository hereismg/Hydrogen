#include <iostream>
#include <fstream>
#include "../../hydrogen/include/kernel/Interpreter.h"

int main(int argc, char *argv[]){
    if (argc < 2){
        std::cout << "argc < 2!" << std::endl;
    }
    std::string path(argv[1]);

    std::ifstream code_file(path);

    if (!code_file.is_open()){
        std::cerr << "Can't open file!" << std::endl;
        return 1;
    }

    std::string code_text;
    std::string line;
    while (std::getline(code_file, line)){
        code_text += line + "\n";
    }

    hdg::Interpreter interpreter;
    auto res = interpreter.interpret(path, code_text);

    std::cout << res << std::endl;

    return 0;
}
