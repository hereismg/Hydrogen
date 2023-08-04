//
// Created by Magnesium on 2023/8/1.
//

#include "../../include/node/IfNode.h"

namespace hdg {
    IfNode::IfNode(const Position &position, Environment *parent):
        Node(position, new Environment("if", parent)), elseExpression(nullptr){
    }

    IfNode::~IfNode() noexcept {
        delete m_environment;
    }

    void IfNode::addBranch(Node *condition, Node *expression) {
        if (condition == nullptr){
            elseExpression = expression;
        }
        else {
            conditions.push_back(condition);
            expressions.push_back(expression);
        }
        m_position.setPosEnd(expression->thisPosition()->getPosEnd());
    }

    std::string IfNode::toString() {
        std::string result;
        result += "if " + conditions[0]->toString() + ": " + expressions[0]->toString() + " ";
        for (int i=1; i<conditions.size(); i++){
            result += "elif " + conditions[i]->toString() + ": " + expressions[i]->toString() + " ";
        }
        if (elseExpression != nullptr){
            result += "else :" + elseExpression->toString();
        }
        return result;
    }

    Object *IfNode::interpret() {
        for (int i=0; i<conditions.size(); i++){
            if (conditions[i]->interpret()->isTrue()){
                return expressions[i]->interpret();
            }
        }

        if (elseExpression!=nullptr){
            return elseExpression->interpret();
        }

        return new None();
    }
} // hdg