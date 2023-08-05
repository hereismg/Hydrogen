//
// Created by Magnesium on 2023/8/4.
//

#ifndef HDG_FUNCTION_H
#define HDG_FUNCTION_H

#include <vector>
#include "Object.h"
#include "../basic/Token.h"

namespace hdg {

    class Function: public Object{
    private:
        std::string name;
        std::vector<std::string> formals;

    public:
        Function();

        std::string toString() override;
        Object* copy() override;
    };

} // hdg

#endif //HDG_FUNCTION_H
