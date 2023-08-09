//
// Created by Magnesium on 2023/8/2.
//

#ifndef HDG_FORNODE_H
#define HDG_FORNODE_H

#include "../basic/Token.h"
#include "Node.h"

namespace hdg {

    class ForNode: public Node{
    protected:
        Token m_index;
        int m_from;
        int m_to;
        int m_step;
        Node* m_expr;

    public:
        ForNode(const Token& index, int to, const Position& position, Environment* parent);
        ForNode(const Token& index, int from, int to, int step, Node* expr, const Position& position, Environment* parent);
        ~ForNode() override;

        void setIndex(const Token& index);
        void setFrom(int from);
        void setTo(int to);
        void setStep(int step);
        void setExpr(Node* expr);

        std::string toString() override;
        Object* interpret() override;
    };

} // hdg

#endif //HDG_FORNODE_H
