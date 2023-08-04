//
// Created by Magnesium on 2023/8/4.
//

#ifndef HDG_FUNCTION_H
#define HDG_FUNCTION_H

#include "Object.h"

namespace hdg {

    class Function: public Object{
    public:
        Function();

        std::string toString();

    };

} // hdg

#endif //HDG_FUNCTION_H
