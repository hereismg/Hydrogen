//
// Created by Magnesium on 2023/7/22.
//

#include "UnaryOperatorNode.h"

namespace hdg {

    UnaryOperatorNode::UnaryOperatorNode(std::string oper, Node* obj, const Position& position):
        Node(position), oper(std::move(oper)), obj(obj){
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

    DataType* UnaryOperatorNode::interpret() {

        DataType* value = obj->interpret();

        if (oper == TT_MINUS){
            if (value->typeName == DT_INTEGER){
                return new Integer(-((Integer*)value)->getValue());
            }
            else if (value->typeName == DT_FLOAT){
                return new Float(-((Float*)value)->getValue());
            }
        }

        return value;
    }
} // hdg