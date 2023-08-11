//
// Created by Magnesium on 2023/7/27.
//

#ifndef HDG_ENVIRONMENT_H
#define HDG_ENVIRONMENT_H

#include <map>
#include <string>
#include <initializer_list>
#include <stack>
#include "../object/Object.h"
#include "../object/Integer.h"
#include "../object/Float.h"

namespace hdg {
    typedef std::map<std::string, Object*> SymbolTable;

    class Environment {
    protected:
        std::string m_name;
        Environment* m_parent;
        SymbolTable m_symbolTable;

    public:
        Environment(std::string name, Environment* parent);
        ~Environment();

        void setName(std::string name);
        void setParent(Environment* parent);
        void setSymbol(const std::string& name, Object* value);
        void setLocalSymbol(const std::string& name, Object* value);

        void setSymbol(const std::string& name, const Integer& value);
        void setSymbol(std::initializer_list<std::pair<std::string, const Integer&>> list);
        void setSymbol(const std::string& name, const Float& value);

        std::string getName();
        Environment* getParent();
        Object* getSymbol(const std::string& name);
    };

} // hdg

#endif //HDG_ENVIRONMENT_H
