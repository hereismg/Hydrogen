//
// Created by Magnesium on 2023/8/14.
//

#ifndef HDG_STATEMENTSNODE_H
#define HDG_STATEMENTSNODE_H

#include <vector>
#include "Node.h"

namespace hdg {

    class StatementsNode: public Node{
    protected:
        std::vector<Node*> m_statements;

    public:
        StatementsNode();
        StatementsNode(const Position& position, Environment* environment);
        ~StatementsNode() override;

        void append(Node* node);

        std::string toString() override;
        Object* interpret() override;
    };

} // hdg

#endif //HDG_STATEMENTSNODE_H
