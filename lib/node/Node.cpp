//
// Created by Magnesium on 2023/7/19.
//

#include "Node.h"

namespace hdg {
    Node::Node() = default;

    std::string Node::toString() {
        return "node";
    }

    std::string Node::interpret() {
        return "NONE";
    }
} // hdg