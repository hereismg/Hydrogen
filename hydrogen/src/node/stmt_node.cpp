#include "../../include/node/stmt_node.h"

#include <cassert>

namespace hdg{
    new_AssignNode::new_AssignNode(std::string name, uNode&& expr)
        : m_name(std::move(name)), 
          m_expr(std::move(expr)) 
    {
        assert(m_expr!=nullptr && "m_expr cannot is NULL!");
    }

    new_AssignNode::new_AssignNode(std::string name, uNode&& expr, const Position& pos)
        : Node(pos),
          m_name(std::move(name)), 
          m_expr(std::move(expr)) 
    {
        assert(m_expr!=nullptr && "m_expr cannot is NULL!");
    }

    std::string& new_AssignNode::getName(){
        return m_name;
    }

    uNode& new_AssignNode::getExpr(){
        return m_expr;
    }

    void new_AssignNode::setName(std::string new_name){
        m_name = std::move(new_name);
    }

    void new_AssignNode::setExpr(uNode&& new_expr){
        m_expr = std::move(new_expr);
    }

    std::string new_AssignNode::toString(){
        return "AssignNode: " + m_name;
    }

    Object* new_AssignNode::interpret(){
        assert(false && "new_AssignNode::interpret");
    }

    void new_AssignNode::accept(Visitor& visitor){
        visitor.visitAssignNode(*this);
    }

    void new_IfStmtNode::addBranch(uNode&& cond, uNode&& exeUnit){
        m_cond.emplace_back(std::move(cond));
        m_exeUnit.emplace_back(std::move(exeUnit));
    }

    void new_IfStmtNode::addElseBranch(uNode&& exeUnit){
        m_elseExeUnit = std::move(exeUnit);
    }

    std::vector<uNode>& new_IfStmtNode::getCond(){
        return m_cond;
    }

    std::vector<uNode>& new_IfStmtNode::getExeUnit(){
        return m_exeUnit;
    }

    uNode& new_IfStmtNode::getElseExeUnit(){
        return m_elseExeUnit;
    }

    std::string new_IfStmtNode::toString(){
        return "if";
    }

    Object* new_IfStmtNode::interpret(){
        assert(false);
    }

    void new_IfStmtNode::accept(Visitor& visitor){
        visitor.visitIfStmtNode(*this);
    }
}