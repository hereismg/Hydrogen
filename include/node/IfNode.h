//
// Created by Magnesium on 2023/8/1.
//

#ifndef HDG_IFNODE_H
#define HDG_IFNODE_H

#include <vector>
#include "Node.h"
#include "../object/None.h"

namespace hdg {

    class IfNode: public Node{
    private:
        std::vector<Node*> conditions;
        std::vector<Node*> expressions;
        Node* elseExpression;

    public:
        IfNode(const Position& position, Environment* parent);
        ~IfNode() override;

        void addBranch(Node* condition, Node* expression);

        std::string toString() override;
        Object* interpret() override;
    };

} // hdg

#endif //HDG_IFNODE_H
