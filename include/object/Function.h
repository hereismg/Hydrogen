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
    protected:
        std::string m_name;
        std::vector<std::string> m_formals;

    public:
        ~Function() override;

        std::string toString() override;
        Object* copy() override;
    };

} // hdg

#endif //HDG_FUNCTION_H
