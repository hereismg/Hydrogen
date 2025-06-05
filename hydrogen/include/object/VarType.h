//
// Created by Magnesium on 2025/6/5.
//

#pragma once

#include <map>
#include <utility>

#include "Object.h"
#include "../basic/Environment.h"

namespace hdg{
    class VarType : public Object {
    protected:
        VarType* m_base;

        const std::string m_class;
        New_Environment   m_envir;

    public:
        explicit VarType(std::string class_)
            : m_class(std::move(class_)), m_base(nullptr) {}

        New_Environment& refEnvir() { return m_envir; }
        const std::string& getClass() const { return m_class; }
    };
} // hdg

