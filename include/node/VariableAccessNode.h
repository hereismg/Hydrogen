//
// Created by Magnesium on 2023/7/27.
//

#ifndef HDG_VARIABLEACCESSNODE_H
#define HDG_VARIABLEACCESSNODE_H

#include "Node.h"

namespace hdg {

    class VariableAccessNode: public Node{
    private:
        std::string m_name;
        Environment* m_environment{};

    public:
        VariableAccessNode(std::string name, const Position& position, Environment* environment);

        std::string toString() override;
        DataType* interpret() override;
    };

} // hdg

#endif //HDG_VARIABLEACCESSNODE_H
