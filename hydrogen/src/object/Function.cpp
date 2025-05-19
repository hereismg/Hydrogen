//
// Created by Magnesium on 2023/8/4.
//

#include "../../include/object/Function.h"

#include <cassert>

#include "../../include/basic/Error.h"

namespace hdg {
    Function::Function() {
        setClass("Function");
    }

    Function::Function(std::string name, std::vector<ObjAssignNode*>args, Environment* environment, Node* body, const Position& position):
            m_environment(environment), m_body(body){
        setClass("Function");
        m_args = std::move(args);
        m_funName = std::move(name);
    }

    Function::~Function() = default;

    Object *Function::parenthesis(const std::vector<Object*>& args) {
        checkArgs(args);

        for (size_t i=0; i<m_args.size(); i++){
            m_environment->setSymbol(m_args[i]->getName(), args[i], Environment::Mode::LOCAL);
        }

        Object* result = m_body->interpret();
        return result;
    }

    std::string Function::toString() {
        return "<" + m_funName + ">";
    }

    Object *Function::copy() {
        return this;
    }

    BuiltInFunction::BuiltInFunction() {
        setClass("BuiltInFunction");
    }

    BuiltInFunction::BuiltInFunction(
            std::function<Object*(const std::vector<Object*> &)> fun,
            std::string funName,
            std::vector<std::string> argsName
    ):
            m_fun(std::move(fun))
    {
        setClass("BuiltInFunction");
        m_funName = std::move(funName);
        for (auto name : argsName)
            m_args.push_back(new ObjAssignNode(name, nullptr));
    }

    BuiltInFunction::~BuiltInFunction() = default;

    void BuiltInFunction::setFun(std::function<Object*(const std::vector<Object *> &)> fun) {
        m_fun = std::move(fun);
    }

    Object *BuiltInFunction::parenthesis(const std::vector<Object *> &args) {
        checkArgs(args);
        return m_fun(args);
    }

    std::string BuiltInFunction::toString() {
        return "<BuiltInFunction>";
    }

    Object *BuiltInFunction::copy() {
        return this;
    }

    BaseFunction::BaseFunction(std::string name, const Position& position):
            Object("BaseFunction", position), m_funName(std::move(name)){}

    bool BaseFunction::checkArgs(const std::vector<Object *> &args) {
        if (m_args.size() != args.size()){
            // 参数不匹配，下面开始构建异常信息
            std::stringstream detail;
            detail << m_funName << "(): " << std::to_string(m_args.size());

            if (m_args.size()<=1) detail << " argument required, ";
            else detail << " arguments required, ";

            detail << "but " << std::to_string(args.size()) << " received.";

            // 抛出异常
            throw RuntimeError(detail.str());
        }
        return true;
    }

    New_BaseFunction::New_BaseFunction(std::vector<std::string> args): m_args(std::move(args)){}
    
    bool New_BaseFunction::checkArgs(const std::vector<sObject>& args){
        if (m_args.size() != args.size()){
            assert(false); // hdgftodo 构造异常信息
        }
        else{
            return true;
        }
    }

    New_DefFunction::New_DefFunction(std::vector<std::string> args, uNode&& body)
        : New_BaseFunction(std::move(args)), m_body(std::move(body))
    {
        assert(m_body != nullptr);
    }

    sObject New_DefFunction::parenthesis(const std::vector<sObject> &args){
        
        return nullptr;
    }

    std::string New_DefFunction::toString(){
        return "func";
    }

    Object* New_DefFunction::copy(){
        assert(false);
    }
} // hdg