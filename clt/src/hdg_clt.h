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

int real_main(int argc, char *argv[]);

#endif
