//
// Created by Magnesium on 2023/8/2.
//

#include "../../include/object/None.h"

namespace hdg {
    None::None(): Integer(0){
        m_class = "None";
    }

    std::string None::toString() {
        return "None";
    }

    Object *None::copy() {
        return new None();
    }

    Object *None::notOperator() {
        return new Integer(1);
    }
} // hdg