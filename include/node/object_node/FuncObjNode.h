//
// Created by Magnesium on 2023/8/10.
//

#ifndef HDG_FUNCOBJNODE_H
#define HDG_FUNCOBJNODE_H

#include <set>
#include "ObjectNode.h"
#include "../ObjAssignNode.h"
#include "../../object/None.h"

namespace hdg {

    class FuncObjNode: public ObjectNode {
    protected:
        std::set<ObjAssignNode*> m_args;
        Node* m_body;

    public:
        FuncObjNode();
        FuncObjNode(const Position& position, Environment* parent);

        void setArg(ObjAssignNode* arg);
        void setBody(Node* body);

        std::string toString();
        Object* interpret();
    };

} // hdg

#endif //HDG_FUNCOBJNODE_H
