#ifndef STMT_NODE_H
#define STMT_NODE_H

#include "Node.h"

namespace hdg{
    // hdgTODO: rename AssignNode
    class new_AssignNode : public Node{
    protected:
        std::string m_name;
        uNode m_lVal;
        uNode m_rVal;

    public:
        new_AssignNode(std::string name, uNode&& rVal);
        new_AssignNode(std::string name, uNode&& rVal, const Position& pos);
        new_AssignNode(uNode&& lVal, uNode&& rVal);
        new_AssignNode(uNode&& lVal, uNode&& rVal, const Position& pos);

        std::string& getName();
        uNode& getExpr();
        uNode& getLVal() { return m_lVal; }
        uNode& getRVal() { return m_rVal; }

        void setName(std::string new_name);
        void setExpr(uNode&& new_expr);
        void setLVal(uNode&& lVal) { m_lVal = std::move(lVal); }
        void setRVal(uNode&& rVal) { m_rVal = std::move(rVal); }

        nlohmann::json toJSON() const override;
        virtual std::string toString();
        virtual Object* interpret();
        virtual void accept(Visitor& visitor);
    };

    class DefNode: public Node {
    protected:
        std::string m_name;
        uNode m_val;

    public:
        DefNode(std::string name, uNode&& val);
        DefNode(std::string name, uNode&& val, const Position& pos);

        uNode& getVal() { return m_val; }
        std::string getName() { return m_name; }

        nlohmann::json toJSON() const override;
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

        nlohmann::json toJSON() const override;
        virtual std::string toString();
        virtual Object* interpret();
        virtual void accept(Visitor& visitor);
    };

    class new_WhileStmtNode: public Node{
    protected:
        uNode m_cond;
        uNode m_loopUnit;
    
    public:
        new_WhileStmtNode(uNode&& cond, uNode&& loopUnit);
        new_WhileStmtNode(uNode&& cond, uNode&& loopUnit, const Position& pos);

        uNode& getCond();
        uNode& getLoopUnit();

        nlohmann::json toJSON() const override;
        virtual std::string toString();
        virtual Object* interpret();
        virtual void accept(Visitor& visitor);
    };
}

#endif