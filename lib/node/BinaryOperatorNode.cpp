//
// Created by Magnesium on 2023/7/19.
//

#include "BinaryOperatorNode.h"

#include <utility>

namespace hdg {

    BinaryOperatorNode::BinaryOperatorNode(std::string oper):
        oper_(std::move(oper)), left_(nullptr), right_(nullptr){
    }

    BinaryOperatorNode::BinaryOperatorNode(std::string oper, Node *left, Node *right):
        oper_(std::move(oper)), left_(left), right_(right){
    }

    void BinaryOperatorNode::setOperator(std::string oper) {
        oper_ = std::move(oper);
    }

    void BinaryOperatorNode::setLeft(Node *node) {
        left_ = node;
    }

    void BinaryOperatorNode::setRight(Node *node) {
        right_ = node;
    }

    std::string BinaryOperatorNode::getOperator() {
        return oper_;
    }

    Node *BinaryOperatorNode::getLeft() {
        return left_;
    }

    Node *BinaryOperatorNode::getRight() {
        return right_;
    }

    std::string BinaryOperatorNode::toString() {
        if (left_ == nullptr && right_ == nullptr){
            return oper_;
        }else{
            return "(" + left_->toString() + ", " + oper_ + ", " + right_->toString() + ")";
        }
        return Node::toString();
    }

    DataType* BinaryOperatorNode::interpret() {
        DataType* left = left_->interpret();
        DataType* right = right_->interpret();

        DataType* result = nullptr;

        if (oper_ == TT_PLUS){
            result = left->plus(right);
        }
        else if (oper_ == TT_MINUS){
            result = left->minus(right);
        }
        else if (oper_ == TT_MUL){
            result = left->mul(right);
        }
        else if (oper_ == TT_DIV){
            result = left->div(right);
        }
        else if (oper_ == TT_POW){
            result = left->pow(right);
        }

        return result;
    }
} // hdg