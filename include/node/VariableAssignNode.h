//
// Created by Magnesium on 2023/7/27.
//

#ifndef HDG_VARIABLEASSIGNNODE_H
#define HDG_VARIABLEASSIGNNODE_H

#include "Node.h"

namespace hdg {

    class VariableAssignNode: public Node{
    private:
        std::string m_name;
        Node* m_expr;

    public:
        VariableAssignNode(std::string name, Node* expr, const Position& position, Environment* environment);
        ~VariableAssignNode() override;

        std::string toString() override;
        Object* interpret() override;
    };

} // hdg

#endif //HDG_VARIABLEASSIGNNODE_H
