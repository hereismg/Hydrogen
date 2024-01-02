//
// Created by Magnesium on 2023/7/27.
//

#ifndef HDG_OBJASSIGNNODE_H
#define HDG_OBJASSIGNNODE_H

#include "Node.h"
#include "object_node/ObjectNode.h"

namespace hdg {

    class ObjAssignNode: public Node{
    protected:
        std::string m_name;
        Node* m_expr;

    public:
        ObjAssignNode();
        ObjAssignNode(std::string name, Node* obj);
        ObjAssignNode(std::string name, Node* obj, const Position& position, Environment* environment);
        ~ObjAssignNode() override;

        void setExpr(Node* expr);
        std::string getName();

        std::string toString() override;
        Object* interpret() override;
    };

} // hdg

#endif //HDG_OBJASSIGNNODE_H
