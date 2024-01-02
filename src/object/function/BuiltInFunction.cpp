//
// Created by Magnesium on 2023/8/30.
//

#include "../../../include/object/function/BuiltInFunction.h"

namespace hdg {
    BuiltInFunction::BuiltInFunction() {
        setClass("BuiltInFunction");
    }

    BuiltInFunction::BuiltInFunction(
            std::function<Object*(const std::vector<Object*> &)> fun,
            std::string funName,
            std::vector<std::string> argsName
            ):
        m_fun(std::move(fun))
    {
        setClass("BuiltInFunction");
        m_funName = std::move(funName);
        for (auto name : argsName)
            m_args.push_back(new ObjAssignNode(name, nullptr));
    }

    BuiltInFunction::~BuiltInFunction() = default;

    void BuiltInFunction::setFun(std::function<Object*(const std::vector<Object *> &)> fun) {
        m_fun = std::move(fun);
    }

    Object *BuiltInFunction::parenthesis(const std::vector<Object *> &args) {
        checkArgs(args);
        return m_fun(args);
    }

    std::string BuiltInFunction::toString() {
        return "<BuiltInFunction>";
    }

    Object *BuiltInFunction::copy() {
        return this;
    }
} // hdg
