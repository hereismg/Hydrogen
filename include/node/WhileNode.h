//
// Created by Magnesium on 2023/8/2.
//

#ifndef HDG_WHILENODE_H
#define HDG_WHILENODE_H

#include "Node.h"
#include "../data_type/None.h"

namespace hdg {

    class WhileNode: public Node {
    private:
        Node* m_condition;
        Node* m_expression;

    public:
        WhileNode(Node* condition, Node* expression, const Position& position, Environment* parent);

        void setCondition(Node* condition);
        void setExpression(Node* expression);

        std::string toString() override;
        Object* interpret() override;

    };

} // hdg

#endif //HDG_WHILENODE_H
