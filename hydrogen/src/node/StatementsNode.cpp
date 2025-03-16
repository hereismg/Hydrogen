//
// Created by Magnesium on 2023/8/14.
//

#include "../../include/node/StatementsNode.h"

namespace hdg {
    StatementsNode::StatementsNode() = default;

    StatementsNode::StatementsNode(const Position &position, Environment *environment) :
        Node(position, environment) {}

    StatementsNode::~StatementsNode() = default;

    void StatementsNode::append(Node *node) {
        m_statements.push_back(node);
    }

    std::string StatementsNode::toString() {
        return "StatementsNode";
    }

    Object *StatementsNode::interpret() {
        Object* result = nullptr;
        for (auto i: m_statements){
            result = i->interpret();
        }
        return result;
    }
} // hdg