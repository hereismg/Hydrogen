//
// Created by Magnesium on 2023/8/10.
//

#ifndef HDG_FUNCOBJNODE_H
#define HDG_FUNCOBJNODE_H

#include "ObjectNode.h"
#include "../ObjAssignNode.h"

namespace hdg {

    class FuncObjNode: public ObjectNode {
    protected:
        std::vector<ObjAssignNode*> m_args;
        Node* m_body;

    public:
        FuncObjNode();
        FuncObjNode(const Position& position, Environment* parent);

        std::string toString();
        Object* interpret();
    };

} // hdg

#endif //HDG_FUNCOBJNODE_H
