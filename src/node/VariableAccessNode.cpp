//
// Created by Magnesium on 2023/7/27.
//

#include "../../include/node/VariableAccessNode.h"

namespace hdg {
    VariableAccessNode::VariableAccessNode(std::string name, const Position &position, Environment *environment):
            Node(position, environment), m_name(std::move(name)){
    }

    std::string VariableAccessNode::toString() {
        return m_name;
    }

    DataType *VariableAccessNode::interpret() {
        try{
            DataType* value = m_environment->getSymbol(m_name);
            return value;
        }
        catch (int error){
            throw RunTimeError(
                    m_position.getPosStart(),
                    m_position.getPosEnd(),
                    m_position.getContext(),
                    "'" + m_name + "' is not defind."
                    );
        }
    }
} // hdg