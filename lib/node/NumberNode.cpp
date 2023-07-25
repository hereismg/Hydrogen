//
// Created by Magnesium on 2023/7/25.
//

#include "NumberNode.h"

namespace hdg {
    NumberNode::NumberNode(int value) {
        this->value = new Integer(value);
    }

    NumberNode::NumberNode(float value) {
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