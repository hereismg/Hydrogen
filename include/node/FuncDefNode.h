//
// Created by Magnesium on 2023/8/5.
//

#ifndef HDG_FUNCDEFNODE_H
#define HDG_FUNCDEFNODE_H

#include "Node.h"

namespace hdg {

    class FuncDefNode: public Node{
    protected:
        std::string m_name;
        Node* m_expr;

    public:
        FuncDefNode();
        FuncDefNode(std::string name, Node* expr);
    };

} // hdg

#endif //HDG_FUNCDEFNODE_H
