//
// Created by Magnesium on 2023/7/14.
//

#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "error/IllegalCharError.h"

#ifndef HDG_SHELL_H
#define HDG_SHELL_H


namespace hdg {

    class Shell {
    public:
        static void run();
    };

} // hdg

#endif //HDG_SHELL_H
