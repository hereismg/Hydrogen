//
// Created by Magnesium on 2023/8/30.
//

#ifndef HDG_BASEFUNCTION_H
#define HDG_BASEFUNCTION_H

#include "../Object.h"
#include "../../basic/Environment.h"

namespace hdg {

    class BaseFunction: public Object{
    protected:
        std::string m_name;
        Environment* m_environment{nullptr};

    public:
        BaseFunction(std::string name, Environment* parent);
        ~BaseFunction() override;
    };

} // hdg

#endif //HDG_BASEFUNCTION_H
