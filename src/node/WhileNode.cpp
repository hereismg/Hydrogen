//
// Created by Magnesium on 2023/8/2.
//

#include "../../include/node/WhileNode.h"

namespace hdg {
    WhileNode::WhileNode(Node *condition, Node *expression, const Position &position, Environment *parent):
            Node(position, new Environment(parent, parent->getFilePath(), parent->getModuleName())),
            m_condition(condition), m_expression(expression){}

    WhileNode::~WhileNode() {
        delete m_environment;
        delete m_condition;
        delete m_expression;
    }

    void WhileNode::setCondition(Node *condition) {
        m_condition = condition;
    }

    void WhileNode::setExpression(Node *expression) {
        m_expression = expression;
    }

    std::string WhileNode::toString() {
        return "while";
    }

    Object *WhileNode::interpret() {
        Object* result = new None();
        while(m_condition->interpret()->isTrue()){
            result = m_expression->interpret();
        }
        return result;
    }
} // hdg