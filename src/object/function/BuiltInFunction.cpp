//
// Created by Magnesium on 2023/8/30.
//

#include "../../../include/object/function/BuiltInFunction.h"

namespace hdg {
//    BuiltInFunction::BuiltInFunction() = default;

//    BuiltInFunction::BuiltInFunction(std::string name,
//                                     Environment *parent,
//                                     std::function<Object *(const std::vector<Object *>)> fun):
//                                     m_fun(std::move(fun)){
//
//    }

    Object *BuiltInFunction::print(const std::vector<Object *> &list) {
        std::cout << list[0]->toString() << std::endl;
//        return None;
    }

    BuiltInFunction::~BuiltInFunction() = default;
} // hdg