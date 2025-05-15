#include "../../include/node/visitor.h"

#include <iostream>
#include <cassert>
#include <typeinfo>

#include "../../include/node/BinaryOperatorNode.h"
#include "../../include/node/ObjectNode.h"

namespace hdg{
    void Visitor::visitBinOperNode(BinOperNode& node){
        std::cout << "Visitor::visitBinOperNode() is not implement!" << std::endl;
    }

    void Visitor::visitNumObjNode(NumObjNode& node){
        std::cout << "Visitor::visitNumObjNode() is not implement!" << std::endl;
    }

    void Visitor::visitIntNode(IntNode& node){
        std::cout << "Visitor::visitIntNode() is not implement!" << std::endl;
    }

    uObject& Visitor::getResult(){
        return m_res;
    }

    uObject Visitor::moveResult(){
        return std::move(m_res);
    }

    void InterpreterVisitor::visitBinOperNode(BinOperNode& node){
        auto& left = node.getLeft();
        left->accept(*this);
        auto left_val = moveResult();

        auto& right = node.getRight();
        right->accept(*this);
        auto right_val = moveResult();

        Token oper = node.getOper();

        if (oper.getType() == Token::Type::PLUS){
            m_res = left_val->plus(right_val);
        }
        else if (oper.getType() == Token::Type::MINUS){

        }
        else if (oper.getType() == Token::Type::MUL){

        }
        else if (oper.getType() == Token::Type::DIV){
            
        }
        else{
            assert(false && "Unknow Oper!");
        }
    }

    void InterpreterVisitor::visitIntNode(IntNode& node){
        m_res = std::make_unique<Integer>(node.getValue());
    }
}
