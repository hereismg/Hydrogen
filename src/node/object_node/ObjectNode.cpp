//
// Created by Magnesium on 2023/8/9.
//

#include "../../../include/node/object_node/ObjectNode.h"

namespace hdg {
    ObjectNode::ObjectNode() = default;

    ObjectNode::ObjectNode(std::string className, const Position &position, Environment *environment)
        : Node(position, environment), m_class(std::move(className)){}

    ObjectNode::ObjectNode(const Position &position, Environment *environment) :
        Node(position, environment) {}

    ObjectNode::~ObjectNode() = default;

    void ObjectNode::setClass(const std::string &className) {
        m_class = className;
    }

    std::string ObjectNode::getClass() {
        return m_class;
    }
} // hdg