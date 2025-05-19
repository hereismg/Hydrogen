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

    class BinOperNode: public Node{
    protected:
        Token m_oper;
        uNode m_left;
        uNode m_right;

    public:
        BinOperNode(Token oper, uNode&& left, uNode&& right);
        BinOperNode(Token oper, uNode&& left, uNode&& right, Position pos);
        
        ~BinOperNode() = default;

        BinOperNode(const BinOperNode&) = delete;
        BinOperNode& operator=(const BinOperNode&) = delete;
        
        BinOperNode(BinOperNode&&) noexcept = default;
        BinOperNode& operator=(BinOperNode&&) noexcept = default;

        void setOper(Token oper);
        void setLeft(uNode&& new_left);
        void setRight(uNode&& new_right);

        const Token& getOper() const;
        uNode& getLeft();
        uNode& getRight();

        virtual std::string toString();
        virtual Object* interpret();
        virtual void accept(Visitor& visitor);
    };

    class PostfixNode: public Node{
        
    };

} // hdg

#endif //HDG_BINARYOPERATORNODE_H
