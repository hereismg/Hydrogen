//
// Created by Magnesium on 2023/8/11.
//

#ifndef HDG_CALLNODE_H
#define HDG_CALLNODE_H

#include "Node.h"
#include "../basic/Token.h"

namespace hdg {

    /**
     * 呼叫节点。用于圆括号、方括号等等的使用。
     * */
    class CallNode: public Node{
    protected:
        Node* m_call{nullptr};                  /// 被呼叫对象
        std::vector<Node*> m_list;              /// 参数列表
        Token::Type m_oper;                     /// 呼叫类型

    public:
        CallNode();
        CallNode(const Position& position, Environment* environment);
        CallNode(Node* call, std::vector<Node*> list, Token::Type oper, const Position& position, Environment* environment);
        ~CallNode() override;

        void addNode(Node* node);
        void setOperator(Token::Type oper);
        void setCall(Node* call);

        std::string toString() override;
        Object* interpret() override;
    };

} // hdg

#endif //HDG_CALLNODE_H
