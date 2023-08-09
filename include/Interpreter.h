//
// Created by Magnesium on 2023/7/21.
//


#ifndef HDG_INTERPRETER_H
#define HDG_INTERPRETER_H

#include <string>
#include "node/Node.h"
#include "basic/Environment.h"

namespace hdg {

    class Interpreter {
    protected:
        Node* m_tree;
        Environment* m_environment;


    public:
        Interpreter(Node* tree, Environment* environment);
        ~Interpreter();

        std::string run();
    };

} // hdg

#endif //HDG_INTERPRETER_H
