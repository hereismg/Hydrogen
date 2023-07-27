//
// Created by Magnesium on 2023/7/21.
//

#include <string>
#include "node/Node.h"

#ifndef HDG_INTERPRETER_H
#define HDG_INTERPRETER_H

namespace hdg {

    class Interpreter {
    private:
        Node* m_tree;

    public:
        explicit Interpreter(Node* tree);

        std::string run();
    };

} // hdg

#endif //HDG_INTERPRETER_H
