//
// Created by Magnesium on 2023/8/10.
//

#ifndef HDG_FUNCOBJNODE_H
#define HDG_FUNCOBJNODE_H

#include <set>
#include "ObjectNode.h"
#include "../ObjAssignNode.h"
#include "../../object/None.h"
#include "../../object/function/Function.h"

namespace hdg {

    class FuncObjNode: public ObjectNode {
    protected:
        std::string m_name;
        std::vector<ObjAssignNode*> m_args;
        Node* m_body{};

    public:
        FuncObjNode();
        FuncObjNode(const Position& position, Environment* parent);
        ~FuncObjNode() override;

        void setArg(ObjAssignNode* arg);
        void setBody(Node* body);
        void setName(const std::string& name);

        std::string toString() override;
        Object* interpret() override;
    };

} // hdg

#endif //HDG_FUNCOBJNODE_H
