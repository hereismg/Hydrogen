//
// Created by Magnesium on 2023/7/21.
//

#include "IntNode.h"

namespace hdg {
    IntNode::IntNode(int value):
        value(value){

    }

    int IntNode::getValue() {
        return value;
    }

    void IntNode::setValue(int value) {
        this->value = value;
    }

    std::string IntNode::toString() {
        return std::to_string(value);
    }
} // hdg