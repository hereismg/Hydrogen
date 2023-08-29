//
// Created by Magnesium on 2023/7/19.
//

#include "../../include/node/BinaryOperatorNode.h"

namespace hdg {

    BinaryOperatorNode::BinaryOperatorNode(const Token& oper, Node *left, Node *right, const Position& position):
        Node(position), m_oper(oper), m_left(left), m_right(right){}

    BinaryOperatorNode::BinaryOperatorNode(Token::Type oper, Node *left, Node *right, const Position& position, Environment* environment):
        Node(position, environment), m_oper(oper), m_left(left), m_right(right){}

    BinaryOperatorNode::~BinaryOperatorNode() {
        delete m_left;
        delete m_right;
    }

    void BinaryOperatorNode::setOperator(const Token& oper){
        m_oper = oper;
    }

    void BinaryOperatorNode::setLeft(Node *node) {
        m_left = node;
    }

    void BinaryOperatorNode::setRight(Node *node) {
        m_right = node;
    }

    Token BinaryOperatorNode::getOperator() {
        return m_oper;
    }

    Node *BinaryOperatorNode::getLeft() {
        return m_left;
    }

    Node *BinaryOperatorNode::getRight() {
        return m_right;
    }

    std::string BinaryOperatorNode::toString() {
        if (m_left == nullptr && m_right == nullptr){
            return Token::TypeNameMap[m_oper.getType()];
        }else{
            return "(" + m_left->toString() + ", " + Token::TypeNameMap[m_oper.getType()] + ", " + m_right->toString() + ")";
        }
    }

    Object* BinaryOperatorNode::interpret() {
        Object* left = m_left->interpret();
//        if (left->getClass() == "None"){
//            throw RuntimeError(
//                "this is 'None'.",
//                *m_left->thisPosition()
//                    );
//        }
        Object* right = m_right->interpret();
//        if (right->getClass() == "None"){
//            throw RuntimeError(
//                    "this is 'None'.",
//                    *m_right->thisPosition()
//            );
//        }

        Object* result = nullptr;

        try{
            if (m_oper.getType() == Token::PLUS){
                result = left->plus(right);
            }
            else if (m_oper.getType() == Token::MINUS){
                result = left->minus(right);
            }
            else if (m_oper.getType() == Token::MUL){
                result = left->mul(right);
            }
            else if (m_oper.getType() == Token::DIV){
                result = left->div(right);
            }
            else if (m_oper.getType() == Token::MOD){
                result = left->mod(right);
            }
            else if (m_oper.getType() == Token::POW){
                result = left->pow(right);
            }
            else if (m_oper.getType() == Token::EE){
                result = left->equation(right);
            }
            else if (m_oper.getType() == Token::NE){
                result  = left->notEquation(right);
            }
            else if (m_oper.getType() == Token::GT){
                result = left->greaterThan(right);
            }
            else if (m_oper.getType() == Token::LT){
                result = left->lessThan(right);
            }
            else if (m_oper.getType() == Token::GTE){
                result = left->greaterThanEquation(right);
            }
            else if (m_oper.getType() == Token::LTE){
                result = left->lessThanEquation(right);
            }
            else if (m_oper.match(Token::KEYWORD, "and")){
                result = left->andOperator(right);
            }
            else if (m_oper.match(Token::KEYWORD, "or")){
                result = left->orOperator(right);
            }
            else{
                std::cout << "BinaryOperator::interpret(): Unknown token type.";
            }
        }
        catch (ZeroDivisionError& error){
            delete left, right;
            error.thisPosStack()->push_back(*m_right->thisPosition());
            throw error;
        }


        delete left, right;
        return result;
    }
} // hdg