//
// Created by Magnesium on 2023/7/27.
//

#include "../../include/basic/Environment.h"

namespace hdg {

    Environment::Environment() = default;


    Environment::Environment(Environment *parent, std::string fPath, std::string moduleName):
        m_parent(parent), m_fPath(std::move(fPath)), m_moduleName(std::move(moduleName)){}

    Environment::~Environment() {
        for (const auto& iter: m_symbolTable){
            delete iter.second;
        }
    }

    void Environment::setFilePath(const std::string &fPath) {
        m_fPath = fPath;
    }

    void Environment::setModuleName(const std::string &moduleName) {
        m_moduleName = moduleName;
    }

    void Environment::setParent(Environment *parent) {
        m_parent = parent;
    }

    /**
     * @details 目前来说，该函数存在两种模式，一种是父级模式（值为“0”），在该模式中，
     *          优先寻找父级环境中是否存在相同名称的符号，若存在，则替换父级中的符号；
     *          另一种是本地模式（值为“1”），在该模式中，直接对本地环境的符号表进行符号操作。
     * */

    void Environment::setSymbol(const std::string &name, Object *value, int mode) {
        if (mode == 0){
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
        else{
            m_symbolTable[name] = value;
        }
    }

    std::string Environment::getFilePath() {
        return m_fPath;
    }

    std::string Environment::getModuleName() {
        return m_moduleName;
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