//
// Created by Magnesium on 2023/7/27.
//

#ifndef HDG_OBJACCESSNODE_H
#define HDG_OBJACCESSNODE_H

#include "Node.h"

namespace hdg {

    class ObjAccessNode: public Node{
    protected:
        std::string m_name;

    public:
        ObjAccessNode(std::string name, const Position& position, Environment* environment);
        ~ObjAccessNode() override;

        std::string toString() override;
        Object* interpret() override;
    };

} // hdg

#endif //HDG_OBJACCESSNODE_H
