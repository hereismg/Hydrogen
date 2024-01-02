//
// Created by Magnesium on 2023/8/30.
//

#ifndef HDG_BUILTINFUNCTION_H
#define HDG_BUILTINFUNCTION_H

#include <functional>
#include "BaseFunction.h"
#include "../String.h"

namespace hdg {

    class BuiltInFunction: public BaseFunction {
    protected:
        std::function<Object*(const std::vector<Object*> &)> m_fun;

    public:
        BuiltInFunction();

        /**
         * @arg fun     函数体
         * @arg args    函数形参列表
         * */

        BuiltInFunction(std::function<Object*(const std::vector<Object*> &)> fun, std::string funName, std::vector<std::string> argsName = {});
        ~BuiltInFunction() override;

        void setFun(std::function<Object*(const std::vector<Object*> &)> fun);

        Object * parenthesis(const std::vector<Object *> &args) override;
        std::string toString() override;
        Object* copy() override;
    };

} // hdg

#endif //HDG_BUILTINFUNCTION_H
