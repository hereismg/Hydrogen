//
// Created by Magnesium on 2023/7/22.
//


#ifndef HDG_UNARYOPERATORNODE_H
#define HDG_UNARYOPERATORNODE_H

#include "Node.h"
#include "../basic/Token.h"
#include "../data_type/Integer.h"
#include "../data_type/Float.h"

namespace hdg {

    class UnaryOperatorNode: public Node{
    private:
        Token m_oper;
        Node* m_obj;

    public:
        UnaryOperatorNode(TokenType oper, Node* obj, const Position& position);
        UnaryOperatorNode(Token oper, Node* obj, const Position& position);
        ~UnaryOperatorNode() override;

        void setOperator(const Token& oper);
        void setObject(Node* obj);

        Token getOperator();
        Node* getObject();

        std::string toString() override;
        DataType* interpret() override;
    };

} // hdg

#endif //HDG_UNARYOPERATORNODE_H
