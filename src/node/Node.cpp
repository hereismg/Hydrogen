//
// Created by Magnesium on 2023/7/19.
//

#include "../../include/node/Node.h"

namespace hdg {
    Node::Node(const Position &position):
        m_position(position){
    }

    Node::Node(const Position &position, Environment *environment):
        m_position(position), m_environment(environment){
    }

    Node::~Node() = default;

    Position* Node::thisPosition() {
        return &m_position;
    }

    Environment *Node::thisEnvironment() {
        return m_environment;
    }

    std::string Node::toString() {
        return "NULL";
    }

    DataType* Node::interpret() {
        return nullptr;
    }


} // hdg