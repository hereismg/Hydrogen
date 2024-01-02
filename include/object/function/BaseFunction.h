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
        std::string m_funName;

    public:
        BaseFunction() = default;
        BaseFunction(std::string name, const Position& position);
        ~BaseFunction() override = default;

        /**
         * @details     检查传入的实参列表是否与函数体的参数列表匹配。
         * @arg args    传入的实参列表
         * @return      如果传入的实参满足函数的要求，那么返回 true；反之抛出 RuntimeError。
         * */

        bool checkArgs(const std::vector<Object *> &args);
    };

} // hdg

#endif //HDG_BASEFUNCTION_H
