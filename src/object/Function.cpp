//
// Created by Magnesium on 2023/8/4.
//

#include "../../include/object/Function.h"

namespace hdg {
    Function::~Function() = default;

    std::string Function::toString() {
        return "<" + m_name + ">";
    }

    Object *Function::copy() {
        return this;
    }
} // hdg