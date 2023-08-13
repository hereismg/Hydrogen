//
// Created by Magnesium on 2023/7/14.
//


#ifndef HDG_SHELL_H
#define HDG_SHELL_H

#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "error/IllegalCharError.h"
#include "basic/Environment.h"

namespace hdg {

    class Shell {
    public:
        static std::string input();
        static void run();
        static void run(const std::string& path);
    };

} // hdg

#endif //HDG_SHELL_H
