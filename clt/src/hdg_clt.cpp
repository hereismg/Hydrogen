#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include "hdg_clt.h"
#include "../../hydrogen/include/kernel/Interpreter.h"

Option::Option(int argc, char *argv[]){
    assert(argc > 0);
    assert(argv[argc] == NULL);

    // 第一个 opt 必须是 hdg 文件
    if (argv[1]){
        std::cout << "Please Entry File Path!" << std::endl;
    }
    file_path = argv[1];

    // 接下来解析各种选项
    int ptr = 2;
    while(ptr < argc){
        if (strcmp(argv[ptr], "-l") == 0){
            is_output_lexer_res = true;
        }
        ptr ++;
    }
}


int real_main(int argc, char *argv[]){
    if (argc < 2){
        std::cout << "argc < 2!" << std::endl;
    }
    std::string path(argv[1]);

    std::ifstream codeFile(path);

    if (!codeFile.is_open()){
        std::cerr << "Can't open file!" << std::endl;
        return 1;
    }

    std::string codeText;
    std::string line;
    while (std::getline(codeFile, line)){
        codeText += line + "\n";
    }

    hdg::Interpreter interpreter;
    auto res = interpreter.interpret(path, codeText);

    std::cout << res << std::endl;

    return 0;
}
