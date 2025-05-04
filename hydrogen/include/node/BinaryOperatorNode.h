//
// Created by Magnesium on 2023/7/19.
//

#ifndef HDG_BINARYOPERATORNODE_H
#define HDG_BINARYOPERATORNODE_H

#include <string>
#include <cmath>
#include <utility>
#include <memory>
#include "Node.h"
#include "../basic/Token.h"
#include "../basic/Error.h"

namespace hdg {

    class BinaryOperatorNode: public Node{
    protected:
        Token m_oper;
        Node* m_left;
        Node* m_right;

        std::unique_ptr<Node> m_left_u;
        std::unique_ptr<Node> m_right_u;

    public:
        BinaryOperatorNode();
        BinaryOperatorNode(const Token& oper, Node* left, Node* right, const Position& position);
        BinaryOperatorNode(Token::Type oper, Node* left, Node* right, const Position& position, Environment* environment);
        ~BinaryOperatorNode() override;

        void setOperator(const Token& oper);
        void setLeft(Node* node);
        void setRight(Node* node);
        Token getOperator();
        Node* getLeft();
        Node* getRight();

        std::string toString() override;
        Object* interpret() override;
    };

} // hdg

#endif //HDG_BINARYOPERATORNODE_H
