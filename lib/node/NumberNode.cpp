//
// Created by Magnesium on 2023/7/25.
//

#include "NumberNode.h"

namespace hdg {
    NumberNode::NumberNode(int value, const Position& position):
            Node(position){
        this->value = new Integer(value);
    }

    NumberNode::NumberNode(float value, const Position& position):
            Node(position){
        this->value = new Float(value);
    }

    NumberNode::NumberNode(double value, const Position &position):
            Node(position){
        this->value = new Float(value);
    }

    NumberNode::~NumberNode() {
        delete value;
    }

    std::string NumberNode::toString() {
        return value->toString();
    }

    DataType *NumberNode::interpret() {
        return value;
    }
} // hdg