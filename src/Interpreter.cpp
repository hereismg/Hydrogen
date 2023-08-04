//
// Created by Magnesium on 2023/7/21.
//

#include "../include/Interpreter.h"

namespace hdg {

    Interpreter::Interpreter(Node *tree, Environment* environment):
        m_tree(tree), m_environment(environment){}


    Interpreter::~Interpreter() {
        delete m_tree;
    }

    std::string Interpreter::run() {
        if (m_tree == nullptr) return "";

        Object* value = m_tree->interpret();
        std::string result = value->toString();

        delete value;
        return result;
    }

} // hdg