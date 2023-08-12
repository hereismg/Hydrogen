//
// Created by Magnesium on 2023/8/12.
//

#include "../../../include/node/object_node/StrObjNode.h"

namespace hdg {
    StrObjNode::StrObjNode() {
        setClass("String");
    }

    StrObjNode::StrObjNode(std::string value, const Position &position, Environment *environment) :
        ObjectNode("String", position, environment), m_value(std::move(value)) {}

    StrObjNode::~StrObjNode() = default;

    void StrObjNode::setValue(const std::string& value) {
        m_value = value;
    }

    std::string StrObjNode::toString() {
        return "StrObjNode(\"" + m_value + "\"";
    }

    Object *StrObjNode::interpret() {
        return new String(m_value, m_position);
    }
} // hdg