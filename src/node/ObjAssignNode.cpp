//
// Created by Magnesium on 2023/7/27.
//

#include "../../include/node/ObjAssignNode.h"

namespace hdg {
    ObjAssignNode::ObjAssignNode(): m_obj(nullptr){}

    ObjAssignNode::ObjAssignNode(std::string name, ObjectNode *obj, const Position &position, Environment* environment):
        Node(position, environment), m_name(std::move(name)), m_obj(obj){
    }

    ObjAssignNode::~ObjAssignNode() {
        delete m_obj;
    }

    std::string ObjAssignNode::toString() {
        std::string value = m_obj->interpret()->toString();
        return m_name + "=" + value;
    }

    Object *ObjAssignNode::interpret() {
        Object* value = m_obj->interpret();
        m_environment->addSymbol(m_name, value);
        return value->copy();
    }



} // hdg