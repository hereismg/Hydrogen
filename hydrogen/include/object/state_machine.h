#pragma once

#include <vector>

#include "Object.h"
#include "../node/unit_node.h"

namespace hdg {
    using std::vector;

    class StateMachine;
    typedef std::shared_ptr<StateMachine> sStateMachine;

    class StateMachine: public Object{
    protected:
        vector<uNode> m_stmts;
        New_Environment m_envir;

    public:
        StateMachine() = default;

        static sStateMachine create(vector<uNode> stmts);

        inline vector<uNode>& refStmts() { return m_stmts; }

        // void exe(i32 index);
        // void exe(i32 begin, i32 end);

        std::string toString() override { return "StateMachine"; }

        // hdg 表达式重载函数
        // sObject parenthesis(const vector<sObject>& args, Visitor& visitor) override;
        // sObject brackets(const vector<sObject>& args, Visitor& visitor) override;
        // sObject dotFun(
        //     const std::string& ident,
        //     std::vector<sObject>&& args,
        //     Visitor& visitor
        // ) override;
    
    };

} // namespace hdg
 