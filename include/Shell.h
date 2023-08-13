//
// Created by Magnesium on 2023/7/14.
//


#ifndef HDG_SHELL_H
#define HDG_SHELL_H

#include <iostream>
#include <sstream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "error/IllegalCharError.h"
#include "basic/Environment.h"

namespace hdg {

    class Shell {
    protected:
        Mode mode;
        std::string path;

    public:
        Shell();

        [[noreturn]] void exe(int argc, char* argv[]);
        void run(const std::string& path);

        static std::string input();
        static std::string input(const std::string& path);
    };

} // hdg

#endif //HDG_SHELL_H
