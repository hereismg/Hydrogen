//
// Created by Magnesium on 2023/8/9.
//

#include "../../../include/node/object_node/ObjectNode.h"

namespace hdg {
    ObjectNode::ObjectNode() = default;

    ObjectNode::ObjectNode(const Position &position, Environment *environment) :
        Node(position, environment) {}

    ObjectNode::~ObjectNode() = default;
} // hdg