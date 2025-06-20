//
// Created by Magnesium on 2023/8/4.
//
#pragma once

#include <functional>
#include <memory>

#include "../node/Node.h"


namespace hdg {
    using std::vector;

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

