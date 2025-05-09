#ifndef HDG_CLT_H
#define HDG_CLT_H

#include <string>

class Option{
public:
    Option(int argc, char *argv[]);

protected:
    std::string file_path;
    
    bool is_output_lexer_res;
};

int real_main(int argc, char *argv[]);

#endif
