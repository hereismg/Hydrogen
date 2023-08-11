//
// Created by Magnesium on 2023/7/27.
//

#include "../../../include/node/object_node/ObjAssignNode.h"

namespace hdg {
    ObjAssignNode::ObjAssignNode(): m_expr(nullptr){}

    ObjAssignNode::ObjAssignNode(std::string name, Node *obj, const Position &position, Environment* environment):
        Node(position, environment), m_name(std::move(name)), m_expr(obj){
    }

    ObjAssignNode::~ObjAssignNode() {
        delete m_expr;
    }

    std::string ObjAssignNode::toString() {
        std::string value = m_expr->interpret()->toString();
        return m_name + "=" + value;
    }

    Object *ObjAssignNode::interpret() {
        Object* value = m_expr->interpret();
        m_environment->setSymbol(m_name, value);
        return value->copy();
    }



} // hdg