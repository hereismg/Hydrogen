#ifndef STMT_NODE_H
#define STMT_NODE_H

#include "Node.h"

namespace hdg{
    // hdgTODO: rename AssignNode
    class new_AssignNode : public Node{
    protected:
        std::string m_name;
        uNode m_expr;

    public:
        new_AssignNode(std::string name, uNode&& expr);
        new_AssignNode(std::string name, uNode&& expr, const Position& pos);

        std::string& getName();
        uNode& getExpr();

        void setName(std::string new_name);
        void setExpr(uNode&& new_expr);

        virtual std::string toString();
        virtual Object* interpret();
        virtual void accept(Visitor& visitor);
    };

    class new_IfStmtNode: public Node{
    protected:
        std::vector<uNode> m_cond;
        std::vector<uNode> m_exeUnit;
        uNode m_elseExeUnit;
    
    public:
        new_IfStmtNode() = default;

        void addBranch(uNode&& cond, uNode&& exeUnit);
        void addElseBranch(uNode&& exeUnit);

        std::vector<uNode>& getCond();
        std::vector<uNode>& getExeUnit();
        uNode& getElseExeUnit();

        virtual std::string toString();
        virtual Object* interpret();
        virtual void accept(Visitor& visitor);
    };
}

#endif