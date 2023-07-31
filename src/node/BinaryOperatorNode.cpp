//
// Created by Magnesium on 2023/7/19.
//

#include "../../include/node/BinaryOperatorNode.h"

namespace hdg {

    BinaryOperatorNode::BinaryOperatorNode(TokenType oper, Node *left, Node *right, const Position& position):
        Node(position), m_oper(oper), m_left(left), m_right(right){
    }

    BinaryOperatorNode::BinaryOperatorNode(TokenType oper, Node *left, Node *right, const Position& position, Environment* environment):
        Node(position, environment), m_oper(oper), m_left(left), m_right(right){
    }

    BinaryOperatorNode::~BinaryOperatorNode() {
        delete m_left;
        delete m_right;
    }

    void BinaryOperatorNode::setOperator(TokenType oper){
        m_oper = oper;
    }

    void BinaryOperatorNode::setLeft(Node *node) {
        m_left = node;
    }

    void BinaryOperatorNode::setRight(Node *node) {
        m_right = node;
    }

    TokenType BinaryOperatorNode::getOperator() {
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
            return tokenTypeName[m_oper];
        }else{
            return "(" + m_left->toString() + ", " + tokenTypeName[m_oper] + ", " + m_right->toString() + ")";
        }
    }

    DataType* BinaryOperatorNode::interpret() {
        DataType* left = m_left->interpret();
        DataType* right = m_right->interpret();

        DataType* result = nullptr;

        if (m_oper == PLUS){
            result = left->plus(right);
        }
        else if (m_oper == MINUS){
            result = left->minus(right);
        }
        else if (m_oper == MUL){
            result = left->mul(right);
        }
        else if (m_oper == DIV){
            try{
                result = left->div(right);
            }
            catch (int error){
                delete left, right;
                throw RunTimeError(
                        "Division by zero",
                        Position(
                                m_position.thisContext(),
                                m_right->thisPosition()->getPosStart(),
                                m_right->thisPosition()->getPosEnd())
                        );
            }
        }
        else if (m_oper == POW){
            result = left->pow(right);
        }

        delete left, right;
        return result;
    }
} // hdg