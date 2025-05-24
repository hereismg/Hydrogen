#include "../../include/node/stmt_node.h"

#include <cassert>

#include "../../include/node/ObjectNode.h"

namespace hdg{
    new_AssignNode::new_AssignNode(std::string name, uNode&& expr)
        : m_name(name), 
          m_lVal(std::make_unique<IdentNode>(name)),
          m_rVal(std::move(expr)) 
    {
        assert(m_rVal!=nullptr && "m_expr cannot is NULL!");
    }

    new_AssignNode::new_AssignNode(std::string name, uNode&& expr, const Position& pos)
        : Node(pos),
          m_name(std::move(name)), 
          m_lVal(std::make_unique<IdentNode>(name)),
          m_rVal(std::move(expr)) 
    {
        assert(m_rVal!=nullptr && "m_expr cannot is NULL!");
    }

    new_AssignNode::new_AssignNode(uNode&& lVal, uNode&& rVal)
        : m_lVal(std::move(lVal)), m_rVal(std::move(rVal)) {}


    new_AssignNode::new_AssignNode(uNode&& lVal, uNode&& rVal, const Position& pos)
        : Node(pos), m_lVal(std::move(lVal)), m_rVal(std::move(rVal)) {}

    std::string& new_AssignNode::getName(){
        return m_name;
    }

    uNode& new_AssignNode::getExpr(){
        return m_rVal;
    }

    void new_AssignNode::setName(std::string new_name){
        m_name = std::move(new_name);
    }

    void new_AssignNode::setExpr(uNode&& new_expr){
        m_rVal = std::move(new_expr);
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

    DefNode::DefNode(std::string name, uNode&& val)
        : m_name(std::move(name)), m_val(std::move(val)) 
    {
        assert(m_val != nullptr);
    }

    
    DefNode::DefNode(std::string name, uNode&& val, const Position& pos)
        : Node(pos), m_name(std::move(name)), m_val(std::move(val)) 
    {
        assert(m_val != nullptr);
    }

    std::string DefNode::toString(){
        return "AssignNode: " + m_name;
    }

    Object* DefNode::interpret(){
        assert(false && "DefNode::interpret");
    }

    void DefNode::accept(Visitor& visitor){
        visitor.visitDefNode(*this);
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

    new_WhileStmtNode::new_WhileStmtNode(uNode&& cond, uNode&& loopUnit)
        : m_cond(std::move(cond)), m_loopUnit(std::move(loopUnit))
    {
        assert(m_cond != nullptr);
        assert(m_loopUnit != nullptr);
    }

    new_WhileStmtNode::new_WhileStmtNode(uNode&& cond, uNode&& loopUnit, const Position& pos)
        : Node(pos), m_cond(std::move(cond)), m_loopUnit(std::move(loopUnit))
    {
        assert(m_cond != nullptr);
        assert(m_loopUnit != nullptr);
    }

    uNode& new_WhileStmtNode::getCond(){
        return m_cond;
    }

    uNode& new_WhileStmtNode::getLoopUnit(){
        return m_loopUnit;
    }

    std::string new_WhileStmtNode::toString(){
        return "while";
    }
    
    Object* new_WhileStmtNode::interpret(){
        assert(false);
    }

    void new_WhileStmtNode::accept(Visitor& visitor){
        visitor.visitWhileStmtNode(*this);
    }
}