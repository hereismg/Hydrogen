//
// Created by Magnesium on 2023/7/22.
//

#include "Node.h"
#include "../Token.h"

#ifndef HDG_UNARYOPERATORNODE_H
#define HDG_UNARYOPERATORNODE_H

namespace hdg {

    class UnaryOperatorNode: public Node{
    private:
        std::string oper;
        Node* obj;

    public:
        explicit UnaryOperatorNode(std::string oper);
        UnaryOperatorNode(std::string oper, Node* obj);

        void setOperator(std::string oper);
        void setObject(Node* obj);

        std::string getOperator();
        Node* getObject();

        std::string toString() override;
        std::string interpret() override;
    };

} // hdg

#endif //HDG_UNARYOPERATORNODE_H
