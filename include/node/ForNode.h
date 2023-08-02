//
// Created by Magnesium on 2023/8/2.
//

#ifndef HDG_FORNODE_H
#define HDG_FORNODE_H

#include "../basic/Token.h"
#include "Node.h"

namespace hdg {

    class ForNode: public Node{
    private:
        Token m_index;
        int m_from;
        int m_to;
        int m_step;
        Node* m_expr;

    public:
        ForNode(const Token& index, int to, const Position& position, Environment* environment);
        ForNode(const Token& index, int from, int to, int step, Node* expr, const Position& position, Environment* environment);

        std::string toString() override;
        DataType* interpret() override;
    };

} // hdg

#endif //HDG_FORNODE_H
