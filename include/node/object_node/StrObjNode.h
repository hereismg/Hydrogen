//
// Created by Magnesium on 2023/8/12.
//

#ifndef HDG_STROBJNODE_H
#define HDG_STROBJNODE_H

#include "ObjectNode.h"
#include "../../object/String.h"

namespace hdg {

    class StrObjNode: public ObjectNode{
    protected:
        std::string m_value;

    public:
        StrObjNode();
        StrObjNode(std::string value, const Position& position, Environment* environment);
        ~StrObjNode() override;

        void setValue(const std::string& value);

        std::string toString() override;
        Object* interpret() override;
    };

} // hdg

#endif //HDG_STROBJNODE_H
