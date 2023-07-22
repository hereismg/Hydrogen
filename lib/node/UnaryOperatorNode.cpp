//
// Created by Magnesium on 2023/7/22.
//

#include "UnaryOperatorNode.h"

namespace hdg {
    UnaryOperatorNode::UnaryOperatorNode(std::string oper):
        oper(std::move(oper)), obj(nullptr){
    }
    UnaryOperatorNode::UnaryOperatorNode(std::string oper, Node* obj):
    oper(std::move(oper)), obj(obj){
    }

    void UnaryOperatorNode::setOperator(std::string oper){
        this->oper = std::move(oper);
    }
    void UnaryOperatorNode::setObject(Node* obj){
        this->obj = obj;
    }

    std::string UnaryOperatorNode::getOperator(){
        return oper;
    }
    Node* UnaryOperatorNode::getObject(){
        return obj;
    }

    std::string UnaryOperatorNode::toString() {
        return "(" + oper + ", " + obj->toString() + ")";
    }

    std::string UnaryOperatorNode::interpret() {
        if (obj == nullptr) return "NONE";

        int value = atoi(obj->interpret().c_str());

        if (oper == TT_MINUS){
            value = -value;
        }
        return std::to_string(value);
    }
} // hdg