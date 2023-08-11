//
// Created by Magnesium on 2023/8/10.
//

#include "../../../include/node/object_node/FuncObjNode.h"

namespace hdg {
    FuncObjNode::FuncObjNode():
        m_name("anonymous"){
        m_environment = new Environment("function", nullptr);
    }

    FuncObjNode::FuncObjNode(const Position &position, Environment *parent) :
        ObjectNode(position, new Environment("function", parent)), m_name("anonymous") {}

    void FuncObjNode::setArg(ObjAssignNode *arg) {
        m_args.push_back(arg);
    }

    void FuncObjNode::setBody(Node *body) {
        m_body = body;
    }

    void FuncObjNode::setName(const std::string& name) {
        m_name = name;
    }

    std::string FuncObjNode::toString() {
        return m_name;
    }

    Object *FuncObjNode::interpret() {
        return new Function(m_name, m_args, m_environment, m_body, m_position);
    }
} // hdg