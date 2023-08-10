//
// Created by Magnesium on 2023/8/4.
//

#include "../../include/object/Function.h"

namespace hdg {
    Function::~Function() = default;

    Object *Function::parenthesis(std::initializer_list<Object *> list) {
        return Object::parenthesis(list);
    }

    std::string Function::toString() {
        return "<function>";
    }

    Object *Function::copy() {
        return this;
    }

} // hdg