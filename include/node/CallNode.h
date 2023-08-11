//
// Created by Magnesium on 2023/8/11.
//

#ifndef HDG_CALLNODE_H
#define HDG_CALLNODE_H

#include "Node.h"
#include "../basic/Token.h"

namespace hdg {

    class CallNode: public Node{
    protected:
        Node* m_call;
        std::vector<Node*> m_list;
        TokenType m_oper;

    public:
        CallNode();
        CallNode(const Position& position, Environment* environment);
        CallNode(Node* call, std::vector<Node*>list, TokenType oper, const Position& position, Environment* environment);

        void addNode(Node* node);
        void setOperator(TokenType oper);
        void setCall(Node* call);

        std::string toString() override;
        Object* interpret() override;
    };

} // hdg

#endif //HDG_CALLNODE_H
