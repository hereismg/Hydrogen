//
// Created by Magnesium on 2023/7/19.
//

#ifndef HDG_BINARYOPERATORNODE_H
#define HDG_BINARYOPERATORNODE_H

#include <string>
#include <cmath>
#include "Node.h"
#include "../Token.h"
#include "../error/RunTimeError.h"

namespace hdg {

    class BinaryOperatorNode: public Node{
    private:
        std::string oper_;
        Node* left_;
        Node* right_;

    public:
        BinaryOperatorNode(std::string oper, Node* left, Node* right, const Position& position);

        void setOperator(std::string oper);
        void setLeft(Node* node);
        void setRight(Node* node);
        std::string getOperator();
        Node* getLeft();
        Node* getRight();

        std::string toString() override;
        DataType* interpret() override;
    };

} // hdg

#endif //HDG_BINARYOPERATORNODE_H
