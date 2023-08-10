//
// Created by Magnesium on 2023/7/27.
//

#ifndef HDG_OBJASSIGNNODE_H
#define HDG_OBJASSIGNNODE_H

#include "Node.h"
#include "ObjectNode.h"

namespace hdg {

    class ObjAssignNode: public Node{
    protected:
        std::string m_name;
        ObjectNode* m_obj;

    public:
        ObjAssignNode();
        ObjAssignNode(std::string name, ObjectNode* obj, const Position& position, Environment* environment);
        ~ObjAssignNode() override;

        std::string toString() override;
        Object* interpret() override;
    }
    ;

} // hdg

#endif //HDG_OBJASSIGNNODE_H
