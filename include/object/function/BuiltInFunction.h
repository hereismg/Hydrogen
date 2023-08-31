//
// Created by Magnesium on 2023/8/30.
//

#ifndef HDG_BUILTINFUNCTION_H
#define HDG_BUILTINFUNCTION_H

#include <functional>
#include "BaseFunction.h"

namespace hdg {

    class BuiltInFunction: BaseFunction {
    protected:
        std::function<Object*(const std::vector<Object*>)> m_fun;

    public:
        BuiltInFunction();
        BuiltInFunction(std::string name, Environment* parent, std::function<Object*(const std::vector<Object*>)> fun);
        ~BuiltInFunction() override;

        Object * parenthesis(const std::vector<Object *> &list);

        static Object* print(const std::vector<Object *> &list);
    };

} // hdg

#endif //HDG_BUILTINFUNCTION_H
