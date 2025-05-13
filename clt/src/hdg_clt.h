#ifndef HDG_CLT_H
#define HDG_CLT_H

#include <string>

class Option{
public:
    enum Mode{
        Unknow,
        Lexer,
        Parser,
        Interpreter
    };

public:
    Option(int argc, char *argv[]);

    std::string getFilePath();
    
    Mode getOptMode();
    
    bool getOptVersion();
    
    bool getOptHelp();

protected:
    std::string m_filePath;

    // Global Options
    bool m_optVersion;
    bool m_optHelp;

    // Options
    Mode m_optMode;
};

/**
 * Usage: hdg_clt [Options] <file>
 * 
 * Global Options:
 *   1. [-v|--version]
 *   2. [-h|--help]
 * 
 * Options:
 *   1. [-m|--mode]=[lexer | parser | interpreter]
*/
int real_main(int argc, char *argv[]);

#endif
