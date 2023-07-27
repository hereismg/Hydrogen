//
// Created by Magnesium on 2023/7/27.
//

#include "../../include/basic/Environment.h"

namespace hdg {
    Environment::Environment(std::string name, Environment* parent):
        m_name(std::move(name)), m_parent(parent){
    }

    Environment::~Environment() {
        for (const auto& iter: m_symbolTable){
            delete iter.second;
        }
    }

    void Environment::setName(std::string name) {
        m_name = std::move(name);
    }

    void Environment::setParent(Environment *parent) {
        m_parent = parent;
    }

    void Environment::setSymbol(const std::string& name, const Integer &value) {
        m_symbolTable[name] = new Integer(value);
    }

    void Environment::setSymbol(std::initializer_list<std::pair<std::string, const Integer &>> list) {
        for (const auto& iter: list){
            setSymbol(iter.first, iter.second);
        }
    }

    void Environment::setSymbol(const std::string& name, const Float &value) {
        m_symbolTable[name] = new Float(value);
    }

    std::string Environment::getName() {
        return m_name;
    }

    Environment *Environment::getParent() {
        return m_parent;
    }

    DataType* Environment::getSymbol(const std::string &name) {
        return m_symbolTable[name];
    }



} // hdg