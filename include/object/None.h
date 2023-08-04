//
// Created by Magnesium on 2023/8/2.
//

#ifndef HDG_NONE_H
#define HDG_NONE_H

#include "Object.h"
#include "Integer.h"

namespace hdg {

    class None: public Object{
    public:
        None();

        Object* notOperator() override;

        std::string toString() override;
        Object* copy() override;
    };

} // hdg

#endif //HDG_NONE_H
