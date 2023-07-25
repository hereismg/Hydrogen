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
        std::string oper;
        Node* obj;

    public:
        UnaryOperatorNode(std::string oper, Node* obj, const Position& position);

        void setOperator(std::string oper);
        void setObject(Node* obj);

        std::string getOperator();
        Node* getObject();

        std::string toString() override;
        DataType* interpret() override;
    };

} // hdg

#endif //HDG_UNARYOPERATORNODE_H
