//
// Created by Magnesium on 2023/8/4.
//

#include "../../include/object/Function.h"

#include <cassert>
#include <string>

#include "../../include/basic/Error.h"
#include "../../include/node/visitor.h"
#include "../../include/node/stmt_node.h"
#include "../../include/object/String.h"

namespace hdg {

    New_BaseFunction::New_BaseFunction(std::vector<std::string> args)
        : m_args(std::move(args)), m_envir(new New_Environment){}
    
    bool New_BaseFunction::checkArgs(const std::vector<sObject>& args){
        if (m_args.size() != args.size()){
            assert(false); // hdgftodo 构造异常信息
            return false;
        }
        else{
            return true;
        }
    }

    New_BuiltInFunction::New_BuiltInFunction(FuncInterface&& fun, std::vector<std::string>&& args)
        : New_BaseFunction(std::move(args)),
          m_fun(std::move(fun))
    {
        assert(m_fun != nullptr);
    }

    sObject New_BuiltInFunction::parenthesis(const std::vector<sObject> &args, Visitor& visitor){
        checkArgs(args);
        return m_fun(args, visitor);
    }

    std::shared_ptr<New_BuiltInFunction> New_BuiltInFunction::print_BIF(){
        auto fun = [](const std::vector<sObject> & args, Visitor & visitor)->sObject{
                std::cout << args[0]->toString() << std::endl;
                return nullptr;
            };
        
        std::vector<std::string> args = { "obj" };
        return std::make_shared<New_BuiltInFunction>(
            std::move(fun), 
            std::move(args)
        );
    }

    std::shared_ptr<New_BuiltInFunction> New_BuiltInFunction::input_BIF(){
        auto fun = [](const vector<sObject> & args, Visitor & visitor)->sObject{
                std::string txt;
                std::getline(std::cin, txt);
                return String::from(txt);
            };
        
        std::vector<std::string> args = {};
        return std::make_shared<New_BuiltInFunction>(
            std::move(fun), 
            std::move(args)
        );
    }
    
    New_DefFunction::New_DefFunction(std::vector<std::string> args, uNode body)
        : New_BaseFunction(std::move(args)), m_body(std::move(body))
    {
        assert(m_body != nullptr);
    }

    sObject New_DefFunction::parenthesis(const std::vector<sObject> &args, Visitor& visitor){
        checkArgs(args);
        
        // 压栈
        visitor.getStack().push_back(std::make_shared<New_Environment>());

        // 参数
        for (size_t i = 0; i<args.size(); i++){
            visitor.getCurrentEnvir()->setSymbol(m_args[i], args[i]);
        }

        // 执行体
        m_body->accept(visitor);

        // 弹栈
        visitor.getStack().pop_back();
        return nullptr;
    }

    std::string New_DefFunction::toString(){
        return "func";
    }

    Object* New_DefFunction::copy(){
        assert(false);
        return nullptr;
    }
} // hdg