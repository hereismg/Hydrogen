//
// Created by Magnesium on 2023/8/30.
//

#ifndef HDG_BASEFUNCTION_H
#define HDG_BASEFUNCTION_H

#include "../Object.h"
#include "../../node/ObjAssignNode.h"
#include "../../basic/Environment.h"

namespace hdg {

    class BaseFunction: public Object{
    protected:
        std::vector<ObjAssignNode*> m_args;

    public:
        BaseFunction() = default;
        explicit BaseFunction(const Position& position);
        ~BaseFunction() override = default;
    };

} // hdg

#endif //HDG_BASEFUNCTION_H
