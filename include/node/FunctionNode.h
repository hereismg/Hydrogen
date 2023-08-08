//
// Created by Magnesium on 2023/8/5.
//

#ifndef HDG_FUNCTIONNODE_H
#define HDG_FUNCTIONNODE_H

#include "Node.h"

namespace hdg {

    class FunctionNode: public Node{
    public:
        std::string name;

        Node* expr;

    public:
        FunctionNode();
    };

} // hdg

#endif //HDG_FUNCTIONNODE_H
