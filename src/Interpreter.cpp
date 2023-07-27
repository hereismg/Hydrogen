//
// Created by Magnesium on 2023/7/21.
//

#include "../include/Interpreter.h"

namespace hdg {

    Interpreter::Interpreter(Node *tree, Environment* environment):
        m_tree(tree), m_environment(environment){}

    std::string Interpreter::run() {
        if (m_tree == nullptr) return "";
        return m_tree->interpret()->toString();
    }
} // hdg