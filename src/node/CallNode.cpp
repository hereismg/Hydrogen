//
// Created by Magnesium on 2023/8/11.
//

#include "../../include/node/CallNode.h"

namespace hdg {
    CallNode::CallNode() = default;

    CallNode::CallNode(Node* call, std::vector<Node *> list, TokenType oper, const Position &position,
                       Environment *environment):
       Node(position, environment), m_call(call), m_list(std::move(list)), m_oper(oper){}


    CallNode::CallNode(const Position &position, Environment *environment):
        Node(position, environment){}

    CallNode::~CallNode() {
        delete m_call;
        for (auto i: m_list) delete i;
    }

    void CallNode::addNode(Node *node) {
        m_list.push_back(node);
    }

    void CallNode::setOperator(TokenType oper) {
        m_oper = oper;
    }

    void CallNode::setCall(Node* call) {
        m_call = call;
    }

    std::string CallNode::toString() {
        return "CallNode";
    }

    Object *CallNode::interpret() {
        Object* obj = m_call->interpret();
        std::vector<Object*> objList;
        objList.reserve(m_list.size());
        for (auto & i : m_list) objList.push_back(i->interpret());

        if (m_oper == LPAREN){
            return obj->parenthesis(objList);
        }
        else{
            throw RuntimeError(
                    "Error",
                    m_position
            );
        }
    }

} // hdg