#ifndef HDG_CLT_H
#define HDG_CLT_H

#include <string>

class Option{
public:
    Option(int argc, char *argv[]);

    std::string getFilePath();
    bool isOutputLexerRes();

protected:
    std::string m_filePath;
    
    bool m_isOutputLexerRes;
};

/**
 * Usage: hdg_clt [Options] <file>
 * 
 * Options:
 *   1. -l | --lexer   生成词法分析的结果
 *   2. -p | --parser  生成语法分析的结果
*/
int real_main(int argc, char *argv[]);

#endif
