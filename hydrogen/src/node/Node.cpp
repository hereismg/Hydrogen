//
// Created by Magnesium on 2023/7/19.
//

#include "../../include/node/Node.h"

namespace hdg {
    Node::Node() = default;

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

    void Node::accept(Visitor& visitor){
        std::cout << "Node::accept() is not implement!" << std::endl;
    }

    nlohmann::json Node::toJSON(){
        std::cout << "Node::toJSON() is not implement!" << std::endl;
        assert(false);
    }
} // hdg