//
// Created by Magnesium on 2023/7/25.
//

#include "../../include/node/NumberNode.h"

namespace hdg {
    NumberNode::NumberNode(int value, const Position& position):
            Node(Position(position)){
        m_value = new Integer(value);
    }

    NumberNode::NumberNode(float value, const Position& position):
            Node(position){
        m_value = new Float(value);
    }

    NumberNode::~NumberNode() {
        delete m_value;
    }

    NumberNode::NumberNode(double value, const Position& position):
            Node(position){
        m_value = new Float(value);
    }


    std::string NumberNode::toString() {
        return m_value->toString();
    }

    Object *NumberNode::interpret() {
        return m_value->copy();
    }
} // hdg