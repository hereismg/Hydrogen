//
// Created by Magnesium on 2023/8/2.
//

#pragma once

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

