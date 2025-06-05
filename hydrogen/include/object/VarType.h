//
// Created by Magnesium on 2025/6/5.
//

#ifndef HDG_VAR_TYPE_H
#define HDG_VAR_TYPE_H

#include <map>

#include "Object.h"
#include "../basic/Environment.h"

namespace hdg{
    class VarType : public Object {
    protected:
        VarType* m_base;

        const std::string m_class;
        New_Environment   m_envir;

    public:
        VarType(const std::string& m_class);

        sObject getMember(const std::string& std);
    };
} // hdg

#endif //HDG_VAR_TYPE_H
