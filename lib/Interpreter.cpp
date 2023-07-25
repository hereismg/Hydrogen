//
// Created by Magnesium on 2023/7/21.
//

#include "Interpreter.h"

namespace hdg {

    Interpreter::Interpreter(Node *tree):
        tree(tree){}

    std::string Interpreter::run() {
        if (tree == nullptr) return "";
        return tree->interpret()->toString();
    }
} // hdg