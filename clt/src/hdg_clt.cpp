#include "hdg_clt.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>

#include "../../hydrogen/include/kernel/Interpreter.h"
#include "../../hydrogen/include/kernel/Parser.h"
#include "../../hydrogen/include/node/visitor.h"

bool startsWith(const char * str, const char * prefix){
    for (int i=0; str[i] != '\0' && prefix[i] != '\0'; i++){
        if (str[i] != prefix[i]){
            return false;
        }
    }
    return true;
}

bool endWith(const char * str, const char * suffix){
    int strLen = strlen(str);
    int suffixLen = strlen(suffix);

    for (int i=0; i < strLen && i < suffixLen; i++){
        if (str[strLen - i - 1] != suffix[suffixLen - i - 1]){
            return false;
        }
    }
    return true;
}

Option::Option(int argc, char *argv[]) {
    assert(argc > 0);
    assert(argv[argc] == NULL);

    // 1. 设置默认值
    m_optVersion = false;
    m_optHelp    = false;
    m_optMode    = Interpreter;

    // 接下来解析各种选项

    for (int ptr = 1; ptr < argc - 1; ptr ++) {
        if (startsWith(argv[ptr], "-m") || startsWith(argv[ptr], "--mode")) {
            if (endWith(argv[ptr], "lexer")) m_optMode = Lexer;
            else if (endWith(argv[ptr], "parser")) m_optMode = Parser;
            else if (endWith(argv[ptr], "interpreter")) m_optMode = Interpreter;
            else if (endWith(argv[ptr], "JSON")) m_optMode = JSON;
            else m_optMode = Unknow;
        }
    }

    m_filePath = argv[argc-1];
}

std::string Option::getFilePath(){
    return m_filePath;
}

Option::Mode Option::getOptMode(){
    return m_optMode;
}

bool Option::getOptHelp(){
    return m_optHelp;
}

bool Option::getOptVersion(){
    return m_optVersion;
}

void printUsage(){
    std::cout << R"(Usage: hdg_clt [Global Options] [Options] <file>

Global Options:
  1. [-v|--version]
  2. [-h|--help]
 
Options:
  1. [-m|--mode]=[lexer | parser | interpreter | JSON])" << std::endl;
}

int real_main(int argc, char *argv[]){
    if (argc < 2){
        printUsage();
        // std::cout << "argc < 2!" << std::endl;
        return 1;
    }
    Option opt(argc, argv);

    // Golbal Opttion

    // 解析文本
    std::ifstream codeFile(opt.getFilePath());
    if (!codeFile.is_open()){
        std::cerr << "Can't open file!" << std::endl;
        return 1;
    }
    std::string codeText;
    std::string line;
    while (std::getline(codeFile, line)){
        codeText += line + "\n";
    }
    
    // 模式
    auto mode = opt.getOptMode();
    switch (mode){
    case Option::Mode::Lexer:{
        
        break;
    }
    case Option::Mode::Parser:{
        break;
    }
    case Option::Mode::Interpreter:{
        hdg::Lexer lexer;

        auto tokens = lexer.run("<stdin>", &codeText);

        hdg::Environment envir;
        hdg::Parser parser(tokens, &envir);
        hdg::uNode ast = parser.new_ExeUnit();

        hdg::InterpreterVisitor visitor;

        ast->accept(visitor);

        auto res = visitor.getResult();
        
        std::cout << res->toString() << std::endl;

        break;
    }
    case Option::Mode::JSON:{
        hdg::Lexer lexer;

        auto tokens = lexer.run("<stdin>", &codeText);

        hdg::Environment envir;
        hdg::Parser parser(tokens, &envir);
        hdg::uNode ast = parser.new_ExeUnit();

        std::cout << ast->toJSON().dump(4) << std::endl;

        break;
    }
    default:{
        
        break;
    }
    }


    return 0;
}
