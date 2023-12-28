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
        explicit BuiltInFunction(std::function<Object*(const std::vector<Object*> &)> fun);
        ~BuiltInFunction() override;

        Object * parenthesis(const std::vector<Object *> &list) override;

        std::string toString() override;
        Object* copy() override;
    };

} // hdg

#endif //HDG_BUILTINFUNCTION_H
