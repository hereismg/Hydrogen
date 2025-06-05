//
// Created by Magnesium on 2023/8/4.
//
#pragma once

#include <functional>
#include <memory>

#include "../node/ObjAssignNode.h"
#include "../node/Node.h"


namespace hdg {

    class BaseFunction: public Object{
    protected:
        std::vector<ObjAssignNode*> m_args;
        std::string m_funName;

    public:
        BaseFunction() = default;
        BaseFunction(std::string name, const Position& position);
        ~BaseFunction() override = default;

        /**
         * @details     检查传入的实参列表是否与函数体的参数列表匹配。
         * @arg args    传入的实参列表
         * @return      如果传入的实参满足函数的要求，那么返回 true；反之抛出 RuntimeError。
         * */

        bool checkArgs(const std::vector<Object *> &args);
    };


    class Function: public BaseFunction{
    protected:
        Environment* m_environment{nullptr};
        Node* m_body{nullptr};

    public:
        Function();
        Function(std::string name, std::vector<ObjAssignNode*>args, Environment* environment, Node* body, const Position& position);
        ~Function() override;

        Object* parenthesis(const std::vector<Object*>& args) override;

        std::string toString() override;
        Object* copy() override;
    };

    class BuiltInFunction: public BaseFunction {
    protected:
        std::function<Object*(const std::vector<Object*> &)> m_fun;

    public:
        BuiltInFunction();

        /**
         * @arg fun     函数体
         * @arg args    函数形参列表
         * */

        BuiltInFunction(std::function<Object*(const std::vector<Object*> &)> fun, std::string funName, std::vector<std::string> argsName = {});
        ~BuiltInFunction() override;

        void setFun(std::function<Object*(const std::vector<Object*> &)> fun);

        Object * parenthesis(const std::vector<Object *> &args) override;
        std::string toString() override;
        Object* copy() override;
    };

    class New_BaseFunction: public Object{
    protected:
        std::vector<std::string> m_args;
        std::shared_ptr<New_Environment> m_envir;
    
    public:
        New_BaseFunction(std::vector<std::string> args);

        bool checkArgs(const std::vector<sObject> &args);
        
        virtual std::string toString() = 0;
        virtual Object* copy() = 0;
    };

    
    typedef std::function<sObject(const std::vector<sObject> &, Visitor &)> FuncInterface;
    class New_BuiltInFunction: public New_BaseFunction {
    private:
        FuncInterface m_fun;

    public:
        New_BuiltInFunction(FuncInterface&& fun, std::vector<std::string>&& args);

        sObject parenthesis(const std::vector<sObject> &args, Visitor& visitor) override;
    
        std::string toString() override { return "BuiltInFunc"; }
        Object* copy() override { assert(false); return nullptr; }
    
        static std::shared_ptr<New_BuiltInFunction> print_BIF();
        static std::shared_ptr<New_BuiltInFunction> input_BIF();
        // static std::shared_ptr<New_BuiltInFunction> parseInt_BIF();
        // static std::shared_ptr<New_BuiltInFunction> len_BIF();
        // static std::shared_ptr<New_BuiltInFunction> gcd_BIF();
        // static std::shared_ptr<New_BuiltInFunction> rand_BIF();
    };

    class New_DefFunction: public New_BaseFunction{
    protected:
        uNode m_body;

    public:
        New_DefFunction(std::vector<std::string> args, uNode&& body);

        sObject parenthesis(const std::vector<sObject> &args, Visitor& visitor) override;

        std::string toString() override;
        Object* copy() override;
    };

} // hdg

