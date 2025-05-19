#include "../../include/node/visitor.h"

#include <iostream>
#include <cassert>
#include <typeinfo>

#include "../../include/node/BinaryOperatorNode.h"
#include "../../include/node/ObjectNode.h"
#include "../../include/node/stmt_node.h"
#include "../../include/node/unit_node.h"

namespace hdg{
    Visitor::Visitor(){
        m_stack.emplace_back(new New_Environment);
    }

    void Visitor::visitBinOperNode(BinOperNode& node){
        std::cout << "Visitor::visitBinOperNode() is not implement!" << std::endl;
    }

    void Visitor::visitNumObjNode(NumObjNode& node){
        std::cout << "Visitor::visitNumObjNode() is not implement!" << std::endl;
    }

    void Visitor::visitFuncObjNode(FuncObjNode& node){
        std::cout << "Visitor::visitFuncObjNode() is not implement!" << std::endl;
    }

    void Visitor::visitIntNode(IntNode& node){
        std::cout << "Visitor::visitIntNode() is not implement!" << std::endl;
    }
    
    void Visitor::visitIdentNode(IdentNode& node){
        std::cout << "Visitor::visitIdentNode() is not implement!" << std::endl;
    }
    
    void Visitor::visitAssignNode(new_AssignNode& node){
        std::cout << "Visitor::visitAssignNode() is not implement!" << std::endl;
    }

    void Visitor::visitIfStmtNode(new_IfStmtNode& node){
        std::cout << "Visitor::visitIfStmtNode() is not implement!" << std::endl;
    }

    void Visitor::visitWhileStmtNode(new_WhileStmtNode& node){
        std::cout << "Visitor::visitWhileStmtNode() is not implement!" << std::endl;
    }

    void Visitor::visitExeUnitNode(new_ExeUnitNode& node){
        std::cout << "Visitor::visitExeUnitNode() is not implement!" << std::endl;
    }

    std::vector<std::shared_ptr<New_Environment>>& Visitor::getStack(){
        return m_stack;
    }

    sObject Visitor::getResult(){
        return m_res;
    }

    sObject Visitor::moveResult(){
        return std::move(m_res);
    }

    std::shared_ptr<New_Environment> Visitor::getCurrentEnvir(){
        return m_stack.back();
    }

    void InterpreterVisitor::visitBinOperNode(BinOperNode& node){
        auto& left = node.getLeft();
        left->accept(*this);
        auto left_val = moveResult();
        assert(left_val != nullptr && "InterpreterVisitor::visitBinOperNode: left_val must be not null!");

        auto& right = node.getRight();
        right->accept(*this);
        auto right_val = moveResult();
        assert(right_val != nullptr && "InterpreterVisitor::visitBinOperNode: right_val must be not null!");

        Token oper = node.getOper();

        if (oper.getType() == Token::Type::PLUS){
            m_res = left_val->plus(right_val);
        }
        else if (oper.getType() == Token::Type::MINUS){
            m_res = left_val->minus(right_val);
        }
        else if (oper.getType() == Token::Type::MUL){
            m_res = left_val->mul(right_val);
        }
        else if (oper.getType() == Token::Type::DIV){
            m_res = left_val->div(right_val);
        }
        else{
            assert(false && "Unknow Oper!");
        }
    }

    void InterpreterVisitor::visitIntNode(IntNode& node){
        m_res = std::make_shared<Integer>(node.getValue());
    }

    void InterpreterVisitor::visitFuncObjNode(FuncObjNode& node){
        m_res = node.getObj();
    }

    void InterpreterVisitor::visitIdentNode(IdentNode& node){
        auto obj = m_stack.back()->getSymbol(node.getIdent());
        m_res = std::move(obj);
    }

    void InterpreterVisitor::visitAssignNode(new_AssignNode& node) {
        std::string& name = node.getName();

        auto& expr = node.getExpr();
        expr->accept(*this);
        auto res = moveResult();
        assert(res != nullptr);

        m_stack.back()->setSymbol(name, std::move(res));
    }

    void InterpreterVisitor::visitIfStmtNode(new_IfStmtNode& node) {
        auto& cond = node.getCond();
        auto& exeUnit = node.getExeUnit();
        assert(cond.size() == exeUnit.size());
        auto& elseExeUnit = node.getElseExeUnit();

        for (size_t i = 0; i < cond.size(); i++){
            cond[i]->accept(*this);
            auto obj = getResult();

            if (obj->isTrue()){
                exeUnit[i]->accept(*this);
            }
        }

        if (elseExeUnit != nullptr){
            elseExeUnit->accept(*this);
        }
    }

    void InterpreterVisitor::visitWhileStmtNode(new_WhileStmtNode& node) {
        auto& cond = node.getCond();
        auto& loopUnit = node.getLoopUnit();

        while(true){
            cond->accept(*this);
            auto obj = getResult();

            if (obj->isTrue()){
                loopUnit->accept(*this);
            }
            else{
                break;
            }
        }
    }

    void InterpreterVisitor::visitExeUnitNode(new_ExeUnitNode& node){
        auto& list = node.getList();
        for (auto& stmt : list){
            assert(stmt != nullptr);
            stmt->accept(*this);
        }
    }
}
