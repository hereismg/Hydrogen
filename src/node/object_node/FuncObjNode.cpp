//
// Created by Magnesium on 2023/8/10.
//

#include "../../../include/node/object_node/FuncObjNode.h"

namespace hdg {
    FuncObjNode::FuncObjNode() {
        m_environment = new Environment("function", nullptr);
    }

    FuncObjNode::FuncObjNode(const Position &position, Environment *parent) :
        ObjectNode(position, new Environment("function", parent)) {}

    std::string FuncObjNode::toString() {
        return "FuncObjNode";
    }

    Object *FuncObjNode::interpret() {
        return nullptr;
    }
} // hdg