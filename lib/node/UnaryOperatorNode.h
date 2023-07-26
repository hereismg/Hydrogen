//
// Created by Magnesium on 2023/7/22.
//


#ifndef HDG_UNARYOPERATORNODE_H
#define HDG_UNARYOPERATORNODE_H

#include "Node.h"
#include "../Token.h"
#include "../data_type/Integer.h"
#include "../data_type/Float.h"

namespace hdg {

    class UnaryOperatorNode: public Node{
    private:
        TokenType m_oper;
        Node* m_obj;

    public:
        UnaryOperatorNode(TokenType oper, Node* obj, const Position& position);

        void setOperator(TokenType oper);
        void setObject(Node* obj);

        TokenType getOperator();
        Node* getObject();

        std::string toString() override;
        DataType* interpret() override;
    };

} // hdg

#endif //HDG_UNARYOPERATORNODE_H
