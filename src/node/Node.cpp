//
// Created by Magnesium on 2023/7/19.
//

#include "../../include/node/Node.h"

namespace hdg {

    Node::Node(const std::string& context, int posStart, int posEnd):
            m_position(context, posStart, posEnd){
    }

    Node::Node(const Position &position) :
            m_position(position){

    }

    Node::Node(const Position &position, Environment *environment):
            m_position(position), m_environment(environment){

    }

    std::string Node::toString() {
        return "NULL";
    }

    DataType* Node::interpret() {
        return nullptr;
    }

    Position &Node::thisPosition() {
        return m_position;
    }

} // hdg