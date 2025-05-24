#include "../../include/node/visitor.h"

#include <iostream>
#include <cassert>
#include <typeinfo>
#include <ranges>

#include "../../include/node/BinaryOperatorNode.h"
#include "../../include/node/ObjectNode.h"
#include "../../include/node/stmt_node.h"
#include "../../include/node/unit_node.h"
#include "../../include/object/Function.h"

namespace hdg{
    Visitor::Visitor(): m_lVal(nullptr){
        m_stack.emplace_back(new New_Environment);
    }

    void Visitor::visitBinOperNode(BinOperNode& node){
        std::cout << "Visitor::visitBinOperNode() is not implement!" << std::endl;
    }

    void Visitor::visitPostfixNode(PostfixNode& node){
        std::cout << "Visitor::visitPostfixNode() is not implement!" << std::endl;
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

    void Visitor::visitDefNode(DefNode& node){
        std::cout << "Visitor::visitDefNode() is not implement!" << std::endl;
    }


    void Visitor::visitFuncDefNode(New_FuncObjNode& node){
        std::cout << "Visitor::visitFuncDefNode() is not implement!" << std::endl;
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
        return m_rVal;
    }

    sObject Visitor::moveResult(){
        return std::move(m_rVal);
    }

    std::shared_ptr<New_Environment> Visitor::getCurrentEnvir(){
        return m_stack.back();
    }

    void InterpreterVisitor::visitBinOperNode(BinOperNode& node){
        auto& left = node.getLeft();
        assert(left != nullptr);
        left->accept(*this);
        auto left_val = getResult();
        assert(left_val != nullptr && "InterpreterVisitor::visitBinOperNode: left_val must be not null!");

        auto& right = node.getRight();
        assert(right != nullptr);
        right->accept(*this);
        auto right_val = getResult();
        assert(right_val != nullptr && "InterpreterVisitor::visitBinOperNode: right_val must be not null!");

        Token oper = node.getOper();

        if (oper.getType() == Token::Type::PLUS){
            m_rVal = left_val->plus(right_val);
        }
        else if (oper.getType() == Token::Type::MINUS){
            m_rVal = left_val->minus(right_val);
        }
        else if (oper.getType() == Token::Type::MUL){
            m_rVal = left_val->mul(right_val);
        }
        else if (oper.getType() == Token::Type::DIV){
            m_rVal = left_val->div(right_val);
        }
        else{
            assert(false && "Unknow Oper!");
        }
    }

    void InterpreterVisitor::visitPostfixNode(PostfixNode& node){ 
        sObject obj;
        auto& primary = node.getPrimary();
        // auto  ident   = node.getIdent(); // hdgtodo: 统一 get 、 move、this 三种访问对象变量的语义
        if(primary != nullptr) {
            primary->accept(*this);
            obj = getResult();
        }
        // else if (ident != ""){
        //     obj = m_stack.back()->getSymbol(ident);
        // }
        else {
            assert(false);
        }

        auto  type = node.getType();
        auto& exprList = node.getExprList();

        // 1. 获得参数列表
        std::vector<sObject> args(exprList.size(), nullptr);
        for (size_t i = 0; i < exprList.size(); i++){
            exprList[i]->accept(*this);
            args[i] = getResult();
        }

        switch (type){
            case Token::Type::RPAREN :
            case Token::Type::LPAREN : { 
                // 圆括号 ()
                obj->parenthesis(args, *this);
                break;
            }
            case Token::Type::RBRACKET :
            case Token::Type::LBRACKET : {
                // 方括号 []
                m_rVal = obj->brackets(args, *this);
                break;
            }
            case Token::Type::DOT : {
                // 点号 .

                break;
            }
            case Token::Type::IDENTIFIER : {
                // 变量
                m_rVal = std::move(obj);
                break;
            }
            default : {
                assert(false); // hdgtodo: 这样应该 hdg 报错：非法的后缀表达式
                break;
            }
        }
    }


    void InterpreterVisitor::visitIntNode(IntNode& node){
        m_rVal = std::make_shared<Integer>(node.getValue());
    }

    void InterpreterVisitor::visitFuncObjNode(FuncObjNode& node){
        m_rVal = node.getObj();
    }

    void InterpreterVisitor::visitIdentNode(IdentNode& node){
        for (auto envir : m_stack | std::views::reverse){

            sObject* obj = envir->getSymbolPtr(node.getIdent());
            if (obj != nullptr){
                m_rVal = *obj;
                m_lVal = obj;
                return;
            }
        }

        assert(false && "The symbol does not exist");
    }

    void InterpreterVisitor::visitAssignNode(new_AssignNode& node) {
        std::string& name = node.getName();

        auto& expr = node.getExpr();
        expr->accept(*this);
        auto res = moveResult();
        assert(res != nullptr);

        m_stack.back()->setSymbol(name, std::move(res));

        // uNode& lValNode = node.getLVal();
        // uNode& rValNode = node.getRVal();

        // lValNode->accept(*this);
        // sObject* lVal = getLVal();
        // rValNode->accept(*this);
        // sObject  rVal = getRVal();

        // *lVal = rVal;
    }

    void InterpreterVisitor::visitDefNode(DefNode& node) {
        std::string name = node.getName();

        uNode& val = node.getVal();
        val->accept(*this);
        sObject obj = getRVal();
        assert(obj != nullptr);

        m_stack.back()->setSymbol(name, obj);
    }

    void InterpreterVisitor::visitFuncDefNode(New_FuncObjNode& node) { // hdgtodo: 改名
        m_rVal = std::make_shared<New_DefFunction>( 
            node.getArgs(), 
            node.moveBody()  // hdgtodo: 应该改成 clone，而不是移动所有权
        );
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
