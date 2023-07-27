//
// Created by Magnesium on 2023/7/27.
//

#ifndef HDG_ENVIRONMENT_H
#define HDG_ENVIRONMENT_H

#include <map>
#include <string>
#include <initializer_list>
#include "../data_type/DataType.h"
#include "../data_type/Integer.h"
#include "../data_type/Float.h"

namespace hdg {
    typedef std::map<std::string, DataType*> SymbolTable;

    class Environment {
    private:
        std::string m_name;
        Environment* m_parent;
        SymbolTable m_symbolTable;

    public:
        Environment(std::string name, Environment* parent);
        ~Environment();

        void setName(std::string name);
        void setParent(Environment* parent);
        void setSymbol(const std::string& name, const Integer& value);
        void setSymbol(std::initializer_list<std::pair<std::string, const Integer&>> list);
        void setSymbol(const std::string& name, const Float& value);

        std::string getName();
        Environment* getParent();
        DataType* getSymbol(const std::string& name);
    };

} // hdg

#endif //HDG_ENVIRONMENT_H
