//
// Created by Magnesium on 2023/7/27.
//

#include "../../include/node/VariableAssignNode.h"

namespace hdg {
    VariableAssignNode::VariableAssignNode(std::string name, Node *expr, const Position &position, Environment* environment):
        Node(position, environment), m_name(std::move(name)), m_expr(expr){
    }

    VariableAssignNode::~VariableAssignNode() {
        delete m_expr;
    }

    std::string VariableAssignNode::toString() {
        std::string value = m_expr->interpret()->toString();
        return m_name + "=" + value;
    }

    Object *VariableAssignNode::interpret() {
        Object* value = m_expr->interpret();
        m_environment->addSymbol(m_name, value);
        return value->copy();
    }



} // hdg