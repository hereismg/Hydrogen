//
// Created by Magnesium on 2023/7/25.
//

#include "../../../include/node/object_node/NumObjNode.h"

namespace hdg {
    NumObjNode::NumObjNode(long long value, const Position& position):
        ObjectNode("Integer", position, nullptr), m_value({.i = value}){}

    NumObjNode::NumObjNode(float value, const Position& position):
        ObjectNode("Float", position, nullptr), m_value({.f = value}){}

    NumObjNode::NumObjNode(double value, const Position& position):
        ObjectNode("Float", position, nullptr), m_value({.f = value}){}

    NumObjNode::~NumObjNode() = default;


    std::string NumObjNode::toString() {
        if (m_class == "Integer"){
            return std::to_string(m_value.i);
        }
        else if (m_class == "Float") {
            return std::to_string(m_value.f);
        }
        else{
            std::cout << "NumObjNode::toString: Unknown class type." << std::endl;
        }
    }

    Object *NumObjNode::interpret() {
        if (m_class == "Integer"){
            return new Integer(m_value.i, m_position);
        }
        else if (m_class == "Float") {
            return new Float(m_value.f, m_position);
        }
        else{
            std::cout << "NumObjNode::interpret: Unknown class type." << std::endl;
        }
    }
} // hdg