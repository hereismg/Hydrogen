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

    void Environment::addSymbol(const std::string &name, Object *value) {
        Environment* iter = this;
        std::stack<Environment*> stack;
        while (iter != nullptr) {
            stack.push(iter);
            iter = iter->m_parent;
        }

        while (!stack.empty()){
            iter = stack.top();
            stack.pop();
            if (iter->m_symbolTable.find(name) != iter->m_symbolTable.end()) break;
        }

        iter->m_symbolTable[name] = value;
    }

    void Environment::addLocalSymbol(const std::string &name, hdg::Object *value) {
        m_symbolTable[name] = value;
    }

    void Environment::addSymbol(const std::string& name, const Integer &value) {
        addSymbol(name, new Integer(value));
    }

    void Environment::addSymbol(std::initializer_list<std::pair<std::string, const Integer &>> list) {
        for (const auto& iter: list){
            addSymbol(iter.first, iter.second);
        }
    }

    void Environment::addSymbol(const std::string& name, const Float &value) {
        addSymbol(name, new Float(value));
    }

    std::string Environment::getName() {
        return m_name;
    }

    Environment *Environment::getParent() {
        return m_parent;
    }

    Object* Environment::getSymbol(const std::string &name) {
        if (m_symbolTable.find(name) != m_symbolTable.end()){
            return m_symbolTable[name];
        }
        else {
            if (m_parent == nullptr) throw -1;
            return m_parent->getSymbol(name);
        }
    }
} // hdg