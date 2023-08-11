//
// Created by Magnesium on 2023/7/25.
//

#include "../../../include/node/object_node/NumObjNode.h"

namespace hdg {
    NumObjNode::NumObjNode(long long value, const Position& position):
            Node(Position(position)), m_value({.i = value}), m_class("Integer"){}

    NumObjNode::NumObjNode(float value, const Position& position):
            Node(position), m_value({.f = value}), m_class("Float"){}

    NumObjNode::~NumObjNode() = default;

    NumObjNode::NumObjNode(double value, const Position& position):
            Node(position), m_value({.f = value}), m_class("Float"){}


    std::string NumObjNode::toString() {
        if (m_class == "Integer"){
            return std::to_string(m_value.i);
        }
        else if (m_class == "Float") {
            return std::to_string(m_value.f);
        }
        else{
            throw -1;
        }
    }

    Object *NumObjNode::interpret() {
        if (m_class == "Integer"){
            return new Integer(m_value.i);
        }
        else if (m_class == "Float") {
            return new Float(m_value.f);
        }
        else{
            throw -1;
        }
    }
} // hdg