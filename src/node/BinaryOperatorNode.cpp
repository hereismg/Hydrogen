//
// Created by Magnesium on 2023/7/19.
//

#include "../../include/node/BinaryOperatorNode.h"

namespace hdg {

    BinaryOperatorNode::BinaryOperatorNode(const Token& oper, Node *left, Node *right, const Position& position):
        Node(position), m_oper(oper), m_left(left), m_right(right){
    }

    BinaryOperatorNode::BinaryOperatorNode(TokenType oper, Node *left, Node *right, const Position& position, Environment* environment):
        Node(position, environment), m_oper(oper), m_left(left), m_right(right){
    }

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
            return tokenTypeName[m_oper.getType()];
        }else{
            return "(" + m_left->toString() + ", " + tokenTypeName[m_oper.getType()] + ", " + m_right->toString() + ")";
        }
    }

    Object* BinaryOperatorNode::interpret() {
        Object* left = m_left->interpret();
        if (left->getClass() == "None"){
            throw RuntimeError(
                "this is 'None'.",
                *m_left->thisPosition()
                    );
        }
        Object* right = m_right->interpret();
        if (right->getClass() == "None"){
            throw RuntimeError(
                    "this is 'None'.",
                    *m_right->thisPosition()
            );
        }

        Object* result = nullptr;

        if (m_oper.getType() == PLUS){
            result = left->plus(right);
        }
        else if (m_oper.getType() == MINUS){
            result = left->minus(right);
        }
        else if (m_oper.getType() == MUL){
            result = left->mul(right);
        }
        else if (m_oper.getType() == DIV){
            try{
                result = left->div(right);
            }
            catch (int error){
                delete left, right;
                throw RuntimeError(
                        "Division by zero",
                        Position(
                                m_position.thisContext(),
                                m_right->thisPosition()->getPosStart(),
                                m_right->thisPosition()->getPosEnd())
                        );
            }
        }
        else if (m_oper.getType() == POW){
            result = left->pow(right);
        }
        else if (m_oper.getType() == EE){
            result = left->equation(right);
        }
        else if (m_oper.getType() == NE){
            result  = left->notEquation(right);
        }
        else if (m_oper.getType() == GT){
            result = left->greaterThan(right);
        }
        else if (m_oper.getType() == LT){
            result = left->lessThan(right);
        }
        else if (m_oper.getType() == GTE){
            result = left->greaterThanEquation(right);
        }
        else if (m_oper.getType() == LTE){
            result = left->lessThanEquation(right);
        }
        else if (m_oper.match(KEYWORD, "and")){
            result = left->andOperator(right);
        }
        else if (m_oper.match(KEYWORD, "or")){
            result = left->orOperator(right);
        }

        delete left, right;
        return result;
    }
} // hdg