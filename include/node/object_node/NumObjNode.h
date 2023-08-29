//
// Created by Magnesium on 2023/7/25.
//

#ifndef HDG_NUMOBJNODE_H
#define HDG_NUMOBJNODE_H

#include "ObjectNode.h"
#include "../../object/Integer.h"
#include "../../object/Float.h"

namespace hdg {

    class NumObjNode: public ObjectNode{
    protected:
        union{
            long long i;
            double f;
        }m_value;

    public:
        NumObjNode(long long value, const Position& position);
        NumObjNode(float value, const Position& position);
        NumObjNode(double value, const Position& position);
        ~NumObjNode() override;

        std::string toString() override;
        Object* interpret() override;
    };

} // hdg

#endif //HDG_NUMOBJNODE_H
