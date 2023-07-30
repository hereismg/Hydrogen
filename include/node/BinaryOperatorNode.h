//
// Created by Magnesium on 2023/7/19.
//

#ifndef HDG_BINARYOPERATORNODE_H
#define HDG_BINARYOPERATORNODE_H

#include <string>
#include <cmath>
#include <utility>
#include "Node.h"
#include "../basic/Token.h"
#include "../error/RunTimeError.h"

namespace hdg {

    class BinaryOperatorNode: public Node{
    private:
        TokenType m_oper;
        Node* m_left;
        Node* m_right;

    public:
        BinaryOperatorNode(TokenType oper, Node* left, Node* right, const Position& position);
        BinaryOperatorNode(TokenType oper, Node* left, Node* right, const Position& position, Environment* environment);

        void setOperator(TokenType oper);
        void setLeft(Node* node);
        void setRight(Node* node);
        TokenType getOperator();
        Node* getLeft();
        Node* getRight();

        std::string toString() override;
        DataType* interpret() override;
    };

} // hdg

#endif //HDG_BINARYOPERATORNODE_H
