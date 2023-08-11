//
// Created by Magnesium on 2023/7/27.
//

#include "../../include/node/ObjAccessNode.h"

namespace hdg {
    ObjAccessNode::ObjAccessNode(std::string name, const Position &position, Environment *environment):
            Node(position, environment), m_name(std::move(name)){
    }

    ObjAccessNode::~ObjAccessNode() = default;

    std::string ObjAccessNode::toString() {
        return m_name;
    }

    Object *ObjAccessNode::interpret() {
        try{
            Object* value = m_environment->getSymbol(m_name);
            return value->copy();
        }
        catch (int error){
            throw RuntimeError(
                    "'" + m_name + "' is not defind.",
                    Position(
                            m_position.thisContext(),
                            m_position.getPosStart(),
                            m_position.getPosEnd())
                    );
        }
    }
} // hdg