//
// Created by Magnesium on 2023/8/1.
//

#include "IfNode.h"

namespace hdg {
    IfNode::IfNode(const Position &position, Environment *environment):
        Node(position, environment), elseExpression(nullptr){
    }

    void IfNode::addBranch(Node *condition, Node *expression) {
        if (condition == nullptr){
            elseExpression = expression;
        }
        else {
            conditions.push_back(condition);
            expressions.push_back(expression);
        }
    }

    std::string IfNode::toString() {
        std::string result;
        result += "if " + conditions[0]->toString() + ": " + expressions[0]->toString() + " ";
        for (int i=1; i<conditions.size(); i++){
            result += "elif " + conditions[0]->toString() + ": " + expressions[0]->toString() + " ";
        }
        if (elseExpression != nullptr){
            result += "else :" + elseExpression->toString();
        }
        return result;
    }

    DataType *IfNode::interpret() {
        for (int i=0; i<conditions.size(); i++){
            if (conditions[i]->interpret()->isTrue()){
                return expressions[i]->interpret();
            }
        }

        if (elseExpression!=nullptr){
            return elseExpression->interpret();
        }

        return nullptr;
    }
} // hdg