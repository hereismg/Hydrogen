//
// Created by Magnesium on 2023/8/30.
//

#include "../../../include/object/function/BuiltInFunction.h"

namespace hdg {
//    BuiltInFunction::BuiltInFunction() {
//        m_fun = [this]()->Object*{
//            std::string text;
//            std::cin >> text;
//            return new String(text);
//        };
//    };

    BuiltInFunction::BuiltInFunction(std::function<Object*(const std::vector<Object*> &)> fun):
        m_fun(std::move(fun)){}

    Object *BuiltInFunction::parenthesis(const std::vector<Object *> &list) {
        return m_fun(list);
    }

    std::string BuiltInFunction::toString() {
        return "<BuiltInFunction>";
    }

    Object *BuiltInFunction::copy() {
        return this;
    }

    BuiltInFunction::~BuiltInFunction() = default;
} // hdg
