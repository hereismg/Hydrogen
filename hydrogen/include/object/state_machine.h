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
        std::shared_ptr<New_Environment> m_envir;

    public:
        StateMachine();

        static sStateMachine create(vector<uNode> stmts);

        inline vector<uNode>& refStmts() { return m_stmts; }

        void exe(Visitor & visitor, i32 index);
        void exe(Visitor & visitor, i32 begin, i32 end);

        std::string toString() override { return "StateMachine"; }

        /**
         * 四则运算
         * 
         * ```hdg
         * sm Test1{
         *     var a = 2
         * }
         * 
         * sm Test2{
         *     a + 3
         * }
         * 
         * Test3 = Test1 + Test2
         * Test3()
         * ```
        */

        // hdg 表达式重载函数
        // sObject parenthesis(const vector<sObject>& args, Visitor& visitor) override;
        
        /**
         * “[]”方括号运算符
         * 
         * 方括号运算符
         * 
         * ```hdg
         * sm Test{
         *     var a = 1 + 2
         *     a + 3
         * }
         * Test[0:2] // 实际上，代码会执行第一行和第二行
         * ```
        */
        sObject brackets(
            const vector<sObject>& args, 
            Visitor& visitor
        ) override;
        
        // sObject dotFun(
        //     const std::string& ident,
        //     std::vector<sObject>&& args,
        //     Visitor& visitor
        // ) override;
    
    };

} // namespace hdg
 